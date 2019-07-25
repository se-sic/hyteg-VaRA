#include "core/DataTypes.h"
#include "core/Environment.h"
#include "core/mpi/MPIManager.h"
#include "core/timing/Timer.h"
#include "core/math/Constants.h"

#include "tinyhhg_core/composites/P2P1TaylorHoodFunction.hpp"
#include "tinyhhg_core/composites/P2P1TaylorHoodStokesOperator.hpp"
#include "tinyhhg_core/VTKWriter.hpp"

#include "tinyhhg_core/FunctionProperties.hpp"
#include "tinyhhg_core/composites/P1StokesFunction.hpp"
#include "tinyhhg_core/composites/P1StokesOperator.hpp"
#include "tinyhhg_core/p1functionspace/P1ConstantOperator.hpp"
#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/Visualization.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/DistributedBalancer.hpp"
#include "tinyhhg_core/solvers/MinresSolver.hpp"
#include "tinyhhg_core/solvers/UzawaSmoother.hpp"
#include "tinyhhg_core/solvers/EmptySolver.hpp"
#include "tinyhhg_core/solvers/GeometricMultigridSolver.hpp"
#include "tinyhhg_core/solvers/GaussSeidelSmoother.hpp"
#include "tinyhhg_core/solvers/CGSolver.hpp"
#include "tinyhhg_core/solvers/preconditioners/StokesBlockDiagonalPreconditioner.hpp"
#include "tinyhhg_core/solvers/preconditioners/IdentityPreconditioner.hpp"
#include "tinyhhg_core/gridtransferoperators/P2P1StokesToP2P1StokesProlongation.hpp"
#include "tinyhhg_core/gridtransferoperators/P2P1StokesToP2P1StokesRestriction.hpp"
#include "tinyhhg_core/gridtransferoperators/P1P1StokesToP1P1StokesProlongation.hpp"
#include "tinyhhg_core/gridtransferoperators/P1P1StokesToP1P1StokesRestriction.hpp"
#include "tinyhhg_core/types/pointnd.hpp"
#include "tinyhhg_core/FunctionProperties.hpp"

#include "tinyhhg_core/petsc/PETScManager.hpp"
#include "tinyhhg_core/petsc/PETScLUSolver.hpp"
#include "tinyhhg_core/petsc/PETScVector.hpp"
#include "tinyhhg_core/petsc/PETScWrapper.hpp"

using walberla::real_t;

namespace hhg{

enum DiscretizationType
{
    P1P1,
    TaylorHood
};

enum SolverType
{
    PETSC,
    MIN_RES,
    UZAWA,
    EMPTY
};

const static std::map< std::string, DiscretizationType > strToDiscretizationType =
{
  { "P1P1",       P1P1 },
  { "TaylorHood", TaylorHood }
};

const static std::map< std::string, SolverType > strToSolverType =
{
  { "petsc",  PETSC },
  { "minres", MIN_RES },
  { "uzawa",  UZAWA },
  { "empty",  EMPTY },
};

template< template< typename ValueType > class Function_T, typename Operator_T  >
class PetscSolver : public Solver< Operator_T >
{
#ifdef HHG_BUILD_WITH_PETSC
public:
    PetscSolver( const std::shared_ptr< hhg::PrimitiveStorage >         & storage,
                 const uint_t                                           & minLevel,
                 const uint_t                                           & maxLevel,
                 const std::function< real_t ( const hhg::Point3D & ) > & velocityUBC,
                 const std::function< real_t ( const hhg::Point3D & ) > & velocityVBC) :
      storage_( storage ), velocityUBC_( velocityUBC ), velocityVBC_( velocityVBC )
    {
      tmpRHS_ = std::make_shared< Function_T< real_t > >( "tmpRHS", storage, minLevel, maxLevel );
      numerator_ = std::make_shared< Function_T< PetscInt > >( "numerator", storage, minLevel, maxLevel );
    }

    void solve( const Operator_T & A,
                const Function_T< real_t > & x,
                const Function_T< real_t > & b,
                size_t level) {

       PETScManager petscManager;
       tmpRHS_->assign( {1.0}, {b}, level, DoFType::Inner | NeumannBoundary );

       //tmpRHS_->u.interpolate(velocityUBC_, level, hhg::DirichletBoundary);
       //tmpRHS_->v.interpolate(velocityVBC_, level, hhg::DirichletBoundary);
       tmpRHS_->u.assign( {1.0}, {x.u}, level, hhg::DirichletBoundary);
       tmpRHS_->v.assign( {1.0}, {x.v}, level, hhg::DirichletBoundary);
       PETScLUSolver< Operator_T> solver( storage_, level );
       solver.solve(A, x, *tmpRHS_, level );
    }

private:
   std::shared_ptr< Function_T< PetscInt > > numerator_;
   std::shared_ptr< Function_T< real_t > > tmpRHS_;
   std::shared_ptr< PrimitiveStorage > storage_;
   std::function< real_t ( const hhg::Point3D & ) > velocityUBC_;
   std::function< real_t ( const hhg::Point3D & ) > velocityVBC_;
#else
public:
    PetscSolver( const std::shared_ptr< hhg::PrimitiveStorage >         &,
                 const uint_t                                           &,
                 const uint_t                                           &,
                 const std::function< real_t ( const hhg::Point3D & ) > &,
                 const std::function< real_t ( const hhg::Point3D & ) > &)
    {}

