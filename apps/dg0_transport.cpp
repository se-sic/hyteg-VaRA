#include <core/timing/Timer.h>

#include <core/Environment.h>

#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/dgfunctionspace/DGFunction.hpp"
#include "tinyhhg_core/p1functionspace/P1Function.hpp"
#include "tinyhhg_core/dgfunctionspace/DGUpwindOperator.hpp"
#include "tinyhhg_core/VTKWriter.hpp"

using walberla::real_t;
using walberla::uint_t;
using walberla::uint_c;

using namespace hyteg;

int main(int argc, char* argv[])
{
  walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
  walberla::MPIManager::instance()->useWorldComm();

  std::string meshFileName = "../data/meshes/quad_4el.msh";

  hyteg::MeshInfo meshInfo = hyteg::MeshInfo::fromGmshFile( meshFileName );
  hyteg::SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c ( walberla::mpi::MPIManager::instance()->numProcesses() ) );

  hyteg::loadbalancing::roundRobin( setupStorage );

  const uint_t minLevel = 2;
  const uint_t maxLevel = 7;
  const uint_t timesteps = 10;
  real_t dt = 0.25 * std::pow(2.0, -walberla::real_c(maxLevel+1));
  WALBERLA_LOG_DEVEL("dt = " << dt)

  std::function<real_t(const hyteg::Point3D&)> initialConcentration = [](const hyteg::Point3D& x) {
    if ((x - Point3D{{{0.5, 0.5, 0.0}}}).norm() < 0.1) {
      return 1.0;
    } else {
      return 0.0;
    }
//    return 1.0;
  };

  std::function<real_t(const hyteg::Point3D&)> vel_x = [](const hyteg::Point3D&) {
//    return std::pow(x[1], 4.0) * (1.0 - x[0]) - x[0] * std::pow(1.0-x[1], 4.0);
    return 1.0;
  };

  std::function<real_t(const hyteg::Point3D&)> vel_y = [](const hyteg::Point3D&) {
//    return -std::pow(x[0], 4.0) * x[1] + std::pow(1.0-x[0], 4.0) * (1.0-x[1]);
    return 0.0;
  };

  std::shared_ptr< hyteg::PrimitiveStorage> storage = std::make_shared< hyteg::PrimitiveStorage>(setupStorage);

  std::shared_ptr< hyteg::DGFunction<real_t>> c_old = std::make_shared< hyteg::DGFunction<real_t>>("c_old", storage, minLevel, maxLevel);
  std::shared_ptr< hyteg::DGFunction<real_t>> c = std::make_shared< hyteg::DGFunction<real_t>>("c", storage, minLevel, maxLevel);
  std::shared_ptr< hyteg::P1Function<real_t>> u = std::make_shared< hyteg::P1Function<real_t>>("u", storage, minLevel, maxLevel);
  std::shared_ptr< hyteg::P1Function<real_t>> v = std::make_shared< hyteg::P1Function<real_t>>("v", storage, minLevel, maxLevel);

  std::array< hyteg::P1Function< real_t >, 2 > velocity{*u, *v};

  hyteg::DGUpwindOperator< hyteg::P1Function<real_t>> N(storage, velocity, minLevel, maxLevel);

  u->interpolate(vel_x, maxLevel);
  v->interpolate(vel_y, maxLevel);
  c_old->interpolate(initialConcentration, maxLevel);

  hyteg::VTKOutput vtkOutput("../output", "dg0_transport", storage);

  vtkOutput.add( *u );
  vtkOutput.add( *v );
  vtkOutput.add( *c_old );
  vtkOutput.add( *c );

  vtkOutput.write( maxLevel );

  for(uint_t i = 1; i <= timesteps; i++) {
    N.apply(*c_old, *c, maxLevel, hyteg::Inner, Replace);
    c->assign({1.0, -dt}, {c_old.get(), c.get()}, maxLevel, hyteg::Inner);

    vtkOutput.write( maxLevel, i );

    c_old.swap(c);
  }

  return EXIT_SUCCESS;
}
