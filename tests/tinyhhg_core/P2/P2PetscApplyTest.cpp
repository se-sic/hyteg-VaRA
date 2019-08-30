
#include <numeric>

#include "core/DataTypes.h"
#include "core/math/Random.h"
#include "core/mpi/MPIManager.h"

#include "tinyhhg_core/FunctionTraits.hpp"
#include "tinyhhg_core/VTKWriter.hpp"
#include "tinyhhg_core/communication/Syncing.hpp"
#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/p2functionspace/P2ConstantOperator.hpp"
#include "tinyhhg_core/p2functionspace/P2Function.hpp"
#include "tinyhhg_core/petsc/PETScManager.hpp"
#include "tinyhhg_core/petsc/PETScSparseMatrix.hpp"
#include "tinyhhg_core/petsc/PETScVector.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"

using walberla::real_t;

namespace hyteg {

bool p2PetscApplyTest( const uint_t& level, const std::string& meshFile, const DoFType& location, const real_t& eps )
{
   WALBERLA_LOG_INFO_ON_ROOT( "level: " << level << ", mesh file: " << meshFile );

   const bool writeVTK = true;

   PETScManager petscManager;

   MeshInfo              meshInfo = hyteg::MeshInfo::fromGmshFile( meshFile );
   SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
   loadbalancing::roundRobin( setupStorage );
   std::shared_ptr< hyteg::PrimitiveStorage > storage = std::make_shared< hyteg::PrimitiveStorage >( setupStorage );

   writeDomainPartitioningVTK( storage, "../../output", "P2PetscApplyTestDomain" );

   P2Function< real_t >   src( "src", storage, level, level );
   P2Function< real_t >   hhgDst( "hhgDst", storage, level, level );
   P2Function< real_t >   petscDst( "petscDst", storage, level, level );
   P2Function< real_t >   err( "error", storage, level, level );
   P2Function< real_t >   ones( "ones", storage, level, level );
   P2Function< PetscInt > numerator( "numerator", storage, level, level );

   std::function< real_t( const hyteg::Point3D& ) > zero = []( const hyteg::Point3D& ) { return 0.0; };
   std::function< real_t( const hyteg::Point3D& ) > one  = []( const hyteg::Point3D& ) { return 1.0; };
   std::function< real_t( const hyteg::Point3D& ) > rand = []( const hyteg::Point3D& ) {
      return walberla::math::realRandom< real_t >();
   };
   std::function< real_t( const hyteg::Point3D& ) > srcFunction = []( const hyteg::Point3D& x ) {
      return x[0] * x[0] * x[0] * x[0] * std::sinh( x[1] ) * std::cos( x[2] );
   };

   src.interpolate( srcFunction, level, hyteg::All );
   hhgDst.interpolate( rand, level, location );
   petscDst.interpolate( rand, level, location );
   ones.interpolate( one, level, location );

   P2ConstantLaplaceOperator L( storage, level, level );

   numerator.enumerate( level );

   const uint_t globalDoFs = hyteg::numberOfGlobalDoFs< hyteg::P2FunctionTag >( *storage, level );
   const uint_t localDoFs  = hyteg::numberOfLocalDoFs< hyteg::P2FunctionTag >( *storage, level );

   WALBERLA_LOG_INFO_ON_ROOT( "Global DoFs: " << globalDoFs );

   // HyTeG apply
   L.apply( src, hhgDst, level, location );

   // PETSc apply
   PETScVector< real_t, P2Function >                          srcPetscVec( localDoFs );
   PETScVector< real_t, P2Function >                          dstPetscVec( localDoFs );
   PETScSparseMatrix< P2ConstantLaplaceOperator, P2Function > petscMatrix( localDoFs, globalDoFs );

   srcPetscVec.createVectorFromFunction( src, numerator, level, All );
   dstPetscVec.createVectorFromFunction( petscDst, numerator, level, All );
   petscMatrix.createMatrixFromFunction( L, level, numerator, All );

   WALBERLA_CHECK( petscMatrix.isSymmetric() );

   MatMult( petscMatrix.get(), srcPetscVec.get(), dstPetscVec.get() );

   dstPetscVec.createFunctionFromVector( petscDst, numerator, level, location );

   // compare
   err.assign( {1.0, -1.0}, {hhgDst, petscDst}, level, location );
   const auto maxError = err.getMaxMagnitude( level );

   WALBERLA_LOG_INFO_ON_ROOT( "Error max Magnitude = " << maxError << " eps: " << eps );

   if ( writeVTK )
   {
      VTKOutput vtkOutput( "../../output", "P2PetscApplyTest", storage );
      vtkOutput.add( src );
      vtkOutput.add( hhgDst );
      vtkOutput.add( petscDst );
      vtkOutput.add( err );
      vtkOutput.write( level, 0 );
   }

   if( maxError > eps ){
     WALBERLA_LOG_INFO_ON_ROOT( "TEST FAILED!" );
     return false;
   } else {
     return true;
   }
}

} // namespace hyteg

int main( int argc, char* argv[] )
{
   walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
   walberla::MPIManager::instance()->useWorldComm();

   bool succeeded = true;

   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/quad_4el.msh", hyteg::All, 5.0e-15 );
   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/annulus_coarse.msh", hyteg::All, 1.7e-13 );
   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/3D/tet_1el.msh", hyteg::Inner, 1.0e-16 );
   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/3D/pyramid_2el.msh", hyteg::Inner, 9.6e-16 );
   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/3D/pyramid_4el.msh", hyteg::Inner, 1.5e-15 );
   succeeded &= hyteg::p2PetscApplyTest( 3, "../../data/meshes/3D/regular_octahedron_8el.msh", hyteg::Inner, 3.2e-15 );
   succeeded &= hyteg::p2PetscApplyTest( 2, "../../data/meshes/3D/cube_24el.msh", hyteg::All, 3.1e-15 );

   WALBERLA_CHECK( succeeded, "One of the tests failed" )

   return EXIT_SUCCESS;
}
