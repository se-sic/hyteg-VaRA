/*
* Copyright (c) 2022 Andreas Wagner.
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

#include "hyteg/gridtransferoperators/DGProlongation.hpp"

#include "core/DataTypes.h"
#include "core/math/Random.h"
#include "core/mpi/MPIManager.h"

#include "hyteg/dataexport/VTKOutput.hpp"
#include "hyteg/dgfunctionspace/DGBasisLinearLagrange_Example.hpp"
#include "hyteg/dgfunctionspace/DGFunction.hpp"
#include "hyteg/dgfunctionspace/DGMassForm_Example.hpp"
#include "hyteg/dgfunctionspace/DGOperator.hpp"
#include "hyteg/functions/FunctionTraits.hpp"
#include "hyteg/mesh/MeshInfo.hpp"
#include "hyteg/petsc/PETScCGSolver.hpp"
#include "hyteg/petsc/PETScManager.hpp"
#include "hyteg/primitivestorage/SetupPrimitiveStorage.hpp"

using walberla::real_t;
using walberla::uint_t;

using namespace hyteg;
using namespace dg;

void testLinear2D( const std::string& meshFile )
{
   const uint_t minLevel = 2;
   const uint_t maxLevel = minLevel + 1;

   MeshInfo              mesh = MeshInfo::fromGmshFile( meshFile );
   SetupPrimitiveStorage setupStorage( mesh, uint_c( walberla::mpi::MPIManager::instance()->numProcesses() ) );
   setupStorage.setMeshBoundaryFlagsOnBoundary( 1, 0, true );
   auto storage = std::make_shared< PrimitiveStorage >( setupStorage, 1 );

   auto dgBasis  = std::make_shared< DGBasisLinearLagrange_Example >();
   auto massForm = std::make_shared< DGMassForm_Example >();

   DGFunction< real_t > test_function( "test_function", storage, minLevel, maxLevel, dgBasis, 1 );
   DGFunction< real_t > tmp( "tmp", storage, minLevel, maxLevel, dgBasis, 1 );
   DGFunction< real_t > solution_function( "solution_function", storage, maxLevel, maxLevel, dgBasis, 1 );

   DGFunction< idx_t > numerator( "numerator", storage, minLevel, maxLevel, dgBasis, 1 );
   numerator.enumerate( minLevel );
   numerator.enumerate( maxLevel );
   DGOperator M( storage, minLevel, maxLevel, massForm );
   tmp.evaluateLinearFunctional( []( const Point3D& p ) { return 0.5 * p[0] + p[1]; }, minLevel );
   tmp.evaluateLinearFunctional( []( const Point3D& p ) { return 0.5 * p[0] + p[1]; }, maxLevel );
   // interpolate test_function on lower level
   {
      PETScCGSolver< DGOperator > solverM( storage, minLevel, numerator );
      solverM.solve( M, test_function, tmp, minLevel );
   }
   // interpolate solution function on upper level
   {
      PETScCGSolver< DGOperator > solverM( storage, maxLevel, numerator );
      solverM.solve( M, solution_function, tmp, maxLevel );
   }

   DGLinearProlongation prolongation;

   prolongation.prolongate( test_function, minLevel, All );

   tmp.assign( { +1., -1. }, { test_function, solution_function }, maxLevel, All );
   const real_t error = tmp.dotGlobal( tmp, maxLevel, All );

   WALBERLA_ASSERT_FLOAT_EQUAL( error, 0. );

   // VTKOutput vtk( "../../output/", "DGProlongationTest", storage );
   // vtk.add( test_function );
   // vtk.write( minLevel );
   // vtk.write( maxLevel );
}

int main( int argc, char* argv[] )
{
   walberla::MPIManager::instance()->initializeMPI( &argc, &argv );
   walberla::MPIManager::instance()->useWorldComm();
   PETScManager petscManager( &argc, &argv );

   testLinear2D( "../../data/meshes/tri_1el.msh" );
   testLinear2D( "../../data/meshes/circle.msh" );

   return 0;
}
