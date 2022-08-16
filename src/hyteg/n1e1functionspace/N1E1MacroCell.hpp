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
#pragma once

#include "core/DataTypes.h"

#include "hyteg/edgedofspace/EdgeDoFIndexing.hpp"
#include "hyteg/edgedofspace/EdgeDoFMacroCell.hpp"
#include "hyteg/edgedofspace/EdgeDoFOrientation.hpp"
#include "hyteg/memory/FunctionMemory.hpp"
#include "hyteg/n1e1functionspace/N1E1Indexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroCell.hpp"
#include "hyteg/primitives/Cell.hpp"
#include "hyteg/volumedofspace/VolumeDoFFunction.hpp"

namespace hyteg {
namespace n1e1 {

template < typename ValueType >
class N1E1VectorFunction;

namespace macrocell {

using indexing::IndexIncrement;
using walberla::int_c;
using walberla::uint_t;
template < typename ValueType >
using VectorType = typename N1E1VectorFunction< ValueType >::VectorType;

inline Eigen::Vector3d microEdgeDirection( const uint_t& level, const Cell& cell, const edgedof::EdgeDoFOrientation& orientation )
{
   const real_t          stepFrequency = 1.0 / real_c( levelinfo::num_microedges_per_edge( level ) );
   const Eigen::Vector3d xDir          = toEigen( cell.getCoordinates()[1] - cell.getCoordinates()[0] ) * stepFrequency;
   const Eigen::Vector3d yDir          = toEigen( cell.getCoordinates()[2] - cell.getCoordinates()[0] ) * stepFrequency;
   const Eigen::Vector3d zDir          = toEigen( cell.getCoordinates()[3] - cell.getCoordinates()[0] ) * stepFrequency;

   switch ( orientation )
   {
   case edgedof::EdgeDoFOrientation::X:
      return xDir;
   case edgedof::EdgeDoFOrientation::Y:
      return yDir;
   case edgedof::EdgeDoFOrientation::Z:
      return zDir;
   case edgedof::EdgeDoFOrientation::XY:
      return yDir - xDir;
   case edgedof::EdgeDoFOrientation::XZ:
      return zDir - xDir;
   case edgedof::EdgeDoFOrientation::YZ:
      return zDir - yDir;
   case edgedof::EdgeDoFOrientation::XYZ:
      return zDir - yDir + xDir;
   default:
      WALBERLA_ABORT( "wrong orienation" )
   }
}

inline VectorType< real_t > evaluateOnMicroElement( const uint_t&                                            level,
                                                    const Cell&                                              cell,
                                                    const hyteg::indexing::Index                             elementIndex,
                                                    const celldof::CellType                                  cellType,
                                                    const Point3D&                                           coordinates,
                                                    const PrimitiveDataID< FunctionMemory< real_t >, Cell >& dataID )
{
   using ValueType = real_t;

   // get vertices of microcell

   auto microCellIndices = getMicroVerticesFromMicroCell( elementIndex, cellType );

   auto microTet0 = vertexdof::macrocell::coordinateFromIndex( level, cell, microCellIndices[0] );
   auto microTet1 = vertexdof::macrocell::coordinateFromIndex( level, cell, microCellIndices[1] );
   auto microTet2 = vertexdof::macrocell::coordinateFromIndex( level, cell, microCellIndices[2] );
   auto microTet3 = vertexdof::macrocell::coordinateFromIndex( level, cell, microCellIndices[3] );

   IndexIncrement vertexIndex0 =
       IndexIncrement( int_c( microCellIndices[0].x() ), int_c( microCellIndices[0].y() ), int_c( microCellIndices[0].z() ) );
   IndexIncrement vertexIndex1 =
       IndexIncrement( int_c( microCellIndices[1].x() ), int_c( microCellIndices[1].y() ), int_c( microCellIndices[1].z() ) );
   IndexIncrement vertexIndex2 =
       IndexIncrement( int_c( microCellIndices[2].x() ), int_c( microCellIndices[2].y() ), int_c( microCellIndices[2].z() ) );
   IndexIncrement vertexIndex3 =
       IndexIncrement( int_c( microCellIndices[3].x() ), int_c( microCellIndices[3].y() ), int_c( microCellIndices[3].z() ) );

   // get edges of microcell

   auto edgeIndex0 = edgedof::calcEdgeDoFIndex( vertexIndex0, vertexIndex1 );
   auto edgeIndex1 = edgedof::calcEdgeDoFIndex( vertexIndex0, vertexIndex2 );
   auto edgeIndex2 = edgedof::calcEdgeDoFIndex( vertexIndex1, vertexIndex2 );
   auto edgeIndex3 = edgedof::calcEdgeDoFIndex( vertexIndex0, vertexIndex3 );
   auto edgeIndex4 = edgedof::calcEdgeDoFIndex( vertexIndex1, vertexIndex3 );
   auto edgeIndex5 = edgedof::calcEdgeDoFIndex( vertexIndex2, vertexIndex3 );

   auto edgeOrientation0 = edgedof::calcEdgeDoFOrientation( vertexIndex0, vertexIndex1 );
   auto edgeOrientation1 = edgedof::calcEdgeDoFOrientation( vertexIndex0, vertexIndex2 );
   auto edgeOrientation2 = edgedof::calcEdgeDoFOrientation( vertexIndex1, vertexIndex2 );
   auto edgeOrientation3 = edgedof::calcEdgeDoFOrientation( vertexIndex0, vertexIndex3 );
   auto edgeOrientation4 = edgedof::calcEdgeDoFOrientation( vertexIndex1, vertexIndex3 );
   auto edgeOrientation5 = edgedof::calcEdgeDoFOrientation( vertexIndex2, vertexIndex3 );

   // get local coordinates

   auto xLocal = vertexdof::macrocell::detail::transformToLocalTet( microTet0, microTet1, microTet2, microTet3, coordinates );

   auto x = xLocal[0];
   auto y = xLocal[1];
   auto z = xLocal[2];

   // get DoFs

   const auto tetE0ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex0.x(), edgeIndex0.y(), edgeIndex0.z(), edgeOrientation0 );
   const auto tetE1ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex1.x(), edgeIndex1.y(), edgeIndex1.z(), edgeOrientation1 );
   const auto tetE2ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex2.x(), edgeIndex2.y(), edgeIndex2.z(), edgeOrientation2 );
   const auto tetE3ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex3.x(), edgeIndex3.y(), edgeIndex3.z(), edgeOrientation3 );
   const auto tetE4ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex4.x(), edgeIndex4.y(), edgeIndex4.z(), edgeOrientation4 );
   const auto tetE5ArrayIdx =
       edgedof::macrocell::index( level, edgeIndex5.x(), edgeIndex5.y(), edgeIndex5.z(), edgeOrientation5 );

   auto edgedofData = cell.getData( dataID )->getPointer( level );

   auto valueTetE0 = edgedofData[tetE0ArrayIdx];
   auto valueTetE1 = edgedofData[tetE1ArrayIdx];
   auto valueTetE2 = edgedofData[tetE2ArrayIdx];
   auto valueTetE3 = edgedofData[tetE3ArrayIdx];
   auto valueTetE4 = edgedofData[tetE4ArrayIdx];
   auto valueTetE5 = edgedofData[tetE5ArrayIdx];

   // evaluate function in reference tet

   // basis functions N1E1 phi(x, y, z):
   // TODO use FEniCS ordering (for consistency)
   //   at [0.5 0.  0. ]: (-y-z+1, x     , x     )ᵀ
   //   at [0.  0.5 0. ]: (y     , -x-z+1, y     )ᵀ
   //   at [0.5 0.5 0. ]: (-y    , x     , 0     )ᵀ
   //   at [0.  0.  0.5]: (z     , z     , -x-y+1)ᵀ
   //   at [0.5 0.  0.5]: (-z    , 0     , x     )ᵀ
   //   at [0.  0.5 0.5]: (0     , -z    , y     )ᵀ

   VectorType< ValueType > scaleE0 = valueTetE0 * VectorType< ValueType >{ -y - z + 1, x, x };
   VectorType< ValueType > scaleE1 = valueTetE1 * VectorType< ValueType >{ y, -x - z + 1, y };
   VectorType< ValueType > scaleE2 = valueTetE2 * VectorType< ValueType >{ -y, x, 0 };
   VectorType< ValueType > scaleE3 = valueTetE3 * VectorType< ValueType >{ z, z, -x - y + 1 };
   VectorType< ValueType > scaleE4 = valueTetE4 * VectorType< ValueType >{ -z, 0, x };
   VectorType< ValueType > scaleE5 = valueTetE5 * VectorType< ValueType >{ 0, -z, y };

   VectorType< ValueType > localValue = scaleE0 + scaleE1 + scaleE2 + scaleE3 + scaleE4 + scaleE5;

   // transform to computational space (covariant Piola mapping)

   // TODO precompute and store foctorized A (for each cell type), use also to find xLocal
   Eigen::Matrix3d A;
   A.row( 0 ) = toEigen( microTet1 - microTet0 );
   A.row( 1 ) = toEigen( microTet2 - microTet0 );
   A.row( 2 ) = toEigen( microTet3 - microTet0 );

   return A.fullPivLu().solve( localValue );
}

