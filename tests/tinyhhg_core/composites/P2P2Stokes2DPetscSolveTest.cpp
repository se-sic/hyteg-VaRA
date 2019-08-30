#include "core/Environment.h"
#include "core/logging/Logging.h"
#include "core/math/Random.h"
#include "core/timing/Timer.h"

#include "tinyhhg_core/VTKWriter.hpp"
#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/misc/ExactStencilWeights.hpp"
#include "tinyhhg_core/p2functionspace/P2ConstantOperator.hpp"
#include "tinyhhg_core/p2functionspace/P2Function.hpp"
#include "tinyhhg_core/petsc/PETScLUSolver.hpp"
#include "tinyhhg_core/petsc/PETScManager.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/FunctionProperties.hpp"
#include "tinyhhg_core/composites/P2P2StabilizedStokesOperator.hpp"

#ifndef HHG_BUILD_WITH_PETSC
WALBERLA_ABORT( "This test only works with PETSc enabled. Please enable it via -DHHG_BUILD_WITH_PETSC=ON" )
#endif

using walberla::real_t;
using walberla::uint_c;
using walberla::uint_t;

namespace hyteg {

void petscSolveTest( const uint_t & level, const MeshInfo & meshInfo, const real_t & resEps, const real_t & errEpsUSum, const real_t & errEpsP )
{
  PETScManager petscManager;

  SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );

  hyteg::loadbalancing::roundRobin( setupStorage );

  std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );
  writeDomainPartitioningVTK( storage, "../../output", "P2P2Stokes2DPetscSolve_Domain" );

  hyteg::P2P2StokesFunction< real_t >                      x( "x", storage, level, level );
  hyteg::P2P2StokesFunction< real_t >                      x_exact( "x_exact", storage, level, level );
  hyteg::P2P2StokesFunction< real_t >                      b( "b", storage, level, level );
  hyteg::P2P2StokesFunction< real_t >                      err( "err", storage, level, level );
  hyteg::P2P2StokesFunction< real_t >                      residuum( "res", storage, level, level );

  hyteg::P2P2StabilizedStokesOperator A( storage, level, level );

  std::function< real_t( const hyteg::Point3D& ) > exactU = []( const hyteg::Point3D& xx ) { return real_c(20) * xx[0] * std::pow( xx[1], 3.0 ); };
  std::function< real_t( const hyteg::Point3D& ) > exactV = []( const hyteg::Point3D& xx ) { return real_c(5) * std::pow( xx[0], 4.0 ) - real_c(5) * std::pow( xx[1], 4.0 ); };
  std::function< real_t( const hyteg::Point3D& ) > exactP = []( const hyteg::Point3D& xx ) { return real_c(60) * std::pow( xx[0], 2.0 ) * xx[1] - real_c(20) * std::pow( xx[1], 3.0 ); };
  std::function< real_t( const hyteg::Point3D& ) > zero =   []( const hyteg::Point3D&    ) { return real_c(0); };
  std::function< real_t( const hyteg::Point3D& ) > ones =   []( const hyteg::Point3D&    ) { return real_c(1); };

  walberla::math::seedRandomGenerator( 0 );
  std::function< real_t( const Point3D& ) > rand = []( const Point3D& ) { return walberla::math::realRandom( 0.0, 1.0 ); };

  b.u.interpolate( exactU, level, hyteg::DirichletBoundary );
  b.v.interpolate( exactV, level, hyteg::DirichletBoundary );

  x.u.interpolate( exactU, level, DirichletBoundary );
  x.v.interpolate( exactV, level, DirichletBoundary );

  x_exact.u.interpolate( exactU, level );
  x_exact.v.interpolate( exactV, level );
  x_exact.p.interpolate( exactP, level );

  VTKOutput vtkOutput("../../output", "P2P2Stokes2DPetscSolve", storage);
  vtkOutput.add( x.u );
  vtkOutput.add( x.v );
  vtkOutput.add( x.p );
  vtkOutput.add( x_exact.u );
  vtkOutput.add( x_exact.v );
  vtkOutput.add( x_exact.p );
  vtkOutput.add( err.u );
  vtkOutput.add( err.v );
  vtkOutput.add( err.p );
  vtkOutput.add( b.u );
  vtkOutput.add( b.v );
  vtkOutput.add( b.p );
  vtkOutput.write( level, 0 );

  uint_t localDoFs1 = hyteg::numberOfLocalDoFs< P2P2StokesFunctionTag >( *storage, level );
  uint_t globalDoFs1 = hyteg::numberOfGlobalDoFs< P2P2StokesFunctionTag >( *storage, level );

  WALBERLA_LOG_INFO( "localDoFs1: " << localDoFs1 << " globalDoFs1: " << globalDoFs1 );

  PETScLUSolver< P2P2StabilizedStokesOperator > solver_1( storage, level );

  walberla::WcTimer timer;
  solver_1.solve( A, x, b, level );
  timer.end();

  hyteg::p2function::projectMean( x.p, level );
  hyteg::p2function::projectMean( x_exact.p, level );

  WALBERLA_LOG_INFO_ON_ROOT( "time was: " << timer.last() );
  A.apply( x, residuum, level, hyteg::Inner );

  err.assign( {1.0, -1.0}, {x, x_exact}, level );

  real_t discr_l2_err_1_u = std::sqrt( err.u.dotGlobal( err.u, level ) / (real_t) globalDoFs1 );
  real_t discr_l2_err_1_v = std::sqrt( err.v.dotGlobal( err.v, level ) / (real_t) globalDoFs1 );
  real_t discr_l2_err_1_p = std::sqrt( err.p.dotGlobal( err.p, level ) / (real_t) globalDoFs1 );
  real_t residuum_l2_1  = std::sqrt( residuum.dotGlobal( residuum, level ) / (real_t) globalDoFs1 );

  WALBERLA_LOG_INFO_ON_ROOT( "discrete L2 error u = " << discr_l2_err_1_u );
  WALBERLA_LOG_INFO_ON_ROOT( "discrete L2 error v = " << discr_l2_err_1_v );
  WALBERLA_LOG_INFO_ON_ROOT( "discrete L2 error p = " << discr_l2_err_1_p );
  WALBERLA_LOG_INFO_ON_ROOT( "residuum 1 = " << residuum_l2_1 );

  vtkOutput.write( level, 1 );

  WALBERLA_CHECK_LESS( residuum_l2_1, resEps );
  WALBERLA_CHECK_LESS( discr_l2_err_1_u + discr_l2_err_1_v, errEpsUSum );
  WALBERLA_CHECK_LESS( discr_l2_err_1_p, errEpsP);
}

}

using namespace hyteg;

int main( int argc, char* argv[] )
{
  walberla::Environment walberlaEnv( argc, argv );
  walberla::MPIManager::instance()->useWorldComm();

  petscSolveTest( 5, hyteg::MeshInfo::fromGmshFile( "../../data/meshes/quad_center_at_origin_4el.msh" ), 6.0e-15, 0.008, 0.13 );

  return EXIT_SUCCESS;
}
