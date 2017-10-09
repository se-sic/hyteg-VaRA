
#include <core/mpi/Environment.h>
#include <core/all.h>
#include "tinyhhg_core/dgfunctionspace/DGFunction.hpp"
#include "tinyhhg_core/tinyhhg.hpp"



using namespace hhg;

int main(int argc, char** argv){

  walberla::mpi::Environment MPIenv( argc, argv);
  walberla::MPIManager::instance()->useWorldComm();
  walberla::debug::enterTestMode();

  MeshInfo meshInfo = MeshInfo::fromGmshFile("../../data/meshes/quad_4el.msh");
  SetupPrimitiveStorage setupStorage(meshInfo, uint_c(walberla::mpi::MPIManager::instance()->numProcesses()));
  std::shared_ptr<PrimitiveStorage> storage = std::make_shared<PrimitiveStorage>(setupStorage);

  DGFunction();

}
