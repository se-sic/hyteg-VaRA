/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl.
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
#include "P2MacroFace.hpp"

#include "hyteg/Levelinfo.hpp"
#include "hyteg/edgedofspace/EdgeDoFIndexing.hpp"
#include "hyteg/edgedofspace/EdgeDoFMacroFace.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"

namespace hyteg::P2::macroface {

real_t evaluate( const uint_t&                                            level,
                 Face&                                                    face,
                 const Point3D&                                           coordinates,
                 const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcVertexDoFID,
                 const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcEdgeDoFID )
{
   Point2D  localCoordinates; // Coordinates in local element
   Matrix2r transform;        // Temporary transformation matrix

   Point3D localVertexDoFs; // DoFs at the local elements vertices
   Point3D localEdgeDoFs;   // DoFs at the local elements edges

   vertexdof::macroface::getLocalElementDoFIndicesFromCoordinates< real_t >(
       level, face, coordinates, srcVertexDoFID, localCoordinates, transform, localVertexDoFs );

   edgedof::macroface::getLocalElementDoFIndicesFromCoordinates< real_t >(
       level, face, coordinates, srcEdgeDoFID, localCoordinates, transform, localEdgeDoFs );

   real_t L2 = localCoordinates[0];
   real_t L3 = localCoordinates[1];
   real_t L1 = real_c( 1 ) - L2 - L3;

   real_t value = real_c( 0 );

   value += L1 * ( real_c( 2 ) * L1 - real_c( 1 ) ) * localVertexDoFs[0];
   value += L2 * ( real_c( 2 ) * L2 - real_c( 1 ) ) * localVertexDoFs[1];
   value += L3 * ( real_c( 2 ) * L3 - real_c( 1 ) ) * localVertexDoFs[2];

   value += real_c( 4 ) * L2 * L3 * localEdgeDoFs[0];
   value += real_c( 4 ) * L1 * L3 * localEdgeDoFs[1];
   value += real_c( 4 ) * L1 * L2 * localEdgeDoFs[2];

   return value;
}

void evaluateGradient( const uint_t&                                            level,
                       Face&                                                    face,
                       const Point3D&                                           coordinates,
                       const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcVertexDoFID,
                       const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcEdgeDoFID,
                       Point3D&                                                 gradient )
{
   Point2D  localCoordinates; // Coordinates in local element
   Matrix2r transform;        // Temporary transformation matrix

   Point3D localVertexDoFs; // DoFs at the local elements vertices
   Point3D localEdgeDoFs;   // DoFs at the local elements edges

   vertexdof::macroface::getLocalElementDoFIndicesFromCoordinates< real_t >(
       level, face, coordinates, srcVertexDoFID, localCoordinates, transform, localVertexDoFs );

   real_t x = localCoordinates[0];
   real_t y = localCoordinates[1];

   Point2D gradient_;

   gradient_[0] = ( real_c( 4.0 ) * x + real_c( 4.0 ) * y - real_c( 3.0 ) ) * localVertexDoFs[0];
   gradient_[0] += ( real_c( 4.0 ) * x - real_c( 1.0 ) ) * localVertexDoFs[1];

   gradient_[1] = ( real_c( 4.0 ) * x + real_c( 4.0 ) * y - real_c( 3.0 ) ) * localVertexDoFs[0];
   gradient_[1] += ( real_c( 4.0 ) * y - real_c( 1.0 ) ) * localVertexDoFs[2];

   edgedof::macroface::getLocalElementDoFIndicesFromCoordinates< real_t >(
       level, face, coordinates, srcEdgeDoFID, localCoordinates, transform, localEdgeDoFs );

   gradient_[0] += ( real_c( 4.0 ) * y ) * localEdgeDoFs[0];
   gradient_[0] += ( real_c( -4.0 ) * y ) * localEdgeDoFs[1];
   gradient_[0] += ( real_c( -8.0 ) * x - real_c( 4.0 ) * y + real_c( 4.0 ) ) * localEdgeDoFs[2];

   gradient_[1] += ( real_c( 4.0 ) * x ) * localEdgeDoFs[0];
   gradient_[1] += ( real_c( -4.0 ) * x - real_c( 8.0 ) * y + real_c( 4.0 ) ) * localEdgeDoFs[1];
   gradient_[1] += ( real_c( -4.0 ) * x ) * localEdgeDoFs[2];

   gradient_   = transform * gradient_;
   gradient[0] = gradient_[0];
   gradient[1] = gradient_[1];
}

void smoothJacobiVertexDoF( const uint_t&                                            level,
                            const Face&                                              face,
                            const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexDoFStencilID,
                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcVertexDoFID,
                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstVertexDoFID,
                            const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeDoFStencilID,
                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcEdgeDoFID,
                            const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsVertexDoFID,
                            const real_t                                             dampingFactor )
{
   typedef stencilDirection sD;

   real_t* vertexDoFStencil = face.getData( vertexDoFStencilID )->getPointer( level );
   real_t* dstVertexDoF     = face.getData( dstVertexDoFID )->getPointer( level );
   real_t* srcVertexDoF     = face.getData( srcVertexDoFID )->getPointer( level );
   real_t* edgeDoFStencil   = face.getData( edgeDoFStencilID )->getPointer( level );
   real_t* srcEdgeDoF       = face.getData( srcEdgeDoFID )->getPointer( level );
   real_t* rhs              = face.getData( rhsVertexDoFID )->getPointer( level );

   real_t tmp;

   for ( const auto& it : hyteg::vertexdof::macroface::Iterator( level, 1 ) )
   {
      tmp = rhs[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )];

      /// update from vertex dofs
      for ( auto k : vertexdof::macroface::neighborsWithoutCenter )
      {
         tmp -= vertexDoFStencil[vertexdof::stencilIndexFromVertex( k )] *
                srcVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), k )];
      }
      /// update from edge dofs
      for ( auto k : edgedof::macroface::neighborsFromVertex )
      {
         tmp -= edgeDoFStencil[edgedof::stencilIndexFromVertex( k )] *
                srcEdgeDoF[edgedof::macroface::indexFromVertex( level, it.x(), it.y(), k )];
      }
      dstVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )] =
          dampingFactor * ( tmp / vertexDoFStencil[vertexdof::stencilIndexFromVertex( sD::VERTEX_C )] ) +
          ( real_c( 1.0 ) - dampingFactor ) *
              srcVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )];
   }
}