    void solve(const Operator_T &,
               const Function_T< real_t > &,
               const Function_T< real_t > &,
               uint_t) override
    {
             WALBERLA_ABORT( "Cannot use PETSc solver if PETSc was not built..." );
    }
#endif

};


void keepMeshBoundaries( SetupPrimitiveStorage & )
{
}

void setAllBoundariesDirichlet( SetupPrimitiveStorage & setupStorage )
{
  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
}

void setRightBFSBoundaryNeumannPoiseuille( SetupPrimitiveStorage & setupStorage )
{
  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );

  const real_t eps = 0.001;

  for ( const auto & it : setupStorage.getVertices() )
  {
    if ( std::fabs( it.second->getCoordinates()[0] - 1.0 ) < eps
         && it.second->getCoordinates()[1] > -1.0 + eps
         && it.second->getCoordinates()[1] <  1.0 - eps )
    {
      setupStorage.setMeshBoundaryFlag( it.first, 2 );
    }
  }

  for ( const auto & it : setupStorage.getEdges() )
  {
    const auto edgeCoordinates = it.second->getCoordinates();
    if ( std::fabs( edgeCoordinates[0][0] - 1.0 ) < eps && std::fabs( edgeCoordinates[1][0] - 1.0 ) < eps )
    {
      setupStorage.setMeshBoundaryFlag( it.first, 2 );
    }
  }
}

void setRightBFSBoundaryNeumannBFS( SetupPrimitiveStorage & setupStorage )
{
  setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );

  const real_t eps = 0.001;

  for ( const auto & it : setupStorage.getVertices() )
  {
    if (    std::fabs( it.second->getCoordinates()[0] - 2.0 ) < eps
         && it.second->getCoordinates()[1] > eps
         && it.second->getCoordinates()[1] < 1.0 - eps )
    {
      setupStorage.setMeshBoundaryFlag( it.first, 2 );
    }
  }

  for ( const auto & it : setupStorage.getEdges() )
  {
    const auto edgeCoordinates = it.second->getCoordinates();
    if ( std::fabs( edgeCoordinates[0][0] - 2.0 ) < eps && std::fabs( edgeCoordinates[1][0] - 2.0 ) < eps )
    {
      setupStorage.setMeshBoundaryFlag( it.first, 2 );
    }
  }
}



