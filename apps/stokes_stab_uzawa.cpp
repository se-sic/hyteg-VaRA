
#include "tinyhhg_core/Format.hpp"

#include "core/Environment.h"
#include "core/mpi/MPIManager.h"

#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/composites/P1StokesFunction.hpp"
#include "tinyhhg_core/composites/P1StokesOperator.hpp"
#include "tinyhhg_core/gridtransferoperators/P1P1StokesToP1P1StokesProlongation.hpp"
#include "tinyhhg_core/gridtransferoperators/P1P1StokesToP1P1StokesRestriction.hpp"
#include "tinyhhg_core/solvers/UzawaSmoother.hpp"
#include "tinyhhg_core/solvers/GeometricMultigridSolver.hpp"
#include "tinyhhg_core/solvers/GaussSeidelSmoother.hpp"
#include "tinyhhg_core/solvers/MinresSolver.hpp"

using walberla::real_t;
using walberla::uint_t;
using walberla::real_c;

int main(int argc, char* argv[])
{
  walberla::Environment walberlaEnv(argc, argv);
  walberla::MPIManager::instance()->useWorldComm();

  walberla::shared_ptr<walberla::config::Config> cfg(new walberla::config::Config);
  if (walberlaEnv.config() == nullptr) {
    auto defaultFile = "../data/param/stokesUzawaTest.prm";
    cfg->readParameterFile(defaultFile);
    if(!*cfg){
      WALBERLA_ABORT("could not open default file: " << defaultFile);
    }
  } else {
    cfg = walberlaEnv.config();
  }

  auto parameters = cfg->getOneBlock("Parameters");
  hyteg::MeshInfo meshInfo = hyteg::MeshInfo::fromGmshFile( parameters.getParameter<std::string>("mesh") );
  hyteg::SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c ( walberla::mpi::MPIManager::instance()->numProcesses() ) );

  hyteg::loadbalancing::roundRobin( setupStorage );

  const uint_t minLevel = parameters.getParameter<uint_t>("minlevel");
  const uint_t maxLevel = parameters.getParameter<uint_t>("maxlevel");
  const uint_t coarseMaxiter = parameters.getParameter<uint_t>("coarse_iter");
  const real_t mg_tolerance = parameters.getParameter<real_t>("rel_tolerance");
  const uint_t maxOuterIter = parameters.getParameter<uint_t>("outer_iter");

  std::shared_ptr< hyteg::PrimitiveStorage> storage = std::make_shared< hyteg::PrimitiveStorage>(setupStorage);

  hyteg::P1StokesFunction<real_t> r("r", storage, minLevel, maxLevel);
  hyteg::P1StokesFunction<real_t> f("f", storage, minLevel, maxLevel);
  hyteg::P1StokesFunction<real_t> u("u", storage, minLevel, maxLevel);

  auto tmp = std::make_shared< hyteg::P1Function<real_t>>("tmp", storage, maxLevel, maxLevel);

  hyteg::P1StokesOperator L(storage, minLevel, maxLevel);

  std::function<real_t(const hyteg::Point3D&)> rhs = [](const hyteg::Point3D&) { return 0.0; };
  std::function<real_t(const hyteg::Point3D&)> zero = [](const hyteg::Point3D&) { return 0.0; };
  std::function<real_t(const hyteg::Point3D&)> ones = [](const hyteg::Point3D&) { return 1.0; };
  std::function<real_t(const hyteg::Point3D&)> rand = [](const hyteg::Point3D&) { return static_cast <real_t> (std::rand()) / static_cast <real_t> (RAND_MAX); };

  r.interpolate(ones, maxLevel);
  uint_t npoints = (uint_t) r.dotGlobal(r, maxLevel);
  r.interpolate(zero, maxLevel);

  u.u.interpolate(rand, maxLevel, hyteg::Inner);
  u.v.interpolate(rand, maxLevel, hyteg::Inner);
  u.p.interpolate(rand, maxLevel, hyteg::All);

  u.u.interpolate(zero, maxLevel, hyteg::DirichletBoundary);
  u.v.interpolate(zero, maxLevel, hyteg::DirichletBoundary);

  L.apply(u, r, maxLevel, hyteg::Inner | hyteg::NeumannBoundary);
  r.assign({1.0, -1.0}, { f, r }, maxLevel, hyteg::Inner | hyteg::NeumannBoundary);

   auto smoother = std::make_shared< hyteg::UzawaSmoother< hyteg::P1StokesOperator > >(
       storage, minLevel, maxLevel, 0.3 );
   auto coarseGridSolver = std::make_shared< hyteg::MinResSolver< hyteg::P1StokesOperator > >( storage, minLevel, minLevel, coarseMaxiter );
   auto restrictionOperator = std::make_shared< hyteg::P1P1StokesToP1P1StokesRestriction>();
   auto prolongationOperator = std::make_shared< hyteg::P1P1StokesToP1P1StokesProlongation >();

   auto solver = hyteg::GeometricMultigridSolver< hyteg::P1StokesOperator >(
       storage, smoother, coarseGridSolver, restrictionOperator, prolongationOperator, minLevel, maxLevel, 2, 2, 2 );

  WALBERLA_LOG_INFO_ON_ROOT("Num dofs = "<< npoints);
  WALBERLA_LOG_INFO_ON_ROOT("Starting Uzawa cycles");
  WALBERLA_LOG_INFO_ON_ROOT( hyteg::format("%6s|%10s|%10s|%10s|%10s","iter","abs_res","rel_res","conv","Time"));

  real_t begin_res = std::sqrt(r.dotGlobal(r, maxLevel, hyteg::Inner | hyteg::NeumannBoundary));
  real_t abs_res_old = begin_res;
  real_t rel_res = 1.0;

  WALBERLA_LOG_INFO_ON_ROOT(
      hyteg::format("%6d|%10.3e|%10.3e|%10.3e|%10.3e",0,begin_res, rel_res, begin_res/abs_res_old, 0));

  real_t totalTime = real_c(0.0);
  real_t averageConvergenceRate = real_c(0.0);
  const uint_t convergenceStartIter = 3;

  uint_t outer;
  for (outer = 0; outer < maxOuterIter; ++outer) {
    auto start = walberla::timing::getWcTime();
    solver.solve(L, u, f, maxLevel);
    auto end = walberla::timing::getWcTime();
    hyteg::vertexdof::projectMean(u.p, maxLevel);


    L.apply(u, r, maxLevel, hyteg::Inner | hyteg::NeumannBoundary);

    r.assign({1.0, -1.0}, { f, r }, maxLevel, hyteg::Inner | hyteg::NeumannBoundary);
    real_t abs_res = std::sqrt(r.dotGlobal(r, maxLevel, hyteg::Inner | hyteg::NeumannBoundary));
    rel_res = abs_res / begin_res;
    WALBERLA_LOG_INFO_ON_ROOT(
        hyteg::format("%6d|%10.3e|%10.3e|%10.3e|%10.3e",outer+1,abs_res, rel_res, abs_res/abs_res_old, end-start));
    totalTime += end-start;

    if (outer >= convergenceStartIter) {
      averageConvergenceRate += abs_res/abs_res_old;
    }

    abs_res_old = abs_res;

    if (rel_res < mg_tolerance)
    {
      break;
    }
  }

  WALBERLA_LOG_INFO_ON_ROOT("Time to solution: " << std::scientific << totalTime);
  WALBERLA_LOG_INFO_ON_ROOT("Avg. convergence rate: " << std::scientific << averageConvergenceRate / real_c(outer+1-convergenceStartIter));

//  hyteg::VTKWriter<hyteg::P1Function<real_t>, hyteg::DGFunction<real_t >>({&u.u, &u.v, &u.p, &f.u, &f->v, &f->p}, {}, maxLevel,
//                                                                    "../output", "after");
  return EXIT_SUCCESS;
}