void smoothJacobiEdgeDoF( const uint_t&                                            Level,
                          const Face&                                              face,
                          const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexDoFStencilID,
                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcVertexDoFID,
                          const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeDoFStencilID,
                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& srcEdgeDoFID,
                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstEdgeDoFID,
                          const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsEdgeDoFID,
                          const real_t                                             dampingFactor )
{
   typedef stencilDirection sD;

   real_t* vertexDoFStencil = face.getData( vertexDoFStencilID )->getPointer( Level );
   real_t* srcVertexDoF     = face.getData( srcVertexDoFID )->getPointer( Level );
   real_t* edgeDoFStencil   = face.getData( edgeDoFStencilID )->getPointer( Level );
   real_t* srcEdgeDoF       = face.getData( srcEdgeDoFID )->getPointer( Level );
   real_t* dstEdgeDoF       = face.getData( dstEdgeDoFID )->getPointer( Level );
   real_t* rhs              = face.getData( rhsEdgeDoFID )->getPointer( Level );

   real_t tmp;
   for ( const auto& it : hyteg::edgedof::macroface::Iterator( Level, 0 ) )
   {
      if ( it.y() != 0 )
      {
         tmp = rhs[edgedof::macroface::indexFromHorizontalEdge( Level, it.x(), it.y(), sD::EDGE_HO_C )];
         for ( uint_t k = 1; k < edgedof::macroface::neighborsFromHorizontalEdge.size(); ++k )
         {
            tmp -= edgeDoFStencil[edgedof::stencilIndexFromHorizontalEdge( edgedof::macroface::neighborsFromHorizontalEdge[k] )] *
                   srcEdgeDoF[edgedof::macroface::indexFromHorizontalEdge(
                       Level, it.x(), it.y(), edgedof::macroface::neighborsFromHorizontalEdge[k] )];
         }

         for ( uint_t k = 0; k < vertexdof::macroface::neighborsFromHorizontalEdge.size(); ++k )
         {
            tmp -= vertexDoFStencil[vertexdof::stencilIndexFromHorizontalEdge(
                       vertexdof::macroface::neighborsFromHorizontalEdge[k] )] *
                   srcVertexDoF[vertexdof::macroface::indexFromHorizontalEdge(
                       Level, it.x(), it.y(), vertexdof::macroface::neighborsFromHorizontalEdge[k] )];
         }

         dstEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( Level, it.x(), it.y(), sD::EDGE_HO_C )] =
             dampingFactor * ( tmp / edgeDoFStencil[edgedof::stencilIndexFromHorizontalEdge( sD::EDGE_HO_C )] ) +
             ( 1 - dampingFactor ) *
                 srcEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( Level, it.x(), it.y(), sD::EDGE_HO_C )];
      }
      if ( it.x() + it.y() != idx_t( hyteg::levelinfo::num_microedges_per_edge( Level ) - 1 ) )
      {
         tmp = rhs[edgedof::macroface::indexFromDiagonalEdge( Level, it.x(), it.y(), sD::EDGE_DI_C )];
         for ( uint_t k = 1; k < edgedof::macroface::neighborsFromDiagonalEdge.size(); ++k )
         {
            tmp -= edgeDoFStencil[edgedof::stencilIndexFromDiagonalEdge( edgedof::macroface::neighborsFromDiagonalEdge[k] )] *
                   srcEdgeDoF[edgedof::macroface::indexFromDiagonalEdge(
                       Level, it.x(), it.y(), edgedof::macroface::neighborsFromDiagonalEdge[k] )];
         }

         for ( uint_t k = 0; k < vertexdof::macroface::neighborsFromDiagonalEdge.size(); ++k )
         {
            tmp -=
                vertexDoFStencil[vertexdof::stencilIndexFromDiagonalEdge( vertexdof::macroface::neighborsFromDiagonalEdge[k] )] *
                srcVertexDoF[vertexdof::macroface::indexFromDiagonalEdge(
                    Level, it.x(), it.y(), vertexdof::macroface::neighborsFromDiagonalEdge[k] )];
         }

         dstEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( Level, it.x(), it.y(), sD::EDGE_DI_C )] =
             dampingFactor * ( tmp / edgeDoFStencil[edgedof::stencilIndexFromDiagonalEdge( sD::EDGE_DI_C )] ) +
             ( real_c( 1.0 ) - dampingFactor ) *
                 srcEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( Level, it.x(), it.y(), sD::EDGE_DI_C )];
      }
      if ( it.x() != 0 )
      {
         tmp = rhs[edgedof::macroface::indexFromVerticalEdge( Level, it.x(), it.y(), sD::EDGE_VE_C )];
         for ( uint_t k = 1; k < edgedof::macroface::neighborsFromVerticalEdge.size(); ++k )
         {
            tmp -= edgeDoFStencil[edgedof::stencilIndexFromVerticalEdge( edgedof::macroface::neighborsFromVerticalEdge[k] )] *
                   srcEdgeDoF[edgedof::macroface::indexFromVerticalEdge(
                       Level, it.x(), it.y(), edgedof::macroface::neighborsFromVerticalEdge[k] )];
         }

         for ( uint_t k = 0; k < vertexdof::macroface::neighborsFromVerticalEdge.size(); ++k )
         {
            tmp -=
                vertexDoFStencil[vertexdof::stencilIndexFromVerticalEdge( vertexdof::macroface::neighborsFromVerticalEdge[k] )] *
                srcVertexDoF[vertexdof::macroface::indexFromVerticalEdge(
                    Level, it.x(), it.y(), vertexdof::macroface::neighborsFromVerticalEdge[k] )];
         }

         dstEdgeDoF[edgedof::macroface::indexFromVerticalEdge( Level, it.x(), it.y(), sD::EDGE_VE_C )] =
             dampingFactor * ( tmp / edgeDoFStencil[edgedof::stencilIndexFromVerticalEdge( sD::EDGE_VE_C )] ) +
             ( 1 - dampingFactor ) *
                 srcEdgeDoF[edgedof::macroface::indexFromVerticalEdge( Level, it.x(), it.y(), sD::EDGE_VE_C )];
      }
   }
}