template< template< typename ValueType > class StokesFunction_T, class StokesOperator_T, class RestrictionOperator_T, class ProlongationOperator_T, class VelocityMassMatrix_T >
void run( const MeshInfo & meshInfo, const uint_t & minLevel, const uint_t & maxLevel,
          const SolverType & solverType, const SolverType & coarseGridSolver, const uint_t & numMGCycles,
          const uint_t & preSmooth,
          const uint_t & postSmooth,
          const uint_t & incrementSmooth,
          const real_t & uzawaRelaxParam,
          const real_t targetResidual, const uint_t & maxIterations,
          const std::function< void( SetupPrimitiveStorage & ) > setBCFlags,
          const std::function< real_t( const Point3D & ) > setUVelocityBC,
          const std::function< real_t( const Point3D & ) > setVVelocityBC,
          const std::function< real_t( const Point3D & ) > setUVelocityRHS,
          const std::function< real_t( const Point3D & ) > setVVelocityRHS,
          const bool & compareWithAnalyticalSolution,
          const std::function< real_t( const Point3D & ) > & solutionU,
          const std::function< real_t( const Point3D & ) > & solutionV,
          const std::function< real_t( const Point3D & ) > & solutionP,
          const bool & rescalePressure,
          const bool & printTimer )
{
  typedef typename StokesFunction_T< real_t >::Tag StokesFunctionTag_T;

  std::shared_ptr< walberla::WcTimingTree > timingTree( new walberla::WcTimingTree() );
  timingTree->start( "Complete app" );

  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Setting up storage..." );
  hhg::SetupPrimitiveStorage setupStorage( meshInfo, walberla::uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
  setBCFlags( setupStorage );

  std::shared_ptr< hhg::PrimitiveStorage > storage = std::make_shared< hhg::PrimitiveStorage >( setupStorage, timingTree );

#ifdef WALBERLA_BUILD_WITH_PARMETIS
  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Load balancing with ParMetis..." );
  hhg::loadbalancing::distributed::parmetis( *storage );
#endif

  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Writing domain partitioning..." );
  hhg::writeDomainPartitioningVTK( storage, "../output", "StokesFlowSolverComparison_domain" );

  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Allocating functions..." );
  StokesFunction_T< real_t > r( "r", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > f( "f", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > u( "u", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > Au( "Au", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > error( "error", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > exactSolution( "exactSolution", storage, minLevel, maxLevel );
  StokesFunction_T< real_t > tmp( "tmp", storage, minLevel, maxLevel );

  StokesOperator_T L( storage, minLevel, maxLevel );
  VelocityMassMatrix_T MassVelocity( storage, minLevel, maxLevel );

  std::function< real_t( const hhg::Point3D& ) > rhs  = []( const hhg::Point3D& ) { return 0.0; };
  std::function< real_t( const hhg::Point3D& ) > zero = []( const hhg::Point3D& ) { return 0.0; };
  std::function< real_t( const hhg::Point3D& ) > ones = []( const hhg::Point3D& ) { return 1.0; };

  exactSolution.u.interpolate( solutionU, maxLevel, DoFType::All );
  exactSolution.v.interpolate( solutionV, maxLevel, DoFType::All );
  exactSolution.p.interpolate( solutionP, maxLevel, DoFType::All );

  ////////////////////////
  // Setting up solvers //
  ////////////////////////

  // Velocity block solver
  typedef hhg::CGSolver< typename StokesOperator_T::VelocityOperator_T >                 VelocityCGSolver_T;
  typedef hhg::GeometricMultigridSolver< typename StokesOperator_T::VelocityOperator_T > VelocityGMGSolver_T;
  auto velocityRestriction  = std::make_shared< typename RestrictionOperator_T::VelocityRestriction_T >();
  auto velocityProlongation = std::make_shared< typename ProlongationOperator_T::VelocityProlongation_T >();
  auto velocityCGSolver     = std::make_shared< VelocityCGSolver_T >( storage, minLevel, maxLevel );
  auto gsSmoother           = std::make_shared< hhg::GaussSeidelSmoother< typename StokesOperator_T::VelocityOperator_T > >();
  auto velocityGMGSolver    = std::make_shared< VelocityGMGSolver_T >( storage,
                                                                    gsSmoother,
                                                                    velocityCGSolver,
                                                                    velocityRestriction,
                                                                    velocityProlongation,
                                                                    minLevel,
                                                                    maxLevel,
                                                                    preSmooth,
                                                                    postSmooth );

  // Empty
  typedef EmptySolver< StokesOperator_T > EmptySolver_T;
  auto emptySolver = std::shared_ptr< EmptySolver_T >();

  // MinRes (preconditioned)
  typedef hhg::StokesBlockDiagonalPreconditioner< StokesOperator_T,
                                                  hhg::P1LumpedInvMassOperator > Preconditioner_T;
  auto preconditioner = std::make_shared< Preconditioner_T >( storage, minLevel, maxLevel, numMGCycles, velocityGMGSolver );
  typedef hhg::MinResSolver< StokesOperator_T > PreconditionedMinResSolver_T;
  auto preconditionedMinResSolver = PreconditionedMinResSolver_T( storage, minLevel, maxLevel, maxIterations, targetResidual, preconditioner );

  // MinRes (only pressure preconditioner)
  auto preconditionerOnlyPressure = std::make_shared< Preconditioner_T >( storage, minLevel, maxLevel, 0 );
  auto minResSolver = std::make_shared< PreconditionedMinResSolver_T >( storage, minLevel, maxLevel, maxIterations, targetResidual, preconditionerOnlyPressure );

  // PETSc
  typedef PetscSolver< StokesFunction_T, StokesOperator_T > PetscSolver_T;
  auto petscSolver = std::make_shared< PetscSolver_T >( storage, minLevel, maxLevel, setUVelocityBC, setVVelocityBC );

  // Laplace solver
  typedef hhg::CGSolver< typename StokesOperator_T::VelocityOperator_T > LaplaceSolver_T;
  LaplaceSolver_T laplaceSolver( storage, minLevel, maxLevel );

  /////////////////////////
  // Boundary conditions //
  /////////////////////////

  u.u.interpolate( setUVelocityBC, maxLevel, hhg::DirichletBoundary );
  u.v.interpolate( setVVelocityBC, maxLevel, hhg::DirichletBoundary );


  /////////////////////
  // Right-hand side //
  /////////////////////

  tmp.u.interpolate( setUVelocityRHS, maxLevel, hhg::All );
  tmp.v.interpolate( setVVelocityRHS, maxLevel, hhg::All );
  MassVelocity.apply( tmp.u, f.u, maxLevel, hhg::All );
  MassVelocity.apply( tmp.v, f.v, maxLevel, hhg::All );
  // f.u.interpolate( setUVelocityRHS, maxLevel, hhg::All );
  // f.v.interpolate( setVVelocityRHS, maxLevel, hhg::All );


  /////////
  // VTK //
  /////////

  hhg::VTKOutput vtkOutput("../output", "StokesFlowSolverComparison", storage);

  vtkOutput.add( r.u );
  vtkOutput.add( r.v );
  vtkOutput.add( r.p );

  vtkOutput.add( f.u );
  vtkOutput.add( f.v );
  vtkOutput.add( f.p );

  vtkOutput.add( u.u );
  vtkOutput.add( u.v );
  vtkOutput.add( u.p );

  if ( compareWithAnalyticalSolution )
  {
    vtkOutput.add( exactSolution.u );
    vtkOutput.add( exactSolution.v );
    vtkOutput.add( exactSolution.p );

    vtkOutput.add( error.u );
    vtkOutput.add( error.v );
    vtkOutput.add( error.p );
  }

  ////////////////////////////////
  // Initial residual and error //
  ////////////////////////////////

  L.apply( u, Au, maxLevel, hhg::Inner | hhg::NeumannBoundary );
  r.assign( {1.0, -1.0}, {f, Au}, maxLevel, hhg::Inner | hhg::NeumannBoundary );
  real_t currentResidualL2 = std::sqrt( r.dotGlobal( r, maxLevel, hhg::Inner | hhg::NeumannBoundary ) ) / real_c(hhg::numberOfGlobalDoFs< StokesFunctionTag_T >( *storage, maxLevel ));
  real_t lastResidualL2    = currentResidualL2;
  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Initial residual: " << currentResidualL2 );

  if ( compareWithAnalyticalSolution )
  {
    error.assign( {1.0, -1.0}, {u, exactSolution}, maxLevel, DoFType::All );
    const real_t currentErrorL2 = std::sqrt( error.dotGlobal( error, maxLevel, hhg::All ) ) / real_c(hhg::numberOfGlobalDoFs< typename StokesFunction_T< real_t >::Tag >( *storage, maxLevel ));
    WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Initial error: " << currentErrorL2 );
  }

  /////////////////////////////////////
  // Solver selection and simulation //
  /////////////////////////////////////

  switch( solverType )
  {
    case EMPTY:
      WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid solver type!" );
      break;
    case PETSC:
    {
#ifdef HHG_BUILD_WITH_PETSC
      vtkOutput.write( maxLevel, 0 );
      WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Solving with PETSc..." );
      petscSolver->solve( L, u, f, maxLevel);

      if ( rescalePressure )
      {
        const real_t minPressure = u.p.getMinValue( maxLevel, DoFType::All );
        u.p.add( -minPressure, maxLevel, DoFType::All );
      }

      if ( compareWithAnalyticalSolution )
      {
        error.assign( {1.0, -1.0}, {&u, &exactSolution}, maxLevel, DoFType::All );
      }

      vtkOutput.write( maxLevel, 1 );
#else
      WALBERLA_ABORT( "[StokesFlowSolverComparison] HHG was not built with PETSc. Cannot invoke PETSC solver" );
#endif
      break;
    }
    case MIN_RES:
    {
      vtkOutput.write( maxLevel, 0 );
      WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Solving with MinRes..." );
      preconditionedMinResSolver.solve( L, u, f, maxLevel );

      if ( rescalePressure )
      {
        const real_t minPressure = u.p.getMinValue( maxLevel, DoFType::All );
        u.p.add( -minPressure, maxLevel, DoFType::All );
      }

      if ( compareWithAnalyticalSolution )
      {
        error.assign( { 1.0, -1.0 }, { u, exactSolution }, maxLevel, DoFType::All );
      }

      vtkOutput.write( maxLevel, 1 );
      break;
    }
    case UZAWA:
    {
      WALBERLA_LOG_WARNING_ON_ROOT( "### Uzawa solvers (for any discretization) are not working correctly! ###" );
      switch ( coarseGridSolver )
      {
        case EMPTY:
        {
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Solving with multigrid (Uzawa + no coarse grid solver)..." )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] iteration | residual (L2) | convergence rate |     time " )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] ----------+---------------+------------------+--------- " )

           auto restrictionOperator = std::make_shared< RestrictionOperator_T >();
           auto prolongationOperator = std::make_shared< ProlongationOperator_T >();
           auto uzawaSmoother = std::make_shared< hhg::UzawaSmoother< StokesOperator_T > >(
               storage, minLevel, maxLevel, storage->hasGlobalCells(), uzawaRelaxParam );

           auto solver = hhg::GeometricMultigridSolver< StokesOperator_T >( storage,
                                                                            uzawaSmoother,
                                                                            emptySolver,
                                                                            restrictionOperator,
                                                                            prolongationOperator,
                                                                            minLevel,
                                                                            maxLevel,
                                                                            preSmooth,
                                                                            postSmooth,
                                                                            incrementSmooth );

           walberla::WcTimer timer;
           for( uint_t mgIteration = 0; mgIteration < numMGCycles; mgIteration++ )
           {
              vtkOutput.write( maxLevel, mgIteration );

              timer.start();
              solver.solve( L, u, f, maxLevel );
              timer.end();

              if( rescalePressure )
              {
                 const real_t minPressure = u.p.getMinValue( maxLevel, DoFType::All );
                 u.p.add( -minPressure, maxLevel, DoFType::All );
              }

              lastResidualL2 = currentResidualL2;
              L.apply( u, Au, maxLevel, hhg::Inner | hhg::NeumannBoundary );
              r.assign( {1.0, -1.0}, {f, Au}, maxLevel, hhg::Inner | hhg::NeumannBoundary );
              currentResidualL2 = std::sqrt( r.dotGlobal( r, maxLevel, hhg::Inner | hhg::NeumannBoundary ) ) /
                                  real_c( hhg::numberOfGlobalDoFs< StokesFunctionTag_T >( *storage, maxLevel ) );

              if( compareWithAnalyticalSolution )
              {
                 error.assign( {1.0, -1.0}, {u, exactSolution}, maxLevel, DoFType::All );
              }

              WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] "
                                         << std::setw( 9 ) << mgIteration << " | " << std::setw( 13 ) << std::scientific
                                         << currentResidualL2 << " | " << std::setw( 16 ) << std::scientific
                                         << currentResidualL2 / lastResidualL2 << " | " << std::setw( 7 ) << std::fixed
                                         << std::setprecision( 3 ) << timer.last() )
          }
          vtkOutput.write( maxLevel, numMGCycles );
          break;
        }
        case MIN_RES:
        {
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Solving with multigrid (Uzawa + MinRes on coarse grid)..." )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] iteration | residual (L2) | convergence rate |     time " )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] ----------+---------------+------------------+--------- " )

          auto restrictionOperator = std::make_shared< RestrictionOperator_T >();
          auto prolongationOperator = std::make_shared< ProlongationOperator_T >();
          auto uzawaSmoother = std::make_shared< hhg::UzawaSmoother< StokesOperator_T > >(
              storage, minLevel, maxLevel, storage->hasGlobalCells(), uzawaRelaxParam );

          auto solver = hhg::GeometricMultigridSolver< StokesOperator_T >( storage,
                                                                           uzawaSmoother,
                                                                           minResSolver,
                                                                           restrictionOperator,
                                                                           prolongationOperator,
                                                                           minLevel,
                                                                           maxLevel,
                                                                           preSmooth,
                                                                           postSmooth,
                                                                           incrementSmooth );

          walberla::WcTimer timer;
          for ( uint_t mgIteration = 0; mgIteration < numMGCycles; mgIteration++ )
          {
            vtkOutput.write( maxLevel, mgIteration );

            timer.start();
            solver.solve( L, u, f, maxLevel );
            timer.end();

            if ( rescalePressure )
            {
              const real_t minPressure = u.p.getMinValue( maxLevel, DoFType::All );
              u.p.add( -minPressure, maxLevel, DoFType::All );
            }

            lastResidualL2 = currentResidualL2;
            L.apply( u, Au, maxLevel, hhg::Inner | hhg::NeumannBoundary );
            r.assign( {1.0, -1.0}, {f, Au}, maxLevel, hhg::Inner | hhg::NeumannBoundary );
            currentResidualL2 = std::sqrt( r.dotGlobal( r, maxLevel, hhg::Inner | hhg::NeumannBoundary ) ) / real_c(hhg::numberOfGlobalDoFs< StokesFunctionTag_T >( *storage, maxLevel ));

            if ( compareWithAnalyticalSolution )
            {
              error.assign( {1.0, -1.0}, {u, exactSolution}, maxLevel, DoFType::All );
            }

            WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] " << std::setw(9) << mgIteration << " | "
                                                                       << std::setw(13) << std::scientific << currentResidualL2 << " | "
                                                                       << std::setw(16) << std::scientific << currentResidualL2 / lastResidualL2 << " | "
                                                                       << std::setw(7) << std::fixed << std::setprecision(3) << timer.last() )
          }
          vtkOutput.write( maxLevel, numMGCycles );
          break;
        }
        case PETSC:
        {
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Solving with multigrid (Uzawa + PETSc on coarse grid)..." )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] iteration | residual (L2) | convergence rate |     time " )
          WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] ----------+---------------+------------------+--------- " )

           auto restrictionOperator = std::make_shared< RestrictionOperator_T >();
           auto prolongationOperator = std::make_shared< ProlongationOperator_T >();
           auto uzawaSmoother = std::make_shared< hhg::UzawaSmoother< StokesOperator_T > >(
               storage, minLevel, maxLevel, storage->hasGlobalCells(), uzawaRelaxParam );

           auto solver = hhg::GeometricMultigridSolver< StokesOperator_T >( storage,
                                                                            uzawaSmoother,
                                                                            petscSolver,
                                                                            restrictionOperator,
                                                                            prolongationOperator,
                                                                            minLevel,
                                                                            maxLevel,
                                                                            preSmooth,
                                                                            postSmooth,
                                                                            incrementSmooth );

          walberla::WcTimer timer;
          for ( uint_t mgIteration = 0; mgIteration < numMGCycles; mgIteration++ )
          {
            vtkOutput.write( maxLevel, mgIteration );

            timer.start();
            solver.solve( L, u, f, maxLevel );
            timer.end();

            if ( rescalePressure )
            {
              const real_t minPressure = u.p.getMinValue( maxLevel, DoFType::All );
              u.p.add( -minPressure, maxLevel, DoFType::All );
            }

            lastResidualL2 = currentResidualL2;
            L.apply( u, Au, maxLevel, hhg::Inner | hhg::NeumannBoundary );
            r.assign( {1.0, -1.0}, {&f, &Au}, maxLevel, hhg::Inner | hhg::NeumannBoundary );
            currentResidualL2 = std::sqrt( r.dotGlobal( r, maxLevel, hhg::Inner | hhg::NeumannBoundary ) ) / real_c(hhg::numberOfGlobalDoFs< StokesFunctionTag_T >( *storage, maxLevel ));

            if ( compareWithAnalyticalSolution )
            {
              error.assign( {1.0, -1.0}, {&u, &exactSolution}, maxLevel, DoFType::All );
            }

            WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] " << std::setw(9) << mgIteration << " | "
                                                                       << std::setw(13) << std::scientific << currentResidualL2 << " | "
                                                                       << std::setw(16) << std::scientific << currentResidualL2 / lastResidualL2 << " | "
                                                                       << std::setw(7) << std::fixed << std::setprecision(3) << timer.last() << "s" )
          }
          vtkOutput.write( maxLevel, numMGCycles );
          break;
        }
        default:
        {
           ///this should never be reached but is needed to avoid compiler warnings
           WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid coarse grid solver type!" );
        }
      }
    }
  }

  L.apply( u, Au, maxLevel, hhg::Inner | hhg::NeumannBoundary );
  r.assign( {1.0, -1.0}, {&f, &Au}, maxLevel, hhg::Inner | hhg::NeumannBoundary );
  currentResidualL2 = std::sqrt( r.dotGlobal( r, maxLevel, hhg::Inner | hhg::NeumannBoundary ) ) / real_c(hhg::numberOfGlobalDoFs< StokesFunctionTag_T >( *storage, maxLevel ));
  WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Final residual:   " << currentResidualL2 );

  if ( compareWithAnalyticalSolution )
  {
    error.assign( {1.0, -1.0}, {&u, &exactSolution}, maxLevel, DoFType::All );
    const real_t currentErrorL2 = std::sqrt( error.dotGlobal( error, maxLevel, hhg::All ) ) / real_c(hhg::numberOfGlobalDoFs< typename StokesFunction_T< real_t >::Tag >( *storage, maxLevel ));
    WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Final error: " << currentErrorL2 );
  }

  timingTree->stop( "Complete app" );
  const auto tt = timingTree->getReduced();
  if ( printTimer )
    WALBERLA_LOG_INFO_ON_ROOT( tt );
}

}

