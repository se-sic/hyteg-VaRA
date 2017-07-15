#include <core/timing/Timer.h>
#include <tinyhhg_core/tinyhhg.hpp>
#include <fmt/format.h>

using walberla::real_t;

int main(int argc, char* argv[])
{
  walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
  walberla::MPIManager::instance()->useWorldComm();
  WALBERLA_LOG_INFO_ON_ROOT("TinyHHG CG Test\n");

  hhg::Mesh mesh("../data/meshes/quad_4el.msh");

  size_t minLevel = 2;
  size_t maxLevel = 2;
  size_t maxiter = 10000;

  hhg::P1Function r("r", mesh, minLevel, maxLevel);
  hhg::P1Function f("f", mesh, minLevel, maxLevel);
  hhg::P1Function u("u", mesh, minLevel, maxLevel);
  hhg::P1Function u_exact("u_exact", mesh, minLevel, maxLevel);
  hhg::P1Function err("err", mesh, minLevel, maxLevel);
  hhg::P1Function npoints_helper("npoints_helper", mesh, minLevel, maxLevel);

  hhg::P1LaplaceOperator L(mesh, minLevel, maxLevel);
  hhg::P1MassOperator M(mesh, minLevel, maxLevel);

  std::function<real_t(const hhg::Point3D&)> exact = [](const hhg::Point3D& xx) { return 1.0 + 2*xx[0] + 3*xx[1] + xx[0]*xx[1] + xx[0]*xx[0] + xx[1]*xx[1]; };
  std::function<real_t(const hhg::Point3D&)> rhs   = [](const hhg::Point3D&) { return -4.0; };
  std::function<real_t(const hhg::Point3D&)> ones  = [](const hhg::Point3D&) { return 1.0; };

  u.interpolate(exact, maxLevel, hhg::DirichletBoundary);
  npoints_helper.interpolate(rhs, maxLevel);
  M.apply(npoints_helper, f, maxLevel, hhg::All);
  u_exact.interpolate(exact, maxLevel);

  auto solver = hhg::CGSolver<hhg::P1Function, hhg::P1LaplaceOperator>(mesh, minLevel, maxLevel);
  walberla::WcTimer timer;
  solver.solve(L, u, f, r, maxLevel, 1e-16, maxiter, hhg::Inner, true);
  timer.end();
  fmt::printf("time was: %e\n",timer.last());
  err.assign({1.0, -1.0}, {&u, &u_exact}, maxLevel);

  npoints_helper.interpolate(ones, maxLevel);
  real_t npoints = npoints_helper.dot(npoints_helper, maxLevel);

  real_t discr_l2_err = std::sqrt(err.dot(err, maxLevel) / npoints);

  WALBERLA_LOG_INFO_ON_ROOT("discrete L2 error = " << discr_l2_err);

  hhg::VTKWriter({ &u, &u_exact, &f, &r, &err }, maxLevel, "../output", "test");
  return 0;
}