inline VectorType< real_t > evaluate( const uint_t&                                            level,
                                      const Cell&                                              cell,
                                      const Point3D&                                           coordinates,
                                      const PrimitiveDataID< FunctionMemory< real_t >, Cell >& dataID )
{
   using ValueType = real_t;

   // find microcell which contains `coordinates`
   // note that local coordinates are determined with respect to a different vertex ordering
   // and are therefore wrong!

   indexing::Index   elementIndex;
   celldof::CellType cellType;
   Point3D           wrongLocalCoordinates;

   volumedofspace::getLocalElementFromCoordinates< ValueType >(
       level, cell, coordinates, elementIndex, cellType, wrongLocalCoordinates );

   return evaluateOnMicroElement( level, cell, elementIndex, cellType, coordinates, dataID );
}

inline void add( const uint_t&                                            level,
                 Cell&                                                    cell,
                 const VectorType< real_t >&                              vector,
                 const PrimitiveDataID< FunctionMemory< real_t >, Cell >& dstId )
{
   using ValueType = real_t;

   // x ↦ ∫ₑ x·t dΓ, direction = tangent·length
   // TODO different quadratures
   const ValueType dofScalarX   = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::X ) );
   const ValueType dofScalarY   = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Y ) );
   const ValueType dofScalarZ   = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Z ) );
   const ValueType dofScalarXY  = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XY ) );
   const ValueType dofScalarXZ  = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XZ ) );
   const ValueType dofScalarYZ  = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::YZ ) );
   const ValueType dofScalarXYZ = vector.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XYZ ) );

   auto dstData = cell.getData( dstId )->getPointer( level );

   for ( const auto& it : edgedof::macrocell::Iterator( level ) )
   {
      const uint_t idxX  = edgedof::macrocell::xIndex( level, it.x(), it.y(), it.z() );
      const uint_t idxY  = edgedof::macrocell::yIndex( level, it.x(), it.y(), it.z() );
      const uint_t idxZ  = edgedof::macrocell::zIndex( level, it.x(), it.y(), it.z() );
      const uint_t idxXY = edgedof::macrocell::xyIndex( level, it.x(), it.y(), it.z() );
      const uint_t idxXZ = edgedof::macrocell::xzIndex( level, it.x(), it.y(), it.z() );
      const uint_t idxYZ = edgedof::macrocell::yzIndex( level, it.x(), it.y(), it.z() );

      dstData[idxX] += dofScalarX;
      dstData[idxY] += dofScalarY;
      dstData[idxZ] += dofScalarZ;
      dstData[idxXY] += dofScalarXY;
      dstData[idxXZ] += dofScalarXZ;
      dstData[idxYZ] += dofScalarYZ;
   }

   for ( const auto& it : edgedof::macrocell::IteratorXYZ( level ) )
   {
      const uint_t idxXYZ = edgedof::macrocell::xyzIndex( level, it.x(), it.y(), it.z() );
      dstData[idxXYZ] += dofScalarXYZ;
   }
}

