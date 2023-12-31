/*
 * Copyright (c) 2022 Daniel Bauer.
 *
 * This file is part of HyTeG
 * (see https://i10git.cs.fau.de/hyteg/hyteg).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/debug/TestSubsystem.h"
#include "core/math/Random.h"
#include "core/mpi/Environment.h"

#include "hyteg/n1e1functionspace/N1E1VectorFunction.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"

using walberla::real_t;
using namespace hyteg;

void test3D()
{
   MeshInfo              meshInfo = MeshInfo::meshSymmetricCuboid( Point3D( 0, 0, 0 ), Point3D( 1, 1, 1 ), 1, 1, 1 );
   SetupPrimitiveStorage setupStorage( meshInfo, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   std::shared_ptr< PrimitiveStorage > storage = std::make_shared< PrimitiveStorage >( setupStorage );

   const size_t minLevel = 2;
   const size_t maxLevel = 4;

   walberla::math::seedRandomGenerator( 42 );

   const uint_t numRandomEvaluations = 1000;

   // most general function in N1E1 space
   const Point3D                                    a         = { 1, 2, 3 };
   const Point3D                                    b         = { 4, 5, 6 };
   const Point3D                                    c         = { 7, 8, 9 };
   const std::function< Point3D( const Point3D& ) > testFunc1 = [&]( const Point3D& x ) { return Point3D{ a + b.cross( x ) }; };
   const std::function< Point3D( const Point3D& ) > testFunc2 = [&]( const Point3D& x ) { return Point3D{ b + c.cross( x ) }; };

   n1e1::N1E1VectorFunction< real_t > f1( "f1", storage, minLevel, maxLevel );
   n1e1::N1E1VectorFunction< real_t > f2( "f2", storage, minLevel, maxLevel );
   n1e1::N1E1VectorFunction< real_t > f3( "f3", storage, minLevel, maxLevel );

   for ( uint_t level = minLevel; level <= maxLevel; level++ )
   {
      f1.interpolate( testFunc1, level );
      f2.interpolate( testFunc2, level );
      f3.assign( { 1, 2 }, { f1, f2 }, level );

      for ( uint_t i = 0; i < numRandomEvaluations; ++i )
      {
         Point3D coordinates;
         coordinates[0] = real_c( walberla::math::realRandom( 0.0, 1.0 ) );
         coordinates[1] = real_c( walberla::math::realRandom( 0.0, 1.0 ) );
         coordinates[2] = real_c( walberla::math::realRandom( 0.0, 1.0 ) );

         Point3D exact = testFunc1( coordinates ) + 2 * testFunc2( coordinates );
         Point3D eval;
         auto    success = f3.evaluate( coordinates, level, eval );
         WALBERLA_CHECK( success );
         WALBERLA_CHECK_FLOAT_EQUAL( eval[0], exact[0], "Test3D: wrong X-coordinate at " << coordinates << "." );
         WALBERLA_CHECK_FLOAT_EQUAL( eval[1], exact[1], "Test3D: wrong Y-coordinate at " << coordinates << "." );
         WALBERLA_CHECK_FLOAT_EQUAL( eval[2], exact[2], "Test3D: wrong Z-coordinate at " << coordinates << "." );

         WALBERLA_LOG_INFO_ON_ROOT( "Passed: " << coordinates )
      }
   }
}

int main( int argc, char** argv )
{
   walberla::debug::enterTestMode();
   walberla::mpi::Environment MPIenv( argc, argv );
   walberla::MPIManager::instance()->useWorldComm();

   test3D();

   return EXIT_SUCCESS;
}
