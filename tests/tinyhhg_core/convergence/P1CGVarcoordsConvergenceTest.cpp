#include "core/Environment.h"
#include "core/timing/Timer.h"
#include "core/math/Constants.h"

#include "tinyhhg_core/mesh/MeshInfo.hpp"
#include "tinyhhg_core/p1functionspace/P1ConstantOperator.hpp"
#include "tinyhhg_core/p1functionspace/P1ElementwiseOperator.hpp"
#include "tinyhhg_core/p1functionspace/P1Function.hpp"
#include "tinyhhg_core/primitivestorage/PrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/DistributedBalancer.hpp"
#include "tinyhhg_core/primitivestorage/loadbalancing/SimpleBalancer.hpp"
#include "tinyhhg_core/solvers/CGSolver.hpp"

using walberla::real_t;
using walberla::uint_c;
using walberla::uint_t;

using namespace hhg;

int main( int argc, char* argv[] )
{
   walberla::Environment walberlaEnv( argc, argv );
   walberla::logging::Logging::instance()->setLogLevel( walberla::logging::Logging::PROGRESS );
   walberla::MPIManager::instance()->useWorldComm();

   std::string meshFileName = "../../data/meshes/quad_2el.msh";

   MeshInfo              meshInfo = MeshInfo::fromGmshFile( meshFileName );
   SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );

   hhg::loadbalancing::roundRobin( setupStorage );

   size_t minLevel = 2;
   size_t maxLevel = 4;

   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

#ifdef WALBERLA_BUILD_WITH_PARMETIS
   loadbalancing::distributed::parmetis( *storage );
#endif

   hhg::P1Function< real_t > r( "r", storage, minLevel, maxLevel );
   hhg::P1Function< real_t > f( "f", storage, minLevel, maxLevel );
   hhg::P1Function< real_t > u( "u", storage, minLevel, maxLevel );
   hhg::P1Function< real_t > u_exact( "u_exact", storage, minLevel, maxLevel );
   hhg::P1Function< real_t > err( "err", storage, minLevel, maxLevel );
   hhg::P1Function< real_t > npoints_helper( "npoints_helper", storage, minLevel, maxLevel );

   auto coordX = std::make_shared< hhg::P1Function< real_t > >( "x", storage, minLevel, maxLevel );
   auto coordY = std::make_shared< hhg::P1Function< real_t > >( "y", storage, minLevel, maxLevel );

   auto coords    = std::make_shared< std::array< const hhg::P1Function< real_t >*, 2 > >();
   ( *coords )[0] = coordX.get();
   ( *coords )[1] = coordY.get();

   //  hhg::P1MassOperator M(storage, minLevel, maxLevel);
   hhg::P1ConstantLaplaceOperator    Ltest( storage, minLevel, maxLevel );
   hhg::P1ElementwiseLaplaceOperator L( storage, *coords, minLevel, maxLevel );
   hhg::P1ElementwiseMassOperator    M( storage, *coords, minLevel, maxLevel );

   std::shared_ptr< walberla::WcTimingTree > timingTree( new walberla::WcTimingTree() );
   r.enableTiming( timingTree );
   f.enableTiming( timingTree );
   u.enableTiming( timingTree );
   u_exact.enableTiming( timingTree );
   err.enableTiming( timingTree );
   npoints_helper.enableTiming( timingTree );
   coordX->enableTiming( timingTree );
   coordY->enableTiming( timingTree );

   L.enableTiming( timingTree );

   std::function< real_t( const hhg::Point3D& ) > map_x = []( const hhg::Point3D& x ) {
      return x[0] + 0.1 * x[0] * std::sin( 3.0 * walberla::math::pi * x[1] );
   };

   std::function< real_t( const hhg::Point3D& ) > map_y = []( const hhg::Point3D& x ) { return x[1]; };

   std::function< real_t( const hhg::Point3D& ) > exact = [&map_x, &map_y]( const hhg::Point3D& x ) {
      Point3D xt{{{map_x( x ), map_y( x ), 0.0}}};
      return ( 1.0 / 2.0 ) * sin( 2 * xt[0] ) * sinh( xt[1] );
   };
   std::function< real_t( const hhg::Point3D& ) > rhs = [&map_x, &map_y]( const hhg::Point3D& x ) {
      Point3D xt{{{map_x( x ), map_y( x ), 0.0}}};
      return ( 3.0 / 2.0 ) * sin( 2 * xt[0] ) * sinh( xt[1] );
   };
   std::function< real_t( const hhg::Point3D& ) > ones = []( const hhg::Point3D& ) { return 1.0; };

   for( uint_t level = minLevel; level <= maxLevel; ++level )
   {
      coordX->interpolate( map_x, level );
      coordY->interpolate( map_y, level );
   }

   // make sure that all coordinates are synchronized over all primitives and levels
   for( uint_t level = minLevel; level <= maxLevel; ++level )
   {
      coordX->communicate< Vertex, Edge >( level );
      coordX->communicate< Edge, Face >( level );
      coordX->communicate< Face, Edge >( level );
      coordX->communicate< Edge, Vertex >( level );

      coordY->communicate< Vertex, Edge >( level );
      coordY->communicate< Edge, Face >( level );
      coordY->communicate< Face, Edge >( level );
      coordY->communicate< Edge, Vertex >( level );
   }

   u.interpolate( exact, maxLevel, hhg::DirichletBoundary );
   u_exact.interpolate( exact, maxLevel );
   npoints_helper.interpolate( rhs, maxLevel );
   M.apply( npoints_helper, f, maxLevel, hhg::All );

   auto solver = hhg::CGSolver< hhg::P1ElementwiseLaplaceOperator >( storage, minLevel, maxLevel );
   walberla::WcTimer timer;
   solver.solve( L, u, f, maxLevel);
   timer.end();
   WALBERLA_LOG_INFO_ON_ROOT( "time was: " << timer.last() );
   err.assign( {1.0, -1.0}, {u, u_exact}, maxLevel );

   npoints_helper.interpolate( ones, maxLevel );
   real_t npoints = npoints_helper.dotGlobal( npoints_helper, maxLevel );

   real_t discr_l2_err = std::sqrt( err.dotGlobal( err, maxLevel ) / npoints );

   WALBERLA_LOG_INFO_ON_ROOT( "discrete L2 error = " << discr_l2_err );

   //  hhg::VTKWriter<hhg::P1Function<real_t>, hhg::DGFunction<real_t >>({ u, u_exact, &f, &r, &err }, {}, maxLevel,
   //                                                                    "../output", "varcoords", coords);

   walberla::WcTimingTree tt = timingTree->getReduced();
   WALBERLA_LOG_INFO_ON_ROOT( tt );

   /// a higher level would significantly decrase the error but also the runtime
   WALBERLA_CHECK_LESS( discr_l2_err, 3e-04 );

   return EXIT_SUCCESS;
}