void smoothSOR( const uint_t&                                            level,
                const Face&                                              face,
                const real_t&                                            relax,
                const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexToVertexStencilID,
                const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeToVertexStencilID,
                const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstVertexDoFID,
                const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexToEdgeStencilID,
                const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeToEdgeStencilID,
                const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstEdgeDoFID,
                const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsVertexDoFID,
                const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsEdgeDoFID )
{
   typedef stencilDirection sD;

   real_t* vertexToVertexStencil = face.getData( vertexToVertexStencilID )->getPointer( level );
   real_t* edgeToVertexStencil   = face.getData( edgeToVertexStencilID )->getPointer( level );
   real_t* dstVertexDoF          = face.getData( dstVertexDoFID )->getPointer( level );
   real_t* vertexToEdgeStencil   = face.getData( vertexToEdgeStencilID )->getPointer( level );
   real_t* edgeToEdgeStencil     = face.getData( edgeToEdgeStencilID )->getPointer( level );
   real_t* dstEdgeDoF            = face.getData( dstEdgeDoFID )->getPointer( level );
   real_t* rhsVertexDoF          = face.getData( rhsVertexDoFID )->getPointer( level );
   real_t* rhsEdgeDoF            = face.getData( rhsEdgeDoFID )->getPointer( level );

   real_t tmpVertex = 0, tmpEdgeHO = 0, tmpEdgeDI = 0, tmpEdgeVE = 0;

   // invert center weights
   const real_t invVertexCenter = real_c( 1.0 ) / vertexToVertexStencil[vertexdof::stencilIndexFromVertex( sD::VERTEX_C )];
   const real_t invEdgeXCenter  = real_c( 1.0 ) / edgeToEdgeStencil[edgedof::stencilIndexFromHorizontalEdge( sD::EDGE_HO_C )];
   const real_t invEdgeXYCenter = real_c( 1.0 ) / edgeToEdgeStencil[edgedof::stencilIndexFromDiagonalEdge( sD::EDGE_DI_C )];
   const real_t invEdgeYCenter  = real_c( 1.0 ) / edgeToEdgeStencil[edgedof::stencilIndexFromVerticalEdge( sD::EDGE_VE_C )];

   /// sum up weighted values first for vertex and edges and write to corresponding dof
   for ( const auto& it : hyteg::edgedof::macroface::Iterator( level, 0 ) )
   {
      ////////// VERTEX //////////
      if ( !vertexdof::macroface::isVertexOnBoundary( level, it ) )
      {
         tmpVertex = rhsVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )];
         /// vertex to vertex
         for ( const auto& dir : vertexdof::macroface::neighborsWithoutCenter )
         {
            tmpVertex -= dstVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), dir )] *
                         vertexToVertexStencil[vertexdof::stencilIndexFromVertex( dir )];
         }
         /// edge to vertex
         for ( const auto& dir : edgedof::macroface::neighborsFromVertex )
         {
            tmpVertex -= dstEdgeDoF[edgedof::macroface::indexFromVertex( level, it.x(), it.y(), dir )] *
                         edgeToVertexStencil[edgedof::stencilIndexFromVertex( dir )];
         }
         dstVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )] =
             ( real_c( 1.0 ) - relax ) *
                 dstVertexDoF[vertexdof::macroface::indexFromVertex( level, it.x(), it.y(), sD::VERTEX_C )] +
             relax * invVertexCenter * tmpVertex;
      }
      ////////// HORIZONTAL EDGE //////////
      if ( !edgedof::macroface::isHorizontalEdgeOnBoundary( level, it ) )
      {
         tmpEdgeHO = rhsEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( level, it.x(), it.y(), sD::EDGE_HO_C )];
         /// vertex to edge
         for ( const auto& dir : vertexdof::macroface::neighborsFromHorizontalEdge )
         {
            tmpEdgeHO -= dstVertexDoF[vertexdof::macroface::indexFromHorizontalEdge( level, it.x(), it.y(), dir )] *
                         vertexToEdgeStencil[vertexdof::stencilIndexFromHorizontalEdge( dir )];
         }
         /// edge to edge
         for ( const auto& dir : edgedof::macroface::neighborsFromHorizontalEdgeWithoutCenter )
         {
            tmpEdgeHO -= dstEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( level, it.x(), it.y(), dir )] *
                         edgeToEdgeStencil[edgedof::stencilIndexFromHorizontalEdge( dir )];
         }
         dstEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( level, it.x(), it.y(), sD::EDGE_HO_C )] =
             ( real_c( 1.0 ) - relax ) *
                 dstEdgeDoF[edgedof::macroface::indexFromHorizontalEdge( level, it.x(), it.y(), sD::EDGE_HO_C )] +
             relax * invEdgeXCenter * tmpEdgeHO;
      }
      ////////// VERTICAL EDGE //////////
      if ( !edgedof::macroface::isVerticalEdgeOnBoundary( level, it ) )
      {
         tmpEdgeVE = rhsEdgeDoF[edgedof::macroface::indexFromVerticalEdge( level, it.x(), it.y(), sD::EDGE_VE_C )];
         /// vertex to edge
         for ( const auto& dir : vertexdof::macroface::neighborsFromVerticalEdge )
         {
            tmpEdgeVE -= dstVertexDoF[vertexdof::macroface::indexFromVerticalEdge( level, it.x(), it.y(), dir )] *
                         vertexToEdgeStencil[vertexdof::stencilIndexFromVerticalEdge( dir )];
         }
         /// edge to edge
         for ( const auto& dir : edgedof::macroface::neighborsFromVerticalEdgeWithoutCenter )
         {
            tmpEdgeVE -= dstEdgeDoF[edgedof::macroface::indexFromVerticalEdge( level, it.x(), it.y(), dir )] *
                         edgeToEdgeStencil[edgedof::stencilIndexFromVerticalEdge( dir )];
         }
         dstEdgeDoF[edgedof::macroface::indexFromVerticalEdge( level, it.x(), it.y(), sD::EDGE_VE_C )] =
             ( real_c( 1.0 ) - relax ) *
                 dstEdgeDoF[edgedof::macroface::indexFromVerticalEdge( level, it.x(), it.y(), sD::EDGE_VE_C )] +
             relax * invEdgeYCenter * tmpEdgeVE;
      }
      ////////// DIAGONAL EDGE //////////
      if ( !edgedof::macroface::isDiagonalEdgeOnBoundary( level, it ) )
      {
         tmpEdgeDI = rhsEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( level, it.x(), it.y(), sD::EDGE_DI_C )];
         /// vertex to edge
         for ( const auto& dir : vertexdof::macroface::neighborsFromDiagonalEdge )
         {
            tmpEdgeDI -= dstVertexDoF[vertexdof::macroface::indexFromDiagonalEdge( level, it.x(), it.y(), dir )] *
                         vertexToEdgeStencil[vertexdof::stencilIndexFromDiagonalEdge( dir )];
         }
         /// edge to edge
         for ( const auto& dir : edgedof::macroface::neighborsFromDiagonalEdgeWithoutCenter )
         {
            tmpEdgeDI -= dstEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( level, it.x(), it.y(), dir )] *
                         edgeToEdgeStencil[edgedof::stencilIndexFromDiagonalEdge( dir )];
         }
         dstEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( level, it.x(), it.y(), sD::EDGE_DI_C )] =
             ( real_c( 1.0 ) - relax ) *
                 dstEdgeDoF[edgedof::macroface::indexFromDiagonalEdge( level, it.x(), it.y(), sD::EDGE_DI_C )] +
             relax * invEdgeXYCenter * tmpEdgeDI;
      }
   }
}

