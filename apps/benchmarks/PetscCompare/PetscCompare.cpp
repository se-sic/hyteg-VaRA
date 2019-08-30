
#include "core/DataTypes.h"
#include "core/Environment.h"
#include "core/config/Config.h"
#include "core/mpi/MPIManager.h"
#include "core/timing/TimingJSON.h"
#include "core/math/Constants.h"

#include "tinyhhg_core/FunctionProperties.hpp"
#include "tinyhhg_core/LikwidWrapper.hpp"
#include "tinyhhg_core/VTKWriter.hpp"
#include "tinyhhg_core/communication/Syncing.hpp"
#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/p1functionspace/P1ConstantOperator.hpp"
#include "tinyhhg_core/p1functionspace/P1Function.hpp"
#include "tinyhhg_core/p1functionspace/P1Petsc.hpp"
#include "tinyhhg_core/petsc/PETScLUSolver.hpp"
#include "tinyhhg_core/petsc/PETScManager.hpp"
#include "tinyhhg_core/petsc/PETScSparseMatrix.hpp"
#include "tinyhhg_core/petsc/PETScVector.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"

using walberla::real_t;
using namespace hyteg;

int main( int argc, char* argv[] )
{
   LIKWID_MARKER_INIT;

   walberla::Environment env( argc, argv );
   walberla::MPIManager::instance()->useWorldComm();

   LIKWID_MARKER_THREADINIT;

   PETScManager petscManager;

   auto cfg = std::make_shared< walberla::config::Config >();
   if( env.config() == nullptr )
   {
      auto defaultFile = "./PetscCompare.prm";
      WALBERLA_LOG_PROGRESS_ON_ROOT( "No Parameter file given loading default parameter file: " << defaultFile );
      cfg->readParameterFile( defaultFile );
   } else
   {
      cfg = env.config();
   }
   const walberla::Config::BlockHandle mainConf = cfg->getBlock( "Parameters" );
   const uint_t                        level    = mainConf.getParameter< uint_t >( "level" );

   std::shared_ptr< hyteg::MeshInfo > meshInfo;
   if( mainConf.getParameter< bool >( "useMeshFile" ) )
   {
      std::string meshFileName = mainConf.getParameter< std::string >( "mesh" );
      meshInfo                 = std::make_shared< hyteg::MeshInfo >( hyteg::MeshInfo::fromGmshFile( meshFileName ) );
   } else
   {
      uint_t numberOfFaces = mainConf.getParameter< uint_t >( "numberOfFaces" );
      if( mainConf.getParameter< bool >( "facesTimesProcs" ) )
      {
         meshInfo = std::make_shared< hyteg::MeshInfo >(
             hyteg::MeshInfo::meshFaceChain( numberOfFaces * uint_c( walberla::MPIManager::instance()->numProcesses() ) ) );
      }
   }

   hyteg::SetupPrimitiveStorage setupStorage( *meshInfo,
                                            walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

   uint_t numberOfFaces = setupStorage.getNumberOfFaces();

   hyteg::loadbalancing::roundRobin( setupStorage );

   std::function< real_t( const hyteg::Point3D& ) > ones  = []( const hyteg::Point3D& ) { return 1.0; };
   std::function< real_t( const hyteg::Point3D& ) > exact = []( const hyteg::Point3D& xx ) {
      //return 5.0;
      return std::sin( walberla::math::pi * xx[0] ) + std::cos( walberla::math::pi * xx[1] );
      //return ( real_c(std::rand()) / real_c(RAND_MAX));
   };

   std::shared_ptr< walberla::WcTimingTree > timingTree( new walberla::WcTimingTree() );

   std::shared_ptr< hyteg::PrimitiveStorage > storage = std::make_shared< hyteg::PrimitiveStorage >( setupStorage, timingTree );

   if( mainConf.getParameter< bool >( "writeDomain" ) )
   {
      hyteg::writeDomainPartitioningVTK( storage, "./output", "domain" );
   }

   hyteg::P1Function< double > oneFunc( "x", storage, level, level );
   oneFunc.interpolate( ones, level );
   hyteg::P1Function< double > x( "x", storage, level, level );
   hyteg::P1Function< double > y( "y", storage, level, level );
   hyteg::P1Function< double > z( "z", storage, level, level );
   hyteg::P1Function< double > diff( "diff", storage, level, level );
   x.interpolate( exact, level, hyteg::Inner );
   //hyteg::communication::syncFunctionBetweenPrimitives(x,level);
   hyteg::P1Function< PetscInt >    numerator( "numerator", storage, level, level );
   hyteg::P1ConstantLaplaceOperator mass( storage, level, level );

   //  for (const auto & faceIT : storage->getFaces()) {
   //    auto facePtr = faceIT.second->getData( mass.getFaceStencilID() )->getPointer( level );
   //    facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_C)] = 1.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_S)] = 0.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_SE)] = 0.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_E)] = 0.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_N)] = 0.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_NW)] = 0.0;
   //      facePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_W)] = 0.0;
   //  }

   //  for (const auto & edgeIT : storage->getEdges()) {
   //    auto edgePtr = edgeIT.second->getData( mass.getEdgeStencilID() )->getPointer( level );
   //    edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_C)] = 1.0;
   //      edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_S)] = 0.0;
   //      edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_SE)] = 0.0;
   //      edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_E)] = 0.0;
   //      edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_W)] = 0.0;
   //      if(edgeIT.second->getNumHigherDimNeighbors() == 2){
   //         edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_N)] = 0.0;
   //         edgePtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_NW)] = 0.0;
   //      }
   //  }

   //  for (const auto & vertexIT : storage->getVertices()) {
   //    auto vertexPtr = vertexIT.second->getData( mass.getVertexStencilID() )->getPointer( level );
   //    vertexPtr[vertexdof::stencilIndexFromVertex(hyteg::stencilDirection::VERTEX_C)] = 1.0;
   //  }

   const uint_t localDoFs = hyteg::numberOfLocalDoFs< hyteg::P1FunctionTag >( *storage, level );
   const uint_t totalDoFs = numberOfGlobalDoFs< hyteg::P1FunctionTag >( *storage, level );

   WALBERLA_LOG_INFO_ON_ROOT( "totalDoFs: " << totalDoFs );
   WALBERLA_LOG_INFO( "localDoFs: " << localDoFs << " totalDoFs: " << totalDoFs );

   //   WALBERLA_CRITICAL_SECTION_START
   //  for (auto &edgeIT : storage->getEdges()) {
   //    auto edge = edgeIT.second;
   //    hyteg::vertexdof::macroedge::printFunctionMemory< PetscInt >(level, *edge, numerator.getEdgeDataID());
   //  }
   //   WALBERLA_CRITICAL_SECTION_END

   numerator.enumerate( level );

   LIKWID_MARKER_START( "PETSc-setup" );
   hyteg::PETScSparseMatrix< hyteg::P1ConstantLaplaceOperator, hyteg::P1Function > matPetsc( localDoFs, totalDoFs );
   matPetsc.createMatrixFromFunction( mass, level, numerator, hyteg::Inner );
   hyteg::PETScVector< real_t, hyteg::P1Function > vecPetsc( localDoFs );
   vecPetsc.createVectorFromFunction( x, numerator, level, hyteg::Inner );
   hyteg::PETScVector< real_t, hyteg::P1Function > dstvecPetsc( localDoFs );
   LIKWID_MARKER_STOP( "PETSc-setup" );

   walberla::WcTimer timer;

   timer.reset();
   LIKWID_MARKER_START( "HyTeG-apply" );
   mass.apply( x, y, level, hyteg::Inner );
   LIKWID_MARKER_STOP( "HyTeG-apply" );
   timer.end();
   double hyteg_apply = timer.last();
   WALBERLA_LOG_INFO_ON_ROOT( "HyTeG apply runtime: " << hyteg_apply );

   //matPetsc.print("./output/petsc_matrix");
   //vecPetsc.print("../output/vector0.vec");
   PetscErrorCode ierr;

   timer.reset();
   LIKWID_MARKER_START( "Petsc-MatMult" );
   ierr = MatMult( matPetsc.get(), vecPetsc.get(), dstvecPetsc.get() );
   LIKWID_MARKER_STOP( "Petsc-MatMult" );
   timer.end();
   double petsc_matmult = timer.last();
   WALBERLA_LOG_INFO_ON_ROOT( "Petsc MatMult runtime: " << petsc_matmult );
   CHKERRQ( ierr );

   dstvecPetsc.createFunctionFromVector( z, numerator, level, hyteg::Inner );

   //dstvecPetsc.print("../output/vector1.vec");

   diff.assign( {1.0, -1.0}, {z, y}, level, hyteg::All );

   if( mainConf.getParameter< bool >( "VTKOutput" ) )
   {
      WALBERLA_LOG_INFO_ON_ROOT( "writing VTK output" );
      hyteg::VTKOutput vtkOutput("./output", "petscCompare", storage);
      vtkOutput.add( x );
      vtkOutput.add( z );
      vtkOutput.add( y );
      vtkOutput.add( diff );
      vtkOutput.write( level );
   }

   walberla::WcTimingTree tt  = timingTree->getReduced();
   auto                   tt2 = tt.getCopyWithRemainder();

   if( mainConf.getParameter< bool >( "printTiming" ) )
   {
      WALBERLA_LOG_INFO_ON_ROOT( tt2 );
   }

   if( mainConf.getParameter< bool >( "writeJSON" ) )
   {
      nlohmann::json ttjson = nlohmann::json( tt2 );
      std::ofstream  o( "PetscCompareOutput.json" );
      o << ttjson;
      o.close();
   }

   WALBERLA_CHECK_FLOAT_EQUAL( y.dotGlobal( oneFunc, level, hyteg::Inner ), z.dotGlobal( oneFunc, level, hyteg::Inner ) );
   WALBERLA_LOG_INFO_ON_ROOT( std::scientific << " | " << numberOfFaces << " | " << level << " | " << totalDoFs << " | "
                                              << walberla::MPIManager::instance()->numProcesses() << " | " << hyteg_apply << " | "
                                              << petsc_matmult << " | " );

   LIKWID_MARKER_CLOSE;
}