inline void interpolate( const uint_t&                                            level,
                         Cell&                                                    cell,
                         const PrimitiveDataID< FunctionMemory< real_t >, Cell >& cellMemoryId,
                         const VectorType< real_t >&                              constant )
{
   using ValueType = real_t;

   auto cellData = cell.getData( cellMemoryId )->getPointer( level );

   // x ↦ ∫ₑ x·t dΓ, direction = tangent·length
   const ValueType dofScalarX   = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::X ) );
   const ValueType dofScalarY   = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Y ) );
   const ValueType dofScalarZ   = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Z ) );
   const ValueType dofScalarXY  = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XY ) );
   const ValueType dofScalarXZ  = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XZ ) );
   const ValueType dofScalarYZ  = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::YZ ) );
   const ValueType dofScalarXYZ = constant.dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XYZ ) );

   for ( const auto& it : edgedof::macrocell::Iterator( level, 0 ) )
   {
      cellData[edgedof::macrocell::xIndex( level, it.x(), it.y(), it.z() )]  = dofScalarX;
      cellData[edgedof::macrocell::yIndex( level, it.x(), it.y(), it.z() )]  = dofScalarY;
      cellData[edgedof::macrocell::zIndex( level, it.x(), it.y(), it.z() )]  = dofScalarZ;
      cellData[edgedof::macrocell::xyIndex( level, it.x(), it.y(), it.z() )] = dofScalarXY;
      cellData[edgedof::macrocell::xzIndex( level, it.x(), it.y(), it.z() )] = dofScalarXZ;
      cellData[edgedof::macrocell::yzIndex( level, it.x(), it.y(), it.z() )] = dofScalarYZ;
   }

   for ( const auto& it : edgedof::macrocell::IteratorXYZ( level, 0 ) )
   {
      cellData[edgedof::macrocell::xyzIndex( level, it.x(), it.y(), it.z() )] = dofScalarXYZ;
   }
}