int main( int argc, char* argv[] )
{
  using walberla::real_c;

  walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
  walberla::MPIManager::instance()->useWorldComm();

  walberla::logging::Logging::printHeaderOnStream();

  std::vector<std::string> args( argv, argv + argc );

  const std::string defaultParameterFile = "../data/param/StokesFlowSolverComparison.prm";

  std::string parameterFile;
  if ( args.size() <= 1 )
  {
    WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] No parameter file given, falling back to " << defaultParameterFile );
    parameterFile = defaultParameterFile;
  }
  else
  {
    WALBERLA_LOG_INFO_ON_ROOT( "[StokesFlowSolverComparison] Using parameter file " << args[1] );
    parameterFile = args[1];
  }
  walberla::shared_ptr< walberla::config::Config > cfg( new walberla::config::Config );
  cfg->readParameterFile( parameterFile.c_str() );
  walberla::Config::BlockHandle parameters = cfg->getOneBlock( "Parameters" );

  const uint_t      minLevel   = parameters.getParameter< uint_t >( "minLevel" );
  const uint_t      maxLevel   = parameters.getParameter< uint_t >( "maxLevel" );
  const std::string meshType   = parameters.getParameter< std::string >( "meshType" );
  const uint_t maxIterations   = parameters.getParameter< uint_t >( "minResMaxIterations" );
  const real_t targetResidual  = parameters.getParameter< real_t >( "minResTargetResidual" );
  const uint_t numMGCycles                   = parameters.getParameter< uint_t >( "numMGCycles" );
  const uint_t preSmooth                     = parameters.getParameter< uint_t >( "preSmooth" );
  const uint_t postSmooth                    = parameters.getParameter< uint_t >( "postSmooth" );
  const uint_t incrementSmooth               = parameters.getParameter< uint_t >( "incrementSmooth" );
  const std::string discretizationTypeString = parameters.getParameter< std::string >( "discretization" );
  const std::string solverTypeString         = parameters.getParameter< std::string >( "solver" );
  const std::string coarseGridSolverString   = parameters.getParameter< std::string >( "coarseGridSolver" );
  const bool rescalePressure = parameters.getParameter< bool >( "rescalePressure" );
  const bool printTimer = parameters.getParameter< bool >( "printTimer" );
  const std::string squareDomainSolutionType = parameters.getParameter< std::string >( "squareDomainReference" );
  const real_t uzawaRelaxParam = parameters.getParameter<real_t>("uzawaRelaxParam");

  ///////////////////////////////////
  // Check and evaluate parameters //
  ///////////////////////////////////

  // Solver type

  if ( hhg::strToSolverType.count( solverTypeString ) == 0 )
  {
    WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid solver type!" );
  }
  if ( hhg::strToSolverType.count( coarseGridSolverString ) == 0 || hhg::strToSolverType.at( coarseGridSolverString ) == hhg::UZAWA )
  {
    WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid coarse grid solver type!" );
  }
  if ( hhg::strToDiscretizationType.count( discretizationTypeString ) == 0 )
  {
    WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid discretization type!" );
  }
  const hhg::SolverType solverType                 = hhg::strToSolverType.at( solverTypeString );
  const hhg::SolverType coarseGridSolver           = hhg::strToSolverType.at( coarseGridSolverString );
  const hhg::DiscretizationType discretizationType = hhg::strToDiscretizationType.at( discretizationTypeString );

  // Mesh

  const hhg::MeshInfo meshInfo = [ meshType, squareDomainSolutionType ]()
  {
    if ( meshType == "square" )
    {
      return hhg::MeshInfo::meshRectangle( squareDomainSolutionType == "colliding_flow" || squareDomainSolutionType == "poiseuille_flow" ? hhg::Point2D({-1, -1}) : hhg::Point2D({0, 0}),
                                      hhg::Point2D({1, 1}),
                                      hhg::MeshInfo::CRISSCROSS, 1, 1 );
    }
    else if ( meshType == "porous_coarse" )
    {
      return hhg::MeshInfo::fromGmshFile( "../data/meshes/porous_coarse.msh" );
    }
    else if ( meshType == "porous_fine" )
    {
      return hhg::MeshInfo::fromGmshFile( "../data/meshes/porous_fine.msh" );
    }
    else if ( meshType == "bfs_coarse" )
    {
      return hhg::MeshInfo::fromGmshFile( "../data/meshes/bfs_12el.msh" );
    }
    else if ( meshType == "bfs_fine" )
    {
      return hhg::MeshInfo::fromGmshFile( "../data/meshes/bfs_126el.msh" );
    }
    else
    {
      WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
      return hhg::MeshInfo::emptyMeshInfo();
    }
  }();

  // Boundaries

  const std::function< real_t( const hhg::Point3D& ) > zero  = []( const hhg::Point3D& ) { return 0.0; };

  const auto setMeshBoundaryFlags = [ meshType, squareDomainSolutionType ]() -> std::function< void( hhg::SetupPrimitiveStorage & ) >
  {
      if ( meshType == "bfs_coarse" || meshType == "bfs_fine" )
      {
        return hhg::setRightBFSBoundaryNeumannBFS;
      }
      else if ( meshType == "square" && squareDomainSolutionType == "poiseuille_flow" )
      {
        return hhg::setRightBFSBoundaryNeumannPoiseuille;
      }
      else if ( meshType == "porous_coarse" || meshType == "porous_fine" )
      {
        return hhg::keepMeshBoundaries;
      }
      else
      {
        return hhg::setAllBoundariesDirichlet;
      }
  }();

  // Velocity BC

  const auto setUVelocityBC = [ meshType, zero, squareDomainSolutionType ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
    if ( meshType == "porous_coarse" || meshType == "porous_fine" )
    {
      auto f = []( const hhg::Point3D & x ) -> real_t
      {
          if ( x[0] < 1e-8 )
          {
            return 4.0 * x[1] * ( 1.0 - x[1] );
          }
          else
          {
            return 0.0;
          }
      };
      return f;
    }
    else if ( meshType == "bfs_coarse" || meshType == "bfs_fine"  )
    {
      auto f = []( const hhg::Point3D & x ) -> real_t
      {
          if( x[0] < 1e-8 )
          {
            return real_c( 16.0 * ( x[1] - 0.5 ) * ( 1.0 - x[1] ) );
          }
          else
          {
            return real_c( 0 );
          }
      };
      return f;
    }
    else if ( meshType == "square" )
    {
      if ( squareDomainSolutionType == "colliding_flow" )
      {
        return []( const hhg::Point3D & x ) -> real_t
        {
            return real_c( 20 ) * x[0] * x[1] * x[1] * x[1];
        };
      }
      else if ( squareDomainSolutionType == "poiseuille_flow" )
      {
        return []( const hhg::Point3D & x ) -> real_t
        {
            if( x[0] < -1.0 + 1e-8 )
            {
              return real_c( 1 - x[1] * x[1] );
            }
            else
            {
              return real_c( 0 );
            }
        };
      }
      else
      {
        return []( const hhg::Point3D & x ) -> real_t
        {
            return real_c( std::sin( walberla::math::pi * x[0] ) * std::sin( walberla::math::pi * x[1] ));
        };
      }
    }
    else
    {
      WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
      return zero;
    }
  }();

  const auto setVVelocityBC = [ meshType, zero, squareDomainSolutionType ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
      if (    meshType == "porous_coarse" || meshType == "porous_fine"
           || meshType == "bfs_coarse"    || meshType == "bfs_fine" )
      {
        return zero;
      }
      else if ( meshType == "square" )
      {
        if ( squareDomainSolutionType == "colliding_flow" )
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
              return real_c( 5 ) *std::pow( x[0], real_c(4) ) - real_c( 5 ) *std::pow( x[1], real_c(4) );
          };
        }
        else if ( squareDomainSolutionType == "poiseuille_flow" )
        {
          return zero;
        }
        else
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
              return real_c( std::cos( walberla::math::pi * x[0] ) * std::cos( walberla::math::pi * x[1] ));
          };
        }

      }
      else
      {
        WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
        return zero;
      }
  }();

  // Velocity RHS

  const auto setUVelocityRHS = [ meshType, zero, squareDomainSolutionType ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
      if (    meshType == "porous_coarse" || meshType == "porous_fine"
           || meshType == "bfs_coarse"    || meshType == "bfs_fine" )
      {
        return zero;
      }
      else if ( meshType == "square" )
      {
        if ( squareDomainSolutionType == "colliding_flow" || squareDomainSolutionType == "poiseuille_flow" )
        {
          return zero;
        }
        else
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
              return real_c( 2 ) * std::pow( walberla::math::pi, 2 ) *
                     std::sin( walberla::math::pi * x[0] ) * std::sin( walberla::math::pi * x[1] ) +
                     std::cos( walberla::math::pi * x[0] ) * std::sin( walberla::math::pi * x[1] );
          };
        }
      }
      else
      {
        WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
        return zero;
      }
  }();

  const auto setVVelocityRHS = [ meshType, zero, squareDomainSolutionType ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
      if (    meshType == "porous_coarse" || meshType == "porous_fine"
              || meshType == "bfs_coarse"    || meshType == "bfs_fine" )
      {
        return zero;
      }
      else if ( meshType == "square" )
      {
        if ( squareDomainSolutionType == "colliding_flow" || squareDomainSolutionType == "poiseuille_flow" )
        {
          return zero;
        }
        else
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
              return real_c( 2 ) * std::pow( walberla::math::pi, 2 ) *
                     std::cos( walberla::math::pi * x[0] ) * std::cos( walberla::math::pi * x[1] ) +
                     std::sin( walberla::math::pi * x[0] ) * std::cos( walberla::math::pi * x[1] );
          };
        }
      }
      else
      {
        WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
        return zero;
      }
  }();

  // Analytical solution

  const auto solutionU = [ meshType, squareDomainSolutionType, setUVelocityBC ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
    if ( meshType == "square" && squareDomainSolutionType == "poiseuille_flow" )
    {
      return []( const hhg::Point3D & x ) -> real_t
      {
        return real_c( 1 - x[1] * x[1] );
      };
    }
    else
    {
      return setUVelocityBC;
    }
  }();
  const auto solutionV = setVVelocityBC;
  const auto solutionP = [ meshType, zero, squareDomainSolutionType, rescalePressure ]() -> std::function< real_t( const hhg::Point3D & ) >
  {
      if (    meshType == "porous_coarse" || meshType == "porous_fine"
           || meshType == "bfs_coarse"    || meshType == "bfs_fine" )
      {
        return zero;
      }
      else if ( meshType == "square" )
      {
        if ( squareDomainSolutionType == "colliding_flow" )
        {
          return [ rescalePressure ]( const hhg::Point3D & x ) -> real_t
          {
              return real_c( 60 ) * x[0] * x[0] * x[1] - real_c(20) * x[1] * x[1] * x[1] + (rescalePressure ? real_c(40) : real_c(0));
          };
        }
        else if ( squareDomainSolutionType == "poiseuille_flow" )
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
              return real_c( -2.0 * x[0] );
          };
        }
        else
        {
          return []( const hhg::Point3D & x ) -> real_t
          {
             return real_c( std::sin( walberla::math::pi * x[0] ) * std::sin( walberla::math::pi * x[1] ));
          };
        }
      }
      else
      {
        WALBERLA_ABORT( "[StokesFlowSolverComparison] Invalid mesh type!" );
        return zero;
      }
  }();

  const bool compareWithAnalyticalSolution = meshType == "square";


  std::stringstream parameterOverview;
  parameterOverview <<       "[StokesFlowSolverComparison] Parameter overview:\n"
                             "                             - meshType:                    " << meshType << "\n"
                             "                             - discretization:              " << discretizationTypeString << "\n"
                             "                             - solver:                      " << solverTypeString << "\n"
                             "                             - analytical solution:         " << (compareWithAnalyticalSolution ? "available" : "not available") << "\n"
                             "                             - solution type:               " << (compareWithAnalyticalSolution ? squareDomainSolutionType : "-") << "\n"
                             "                             - timer output:                " << (printTimer ? "enabled" : "disabled") << "\n"
                             "                             - rescale pressure:            " << (rescalePressure ? "enabled" : "disabled") << "\n";

  if ( solverType == hhg::UZAWA )
  {
    parameterOverview <<     "                             - coarsest level:              " << minLevel << "\n"
                             "                             - finest level:                " << maxLevel << "\n"
                             "                             - coarse grid solver:          " << coarseGridSolverString << "\n"
                             "                             - num MG cycles:               " << numMGCycles << "\n"
                             "                             - pre- / post-smoothing steps: " << "( " << preSmooth << ", " << postSmooth << " )";
  }
  else if ( solverType == hhg::MIN_RES )
  {
    parameterOverview <<     "                             - level:                       " << maxLevel << "\n"
                             "                             - max. iterations:             " << maxIterations << "\n"
                             "                             - tolerance:                   " << targetResidual << "\n"
                             "                             - A-block V-Cycles:            " << numMGCycles << "\n"
                             "                             - pre- / post-smoothing steps: " << "( " << preSmooth << ", " << postSmooth << " )";
  }
  WALBERLA_LOG_INFO_ON_ROOT( parameterOverview.str() );

  switch ( discretizationType )
  {
    case hhg::P1P1:
      hhg::run< hhg::P1StokesFunction, hhg::P1StokesOperator, hhg::P1P1StokesToP1P1StokesRestriction, hhg::P1P1StokesToP1P1StokesProlongation, hhg::P1ConstantMassOperator >(
        meshInfo, minLevel, maxLevel, solverType, coarseGridSolver, numMGCycles, preSmooth, postSmooth, incrementSmooth, uzawaRelaxParam, targetResidual, maxIterations,
        setMeshBoundaryFlags, setUVelocityBC, setVVelocityBC, setUVelocityRHS, setVVelocityRHS,
        compareWithAnalyticalSolution, solutionU, solutionV, solutionP,
        rescalePressure, printTimer );
      break;
    case hhg::TaylorHood:
      hhg::run< hhg::P2P1TaylorHoodFunction, hhg::P2P1TaylorHoodStokesOperator, hhg::P2P1StokesToP2P1StokesRestriction, hhg::P2P1StokesToP2P1StokesProlongation, hhg::P2ConstantMassOperator >(
        meshInfo, minLevel, maxLevel, solverType, coarseGridSolver, numMGCycles, preSmooth, postSmooth, incrementSmooth, uzawaRelaxParam, targetResidual, maxIterations,
        setMeshBoundaryFlags, setUVelocityBC, setVVelocityBC, setUVelocityRHS, setVVelocityRHS,
        compareWithAnalyticalSolution, solutionU, solutionV, solutionP,
        rescalePressure, printTimer );
      break;
  }

  walberla::logging::Logging::printFooterOnStream();
  return EXIT_SUCCESS;
}
