#include <tinyhhg_core/tinyhhg.hpp>

#include <fmt/format.h>

using walberla::real_t;

int main(int argc, char* argv[])
{
  walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
  walberla::MPIManager::instance()->useWorldComm();
  WALBERLA_LOG_INFO_ON_ROOT("TinyHHG default test");

  hhg::Mesh mesh("../data/meshes/tri_1el.msh");

  size_t minLevel = 2;
  size_t maxLevel = 5;

  std::function<real_t(const hhg::Point3D&)> expr = [](const hhg::Point3D&) { return 1.0; };
  hhg::P1FunctionOld u("u", mesh, minLevel, maxLevel);
  hhg::P1FunctionOld Lu("Lu", mesh, minLevel, maxLevel);

  u.interpolate(expr, maxLevel);
  hhg::P1LaplaceOperator L(mesh, minLevel, maxLevel);
  hhg::P1MassOperator L_gen(mesh, minLevel, maxLevel);

  hhg::VTKWriter({&u}, maxLevel, "../output", "test");
  return 0;
}