inline void
    interpolate( const uint_t&                                                                      level,
                 Cell&                                                                              cell,
                 const PrimitiveDataID< FunctionMemory< real_t >, Cell >&                           cellMemoryId,
                 const std::vector< std::reference_wrapper< const N1E1VectorFunction< real_t > > >& srcFunctions,
                 const std::function< VectorType< real_t >( const Point3D&, const std::vector< VectorType< real_t > >& ) >& expr )
{
   using ValueType = real_t;

   auto cellData = cell.getData( cellMemoryId )->getPointer( level );

   std::vector< VectorType< ValueType > > srcVectorX( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorY( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorZ( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorXY( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorXZ( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorYZ( srcFunctions.size() );
   std::vector< VectorType< ValueType > > srcVectorXYZ( srcFunctions.size() );

   for ( const auto& it : edgedof::macrocell::Iterator( level, 0 ) )
   {
      const Point3D microVertexPosition = vertexdof::macrocell::coordinateFromIndex( level, cell, it );
      const Point3D xMicroEdgePosition  = microVertexPosition + edgedof::macrocell::xShiftFromVertex( level, cell );
      const Point3D yMicroEdgePosition  = microVertexPosition + edgedof::macrocell::yShiftFromVertex( level, cell );
      const Point3D zMicroEdgePosition  = microVertexPosition + edgedof::macrocell::zShiftFromVertex( level, cell );
      const Point3D xyMicroEdgePosition = microVertexPosition + edgedof::macrocell::xShiftFromVertex( level, cell ) +
                                          edgedof::macrocell::yShiftFromVertex( level, cell );
      const Point3D xzMicroEdgePosition = microVertexPosition + edgedof::macrocell::xShiftFromVertex( level, cell ) +
                                          edgedof::macrocell::zShiftFromVertex( level, cell );
      const Point3D yzMicroEdgePosition = microVertexPosition + edgedof::macrocell::yShiftFromVertex( level, cell ) +
                                          edgedof::macrocell::zShiftFromVertex( level, cell );

      Point3D xBlend, yBlend, zBlend, xyBlend, xzBlend, yzBlend;
      cell.getGeometryMap()->evalF( xMicroEdgePosition, xBlend );
      cell.getGeometryMap()->evalF( yMicroEdgePosition, yBlend );
      cell.getGeometryMap()->evalF( zMicroEdgePosition, zBlend );
      cell.getGeometryMap()->evalF( xyMicroEdgePosition, xyBlend );
      cell.getGeometryMap()->evalF( xzMicroEdgePosition, xzBlend );
      cell.getGeometryMap()->evalF( yzMicroEdgePosition, yzBlend );

      for ( uint_t k = 0; k < srcFunctions.size(); ++k )
      {
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorX[k] );
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorY[k] );
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorZ[k] );
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorXY[k] );
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorXZ[k] );
         srcFunctions[k].get().evaluate( xBlend, level, srcVectorYZ[k] );
      }

      // x ↦ ∫ₑ x·t dΓ, direction = tangent·length
      const ValueType dofScalarX =
          expr( xBlend, srcVectorX ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::X ) );
      const ValueType dofScalarY =
          expr( yBlend, srcVectorY ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Y ) );
      const ValueType dofScalarZ =
          expr( zBlend, srcVectorZ ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::Z ) );
      const ValueType dofScalarXY =
          expr( xyBlend, srcVectorXY ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XY ) );
      const ValueType dofScalarXZ =
          expr( xzBlend, srcVectorXZ ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XZ ) );
      const ValueType dofScalarYZ =
          expr( yzBlend, srcVectorYZ ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::YZ ) );

      cellData[edgedof::macrocell::xIndex( level, it.x(), it.y(), it.z() )]  = dofScalarX;
      cellData[edgedof::macrocell::yIndex( level, it.x(), it.y(), it.z() )]  = dofScalarY;
      cellData[edgedof::macrocell::zIndex( level, it.x(), it.y(), it.z() )]  = dofScalarZ;
      cellData[edgedof::macrocell::xyIndex( level, it.x(), it.y(), it.z() )] = dofScalarXY;
      cellData[edgedof::macrocell::xzIndex( level, it.x(), it.y(), it.z() )] = dofScalarXZ;
      cellData[edgedof::macrocell::yzIndex( level, it.x(), it.y(), it.z() )] = dofScalarYZ;
   }

   for ( const auto& it : edgedof::macrocell::IteratorXYZ( level, 0 ) )
   {
      const Point3D microVertexPosition  = vertexdof::macrocell::coordinateFromIndex( level, cell, it );
      const Point3D xyzMicroEdgePosition = microVertexPosition + edgedof::macrocell::xShiftFromVertex( level, cell ) +
                                           edgedof::macrocell::yShiftFromVertex( level, cell ) +
                                           edgedof::macrocell::zShiftFromVertex( level, cell );

      Point3D xyzBlend;
      cell.getGeometryMap()->evalF( xyzMicroEdgePosition, xyzBlend );

      for ( uint_t k = 0; k < srcFunctions.size(); ++k )
      {
         srcFunctions[k].get().evaluate( xyzBlend, level, srcVectorXYZ[k] );
      }

      const ValueType dofScalarXYZ =
          expr( xyzBlend, srcVectorXYZ ).dot( microEdgeDirection( level, cell, edgedof::EdgeDoFOrientation::XYZ ) );

      cellData[edgedof::macrocell::xyzIndex( level, it.x(), it.y(), it.z() )] = dofScalarXYZ;
   }
}

} // namespace macrocell
} // namespace n1e1
} // namespace hyteg