void smoothSOR3D(
    const uint_t&                                                                                level,
    const PrimitiveStorage&                                                                      storage,
    const Face&                                                                                  face,
    const real_t&                                                                                relax,
    const PrimitiveDataID< LevelWiseMemory< vertexdof::macroface::StencilMap_T >, Face >&        vertexToVertexOperatorId,
    const PrimitiveDataID< LevelWiseMemory< EdgeDoFToVertexDoF::MacroFaceStencilMap_T >, Face >& edgeToVertexOperatorId,
    const PrimitiveDataID< LevelWiseMemory< VertexDoFToEdgeDoF::MacroFaceStencilMap_T >, Face >& vertexToEdgeOperatorId,
    const PrimitiveDataID< LevelWiseMemory< edgedof::macroface::StencilMap_T >, Face >&          edgeToEdgeOperatorId,
    const PrimitiveDataID< FunctionMemory< real_t >, Face >&                                     vertexDoFDstId,
    const PrimitiveDataID< FunctionMemory< real_t >, Face >&                                     vertexDoFRhsId,
    const PrimitiveDataID< FunctionMemory< real_t >, Face >&                                     edgeDoFDstId,
    const PrimitiveDataID< FunctionMemory< real_t >, Face >&                                     edgeDoFRhsId )
{
   using edgedof::EdgeDoFOrientation;
   using indexing::Index;

   auto v2v_operator = face.getData( vertexToVertexOperatorId )->getData( level );
   auto e2v_operator = face.getData( edgeToVertexOperatorId )->getData( level );
   auto v2e_operator = face.getData( vertexToEdgeOperatorId )->getData( level );
   auto e2e_operator = face.getData( edgeToEdgeOperatorId )->getData( level );

   real_t* vertexDoFDst = face.getData( vertexDoFDstId )->getPointer( level );
   real_t* vertexDoFRhs = face.getData( vertexDoFRhsId )->getPointer( level );
   real_t* edgeDoFDst   = face.getData( edgeDoFDstId )->getPointer( level );
   real_t* edgeDoFRhs   = face.getData( edgeDoFRhsId )->getPointer( level );

   real_t centerWeight = real_c( 0 );
   for ( uint_t neighborCellIdx = 0; neighborCellIdx < face.getNumNeighborCells(); neighborCellIdx++ )
   {
      centerWeight += v2v_operator[neighborCellIdx][{ 0, 0, 0 }];
   }

   const real_t vertexDoFRelaxOverCenter = relax / centerWeight;
   const real_t oneMinusRelax            = real_c( 1 ) - relax;

   real_t tmp;

   // updating vertex unknowns
   for ( const auto& centerIndexInFace : hyteg::vertexdof::macroface::Iterator( level, 1 ) )
   {
      const auto dstIdx = vertexdof::macroface::index( level, centerIndexInFace.x(), centerIndexInFace.y() );
      tmp               = vertexDoFRhs[dstIdx];

      for ( uint_t neighborCellIdx = 0; neighborCellIdx < face.getNumNeighborCells(); neighborCellIdx++ )
      {
         auto neighborCell = storage.getCell( face.neighborCells().at( neighborCellIdx ) );
         auto centerIndexInCell =
             vertexdof::macroface::getIndexInNeighboringMacroCell( centerIndexInFace, face, neighborCellIdx, storage, level );
         for ( const auto& stencilIt : v2v_operator[neighborCellIdx] )
         {
            if ( stencilIt.first == indexing::Index( { 0, 0, 0 } ) )
               continue;

            auto weight               = stencilIt.second;
            auto leafIndexInMacroCell = centerIndexInCell + stencilIt.first;
            auto leafIndexInMacroFace = vertexdof::macrocell::getIndexInNeighboringMacroFace(
                leafIndexInMacroCell, *neighborCell, neighborCell->getLocalFaceID( face.getID() ), storage, level );

            uint_t leafArrayIndexInMacroFace;
            if ( leafIndexInMacroFace.z() == 0 )
            {
               leafArrayIndexInMacroFace =
                   vertexdof::macroface::index( level, leafIndexInMacroFace.x(), leafIndexInMacroFace.y() );
            }
            else
            {
               WALBERLA_ASSERT_EQUAL( leafIndexInMacroFace.z(), 1 );
               leafArrayIndexInMacroFace =
                   vertexdof::macroface::index( level, leafIndexInMacroFace.x(), leafIndexInMacroFace.y(), neighborCellIdx );
            }

            tmp -= weight * vertexDoFDst[leafArrayIndexInMacroFace];
         }
      }

      // edge leaves
      for ( uint_t neighborCellID = 0; neighborCellID < face.getNumNeighborCells(); neighborCellID++ )
      {
         const Cell&  neighborCell = *( storage.getCell( face.neighborCells().at( neighborCellID ) ) );
         const uint_t localFaceID  = neighborCell.getLocalFaceID( face.getID() );

         const auto centerIndexInCell =
             vertexdof::macroface::getIndexInNeighboringMacroCell( centerIndexInFace, face, neighborCellID, storage, level );

         WALBERLA_ASSERT_GREATER( vertexdof::macrocell::isOnCellFace( centerIndexInCell, level ).size(), 0 );

         for ( const auto& leafOrientation : edgedof::allEdgeDoFOrientations )
         {
            for ( const auto& stencilIt : e2v_operator[neighborCellID][leafOrientation] )
            {
               const auto stencilOffset = stencilIt.first;
               const auto stencilWeight = stencilIt.second;

               const auto leafOrientationInFace = edgedof::macrocell::getOrientationInNeighboringMacroFace(
                   leafOrientation, neighborCell, localFaceID, storage );

               const auto leafIndexInCell = centerIndexInCell + stencilOffset;
               const auto leafIndexInFace = leafOrientation == edgedof::EdgeDoFOrientation::XYZ ?
                                                edgedof::macrocell::getIndexInNeighboringMacroFaceXYZ(
                                                    leafIndexInCell, neighborCell, localFaceID, storage, level ) :
                                                edgedof::macrocell::getIndexInNeighboringMacroFace(
                                                    leafIndexInCell, neighborCell, localFaceID, storage, level );

               WALBERLA_ASSERT_LESS_EQUAL( leafIndexInFace.z(), 1 );

               uint_t leafArrayIndexInFace;
               if ( algorithms::contains( edgedof::faceLocalEdgeDoFOrientations, leafOrientationInFace ) &&
                    leafIndexInFace.z() == 0 )
               {
                  leafArrayIndexInFace =
                      edgedof::macroface::index( level, leafIndexInFace.x(), leafIndexInFace.y(), leafOrientationInFace );
               }
               else
               {
                  leafArrayIndexInFace = edgedof::macroface::index(
                      level, leafIndexInFace.x(), leafIndexInFace.y(), leafOrientationInFace, neighborCellID );
               }

               tmp -= stencilWeight * edgeDoFDst[leafArrayIndexInFace];
            }
         }
      }

      vertexDoFDst[dstIdx] = oneMinusRelax * vertexDoFDst[dstIdx] + vertexDoFRelaxOverCenter * tmp;
   }

   // updating edge unknowns
   for ( const auto& centerIndexInFace : hyteg::edgedof::macroface::Iterator( level, 0 ) )
   {
      for ( const auto& faceCenterOrientation : edgedof::faceLocalEdgeDoFOrientations )
      {
         if ( faceCenterOrientation == edgedof::EdgeDoFOrientation::X &&
              edgedof::macroface::isHorizontalEdgeOnBoundary( level, centerIndexInFace ) )
            continue;
         if ( faceCenterOrientation == edgedof::EdgeDoFOrientation::Y &&
              edgedof::macroface::isVerticalEdgeOnBoundary( level, centerIndexInFace ) )
            continue;
         if ( faceCenterOrientation == edgedof::EdgeDoFOrientation::XY &&
              edgedof::macroface::isDiagonalEdgeOnBoundary( level, centerIndexInFace ) )
            continue;

         const auto dstIdx =
             edgedof::macroface::index( level, centerIndexInFace.x(), centerIndexInFace.y(), faceCenterOrientation );
         tmp = edgeDoFRhs[dstIdx];

         real_t e2eDiagonalEntry = 0;

         for ( uint_t neighborCellID = 0; neighborCellID < face.getNumNeighborCells(); neighborCellID++ )
         {
            const Cell&  neighborCell = *( storage.getCell( face.neighborCells().at( neighborCellID ) ) );
            const uint_t localFaceID  = neighborCell.getLocalFaceID( face.getID() );

            const auto centerIndexInCell =
                edgedof::macroface::getIndexInNeighboringMacroCell( centerIndexInFace, face, neighborCellID, storage, level );
            const auto cellCenterOrientation =
                edgedof::macroface::getOrientationInNeighboringMacroCell( faceCenterOrientation, face, neighborCellID, storage );

            // vertex leaves
            for ( const auto& stencilIt : v2e_operator[neighborCellID][cellCenterOrientation] )
            {
               const auto stencilOffset = stencilIt.first;
               const auto stencilWeight = stencilIt.second;

               const auto leafIndexInCell = centerIndexInCell + stencilOffset;
               const auto leafIndexInFace = vertexdof::macrocell::getIndexInNeighboringMacroFace(
                   leafIndexInCell, neighborCell, localFaceID, storage, level );

               WALBERLA_ASSERT_LESS_EQUAL( leafIndexInFace.z(), 1 );

               uint_t leafArrayIndexInFace;
               if ( leafIndexInFace.z() == 0 )
               {
                  leafArrayIndexInFace = vertexdof::macroface::index( level, leafIndexInFace.x(), leafIndexInFace.y() );
               }
               else
               {
                  leafArrayIndexInFace =
                      vertexdof::macroface::index( level, leafIndexInFace.x(), leafIndexInFace.y(), neighborCellID );
               }

               tmp -= stencilWeight * vertexDoFDst[leafArrayIndexInFace];
            }

            // edge leaves
            for ( const auto& leafOrientation : edgedof::allEdgeDoFOrientations )
            {
               for ( const auto& stencilIt : e2e_operator[neighborCellID][cellCenterOrientation][leafOrientation] )
               {
                  const auto stencilOffset = stencilIt.first;
                  const auto stencilWeight = stencilIt.second;

                  if ( leafOrientation == cellCenterOrientation && stencilOffset == Index( 0, 0, 0 ) )
                  {
                     e2eDiagonalEntry += stencilWeight;
                     continue;
                  }

                  const auto leafOrientationInFace = edgedof::macrocell::getOrientationInNeighboringMacroFace(
                      leafOrientation, neighborCell, localFaceID, storage );

                  const auto leafIndexInCell = centerIndexInCell + stencilOffset;
                  const auto leafIndexInFace = leafOrientation == edgedof::EdgeDoFOrientation::XYZ ?
                                                   edgedof::macrocell::getIndexInNeighboringMacroFaceXYZ(
                                                       leafIndexInCell, neighborCell, localFaceID, storage, level ) :
                                                   edgedof::macrocell::getIndexInNeighboringMacroFace(
                                                       leafIndexInCell, neighborCell, localFaceID, storage, level );

                  WALBERLA_ASSERT_LESS_EQUAL( leafIndexInFace.z(), 1 );

                  uint_t leafArrayIndexInFace;
                  if ( algorithms::contains( edgedof::faceLocalEdgeDoFOrientations, leafOrientationInFace ) &&
                       leafIndexInFace.z() == 0 )
                  {
                     leafArrayIndexInFace =
                         edgedof::macroface::index( level, leafIndexInFace.x(), leafIndexInFace.y(), leafOrientationInFace );
                  }
                  else
                  {
                     leafArrayIndexInFace = edgedof::macroface::index(
                         level, leafIndexInFace.x(), leafIndexInFace.y(), leafOrientationInFace, neighborCellID );
                  }

                  tmp -= stencilWeight * edgeDoFDst[leafArrayIndexInFace];
               }
            }
         }

         edgeDoFDst[dstIdx] = oneMinusRelax * edgeDoFDst[dstIdx] + ( relax / e2eDiagonalEntry ) * tmp;
      }
   }
}

void smoothGaussSeidel( const uint_t&                                            level,
                        const Face&                                              face,
                        const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexToVertexStencilID,
                        const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeToVertexStencilID,
                        const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstVertexDoFID,
                        const PrimitiveDataID< StencilMemory< real_t >, Face >&  vertexToEdgeStencilID,
                        const PrimitiveDataID< StencilMemory< real_t >, Face >&  edgeToEdgeStencilID,
                        const PrimitiveDataID< FunctionMemory< real_t >, Face >& dstEdgeDoFID,
                        const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsVertexDoFID,
                        const PrimitiveDataID< FunctionMemory< real_t >, Face >& rhsEdgeDoFID )
{
   smoothSOR( level,
              face,
              real_c( 1.0 ),
              vertexToVertexStencilID,
              edgeToVertexStencilID,
              dstVertexDoFID,
              vertexToEdgeStencilID,
              edgeToEdgeStencilID,
              dstEdgeDoFID,
              rhsVertexDoFID,
              rhsEdgeDoFID );
}

} // namespace hyteg::P2::macroface
