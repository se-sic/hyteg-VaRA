#include "core/Environment.h"
#include "core/logging/Logging.h"
#include "core/math/Random.h"
#include "core/timing/Timer.h"

#include "tinyhhg_core/VTKWriter.hpp"
#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/misc/ExactStencilWeights.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/FunctionProperties.hpp"
#include "tinyhhg_core/composites/P2P1TaylorHoodStokesOperator.hpp"

#include "tinyhhg_core/solvers/SchurCGSolver.hpp"

using walberla::real_t;
using walberla::uint_c;
using walberla::uint_t;

namespace hhg {

void P2P1SchurCGConvergenceTest( const uint_t & level, const MeshInfo & meshInfo, const real_t & errEps, const real_t & resEps )
{
  SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );

  hhg::loadbalancing::roundRobin( setupStorage );

  std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );
  writeDomainPartitioningVTK( storage, "../../output", "P2P1Stokes2DSchurCGConvergence_Domain" );

  hhg::P2P1TaylorHoodFunction< real_t >                      x( "x", storage, level, level );
  hhg::P2P1TaylorHoodFunction< real_t >                      x_exact( "x_exact", storage, level, level );
  hhg::P2P1TaylorHoodFunction< real_t >                      btmp( "btmp", storage, level, level );
  hhg::P2P1TaylorHoodFunction< real_t >                      b( "b", storage, level, level );
  hhg::P2P1TaylorHoodFunction< real_t >                      err( "err", storage, level, level );
  hhg::P2P1TaylorHoodFunction< real_t >                      residuum( "res", storage, level, level );

  hhg::P2P1TaylorHoodStokesOperator A( storage, level, level );

  std::function< real_t( const hhg::Point3D& ) > exactU = []( const hhg::Point3D& xx ) { return real_c(20) * xx[0] * xx[1] * xx[1] * xx[1]; };
  std::function< real_t( const hhg::Point3D& ) > exactV = []( const hhg::Point3D& xx ) { return real_c(5) * xx[0] * xx[0] * xx[0] * xx[0] - real_c(5) * xx[1] * xx[1] * xx[1] * xx[1]; };
  std::function< real_t( const hhg::Point3D& ) > exactP = []( const hhg::Point3D& xx ) { return real_c(60) * std::pow( xx[0], 2.0 ) * xx[1] - real_c(20) * std::pow( xx[1], 3.0 ); };
  std::function< real_t( const hhg::Point3D& ) > zero =   []( const hhg::Point3D&    ) { return real_c(0); };

  x.u.interpolate( exactU, level, hhg::DirichletBoundary );
  x.v.interpolate( exactV, level, hhg::DirichletBoundary );

  x_exact.u.interpolate( exactU, level );
  x_exact.v.interpolate( exactV, level );
  x_exact.p.interpolate( exactP, level );

  VTKOutput vtkOutput("../../output", "P2P1Stokes2DSchurCGConvergence", storage);
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

  uint_t localDoFs1 = hhg::numberOfLocalDoFs< P2P1TaylorHoodFunctionTag >( *storage, level );
  uint_t globalDoFs1 = hhg::numberOfGlobalDoFs< P2P1TaylorHoodFunctionTag >( *storage, level );

  WALBERLA_LOG_INFO( "localDoFs1: " << localDoFs1 << " globalDoFs1: " << globalDoFs1 );

  auto cgSolver = std::make_shared< CGSolver< P2ConstantLaplaceOperator > >( storage, level, level );
  SchurCGSolver< P2P1TaylorHoodStokesOperator > solver( storage, cgSolver, level, level, 1e-15, 10, Inner | NeumannBoundary );

  walberla::WcTimer timer;
  solver.solve( A, x, b, level );
  timer.end();

  // hhg::vertexdof::projectMean( x.p, err.p, level );
  // hhg::vertexdof::projectMean( x_exact.p, err.p, level );

  WALBERLA_LOG_INFO_ON_ROOT( "time was: " << timer.last() );
  A.apply( x, residuum, level, hhg::Inner | hhg::NeumannBoundary );

  err.assign( {1.0, -1.0}, {x, x_exact}, level );

  real_t discr_l2_err_1 = std::sqrt( err.dotGlobal( err, level ) / (real_t) globalDoFs1 );
  real_t residuum_l2_1  = std::sqrt( residuum.dotGlobal( residuum, level, Inner ) / (real_t) globalDoFs1 );

  WALBERLA_LOG_INFO_ON_ROOT( "discrete L2 error 1 = " << discr_l2_err_1 );
  WALBERLA_LOG_INFO_ON_ROOT( "residuum 1 = " << residuum_l2_1 );

  vtkOutput.write( level, 1 );

  WALBERLA_CHECK_LESS( residuum_l2_1, resEps );
  WALBERLA_CHECK_LESS( discr_l2_err_1, errEps );
}

}

using namespace hhg;

int main( int argc, char* argv[] )
{
  walberla::Environment walberlaEnv( argc, argv );
  walberla::MPIManager::instance()->useWorldComm();

  P2P1SchurCGConvergenceTest( 3, hhg::MeshInfo::fromGmshFile( "../../data/meshes/quad_center_at_origin_4el.msh" ), 0.2, 0.12 );

  return EXIT_SUCCESS;
}

