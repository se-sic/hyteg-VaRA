/*
* Copyright (c) 2017-2022 Nils Kohl.
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

#include <hyteg/communication/Syncing.hpp>

#include "hyteg/celldofspace/CellDoFIndexing.hpp"
#include "hyteg/dgfunctionspace/DGFormAbort.hpp"
#include "hyteg/dgfunctionspace/DGFunction.hpp"
#include "hyteg/dgfunctionspace/P1_to_P0_div_form.hpp"
#include "hyteg/functions/Function.hpp"
#include "hyteg/indexing/Common.hpp"
#include "hyteg/indexing/MacroCellIndexing.hpp"
#include "hyteg/indexing/MacroEdgeIndexing.hpp"
#include "hyteg/indexing/MacroFaceIndexing.hpp"
#include "hyteg/memory/FunctionMemory.hpp"
#include "hyteg/operators/Operator.hpp"
#include "hyteg/p0functionspace/P0Function.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"
#include "hyteg/solvers/Smoothables.hpp"

namespace hyteg {

using namespace dg;
using facedof::FaceType;
using indexing::Index;
using volumedofspace::indexing::VolumeDoFMemoryLayout;
using walberla::int_c;
using walberla::real_t;

template < typename Form >
class P1ToP0Operator : public Operator< P1Function< real_t >, P0Function< real_t > >
{
 public:
   P1ToP0Operator( const std::shared_ptr< PrimitiveStorage >& storage, uint_t minLevel, uint_t maxLevel )
   : Operator< P1Function< real_t >, P0Function< real_t > >( storage, minLevel, maxLevel )
   , form_( std::make_shared< Form >() )
   {}

   void apply( const P1Function< real_t >& src,
               const P0Function< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override
   {
      assembleAndOrApply( src, dst, level, flag, nullptr, updateType );
   }

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const P1Function< idx_t >&                  src,
                  const P0Function< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override
   {
      assembleAndOrApply( src, dst, level, flag, mat, Replace );
   }

 private:
   template < typename VType >
   VType* p1Data( const P1Function< VType >&                 function,
                  const std::shared_ptr< PrimitiveStorage >& storage,
                  const PrimitiveID&                         pid,
                  uint_t                                     level ) const
   {
      if ( storage->hasGlobalCells() )
      {
         WALBERLA_ASSERT( storage->cellExistsLocally( pid ) );
         auto cell = storage->getCell( pid );
         return cell->getData( function.getCellDataID() )->getPointer( level );
      }
      else
      {
         WALBERLA_ASSERT( storage->faceExistsLocally( pid ) );
         auto face = storage->getFace( pid );
         return face->getData( function.getFaceDataID() )->getPointer( level );
      }
   }

   /// \brief This is similar to the implementation in the dg::DGOperator class.
   template < typename VType >
   inline void assembleAndOrApply( const P1Function< VType >&                  src,
                                   const P0Function< VType >&                  dst,
                                   size_t                                      level,
                                   DoFType                                     flag,
                                   const std::shared_ptr< SparseMatrixProxy >& mat,
                                   UpdateType                                  updateType = Replace ) const
   {
      // To avoid code duplication in this already long method, the implementation "fuses" the 2D and 3D implementation.
      // This more or less serves as a reference - for better performance the matrix-vector multiplication should be specialized.

      DGBasisLinearLagrange_Example srcBasis;

      using indexing::Index;
      using volumedofspace::indexing::ElementNeighborInfo;

      communication::syncFunctionBetweenPrimitives( src, level );

      if ( !storage_->hasGlobalCells() )
      {
         src.template communicate< Face, Face >( level );
      }
      else
      {
         WALBERLA_ABORT( "Not implemented." );
      }

      const auto storage = this->getStorage();

      int dim = 2;
      if ( storage->hasGlobalCells() )
      {
         dim = 3;
      }

      std::vector< PrimitiveID > pids;
      if ( dim == 2 )
      {
         pids = storage->getFaceIDs();
      }
      else
      {
         pids = storage->getCellIDs();
      }

      for ( const auto& pid : pids )
      {
         const auto srcPolyDegree = 1;
         const auto dstPolyDegree = 0;

         const auto numSrcDofs = dim + 1;
         const auto numDstDofs = 1;

         const auto srcDofMemory = p1Data< VType >( src, storage, pid, level );
         auto       dstDofMemory = dst.getDGFunction()->volumeDoFFunction()->dofMemory( pid, level );

         const auto dstMemLayout = dst.getDGFunction()->volumeDoFFunction()->memoryLayout();

         std::map< uint_t, VType* > glMemory;

         if ( dim == 2 )
         {
            WALBERLA_ASSERT( storage->faceExistsLocally( pid ) );
            const auto face = storage->getFace( pid );
            for ( const auto& [n, _] : face->getIndirectNeighborFaceIDsOverEdges() )
            {
               glMemory[n] = face->getData( src.getFaceGLDataID( n ) )->getPointer( level );
            }
         }
         else
         {
            WALBERLA_ASSERT( storage->cellExistsLocally( pid ) );
            const auto cell = storage->getCell( pid );
            for ( const auto& [n, _] : cell->getIndirectNeighborCellIDsOverFaces() )
            {
               glMemory[n] = cell->getData( src.getCellGLDataID( n ) )->getPointer( level );
            }
         }

         const uint_t numMicroVolTypes = ( storage->hasGlobalCells() ? 6 : 2 );

         for ( uint_t microVolType = 0; microVolType < numMicroVolTypes; microVolType++ )
         {
            if ( dim == 2 && microVolType >= 2 )
            {
               break;
            }

            auto faceType = facedof::allFaceTypes[microVolType];
            auto cellType = celldof::allCellTypes[microVolType];

            auto itFace = facedof::macroface::Iterator( level, faceType ).begin();
            auto itCell = celldof::macrocell::Iterator( level, cellType ).begin();

            while ( ( dim == 2 && itFace != itFace.end() ) || ( dim == 3 && itCell != itCell.end() ) )
            {
               Index elementIdx;

               if ( dim == 2 )
               {
                  elementIdx = *itFace;
                  itFace++;
               }
               else
               {
                  elementIdx = *itCell;
                  itCell++;
               }

               // TODO: all these coord computations can be executed _once_ and then the coordinates can be incremented by h
               // TODO: blending

               // This object does the heavy lifting of computing all required coordinates and normals.
               ElementNeighborInfo neighborInfo;

               if ( dim == 2 )
               {
                  neighborInfo = ElementNeighborInfo( elementIdx, faceType, level, src.getBoundaryCondition(), pid, storage_ );
               }
               else
               {
                  neighborInfo = ElementNeighborInfo( elementIdx, cellType, level, src.getBoundaryCondition(), pid, storage_ );
               }

               // We only write to the DoFs in the current volume, let's prepare a temporary vector for that.
               Eigen::Matrix< real_t, Eigen::Dynamic, 1 > dstDofs;
               dstDofs.resize( numDstDofs, Eigen::NoChange_t::NoChange );
               dstDofs.setZero();

               /////////////////////////
               // Volume contribution //
               /////////////////////////

               Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic > localMat;
               localMat.resize( numDstDofs, numSrcDofs );

               // Little difference here is that the source is now a CG P1 function.
               // So we need to obtain the DoFs a little differently and set the basis manually.

               form_->integrateVolume( dim,
                                       neighborInfo.elementVertexCoords(),
                                       srcBasis,
                                       *dst.getDGFunction()->basis(),
                                       srcPolyDegree,
                                       dstPolyDegree,
                                       localMat );

               Eigen::Matrix< real_t, Eigen::Dynamic, 1 > srcDofs;
               srcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );

               // Getting the vertex DoF indices for the current micro volume.
               std::vector< Index > vertexDoFIndices;
               if ( dim == 2 )
               {
                  auto vertexDoFIndicesArray = facedof::macroface::getMicroVerticesFromMicroFace( elementIdx, faceType );
                  vertexDoFIndices.insert( vertexDoFIndices.begin(), vertexDoFIndicesArray.begin(), vertexDoFIndicesArray.end() );
               }
               else
               {
                  auto vertexDoFIndicesArray = celldof::macrocell::getMicroVerticesFromMicroCell( elementIdx, cellType );
                  vertexDoFIndices.insert( vertexDoFIndices.begin(), vertexDoFIndicesArray.begin(), vertexDoFIndicesArray.end() );
               }

               for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
               {
                  if ( dim == 2 )
                  {
                     srcDofs( srcDofIdx ) = srcDofMemory[vertexdof::macroface::index(
                         level, vertexDoFIndices[srcDofIdx].x(), vertexDoFIndices[srcDofIdx].y() )];
                  }
                  else
                  {
                     srcDofs( srcDofIdx ) = srcDofMemory[vertexdof::macrocell::index( level,
                                                                                      vertexDoFIndices[srcDofIdx].x(),
                                                                                      vertexDoFIndices[srcDofIdx].y(),
                                                                                      vertexDoFIndices[srcDofIdx].z() )];
                  }
               }

               if ( mat == nullptr )
               {
                  // Matrix-vector multiplication.
                  dstDofs += localMat * srcDofs;
               }
               else
               {
                  // Sparse assembly.
                  for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                  {
                     if ( dim == 2 )
                     {
                        const auto globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                            elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, dstMemLayout )];
                        const auto globalColIdx = srcDofMemory[vertexdof::macroface::index(
                            level, vertexDoFIndices[srcDofIdx].x(), vertexDoFIndices[srcDofIdx].y() )];
                        mat->addValue( globalRowIdx, globalColIdx, localMat( 0, Eigen::Index( srcDofIdx ) ) );
                     }
                     else
                     {
                        WALBERLA_ABORT( "Not implemented." );
                     }
                  }
               }

               if ( !form_->onlyVolumeIntegrals() )
               {
                  /////////////////////////////
                  // Interface contributions //
                  /////////////////////////////

                  // Loop over neighboring volumes.
                  for ( uint_t n = 0; n < uint_c( dim + 1 ); n++ )
                  {
                     /////////////////////
                     // Domain boundary //
                     /////////////////////

                     if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == DirichletBoundary )
                     {
                        ////////////////////////
                        // Dirichlet boundary //
                        ////////////////////////

                        localMat.setZero();
                        form_->integrateFacetDirichletBoundary( dim,
                                                                neighborInfo.elementVertexCoords(),
                                                                neighborInfo.interfaceVertexCoords( n ),
                                                                neighborInfo.oppositeVertexCoords( n ),
                                                                neighborInfo.outwardNormal( n ),
                                                                srcBasis,
                                                                *dst.getDGFunction()->basis(),
                                                                srcPolyDegree,
                                                                dstPolyDegree,
                                                                localMat );

                        if ( mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * srcDofs;
                        }
                        else
                        {
                           // Sparse assembly.
                           for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 const auto globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                                     elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, dstMemLayout )];
                                 const auto globalColIdx = srcDofMemory[vertexdof::macroface::index(
                                     level, vertexDoFIndices[srcDofIdx].x(), vertexDoFIndices[srcDofIdx].y() )];
                                 mat->addValue( globalRowIdx, globalColIdx, localMat( 0, Eigen::Index( srcDofIdx ) ) );
                              }
                              else
                              {
                                 WALBERLA_ABORT( "Not implemented." );
                              }
                           }
                        }
                     }
                     else if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == NeumannBoundary )
                     {
                        WALBERLA_ABORT( "Neumann boundary handling not implemented." );
                     }
                     else if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == FreeslipBoundary )
                     {
                        WALBERLA_ABORT( "Free-slip boundary handling not implemented." );
                     }

                     //////////////////
                     // Inner domain //
                     //////////////////

                     else
                     {
                        ///////////////////////////////////
                        // a) inner element contribution //
                        ///////////////////////////////////

                        localMat.setZero();
                        form_->integrateFacetInner( dim,
                                                    neighborInfo.elementVertexCoords(),
                                                    neighborInfo.interfaceVertexCoords( n ),
                                                    neighborInfo.oppositeVertexCoords( n ),
                                                    neighborInfo.outwardNormal( n ),
                                                    srcBasis,
                                                    *dst.getDGFunction()->basis(),
                                                    srcPolyDegree,
                                                    dstPolyDegree,
                                                    localMat );

                        if ( mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * srcDofs;
                        }
                        else
                        {
                           // Sparse assembly.
                           for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 const auto globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                                     elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, dstMemLayout )];
                                 const auto globalColIdx = srcDofMemory[vertexdof::macroface::index(
                                     level, vertexDoFIndices[srcDofIdx].x(), vertexDoFIndices[srcDofIdx].y() )];
                                 mat->addValue( globalRowIdx, globalColIdx, localMat( 0, Eigen::Index( srcDofIdx ) ) );
                              }
                              else
                              {
                                 WALBERLA_ABORT( "Not implemented." );
                              }
                           }
                        }

                        ////////////////////////////////////////
                        // b) coupling to neighboring element //
                        ////////////////////////////////////////

                        if ( neighborInfo.atMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == Inner )
                        {
                           ////////////////////////////////////////////////
                           // i) micro-interface on macro-macro-boundary //
                           ////////////////////////////////////////////////

                           // The neighboring micro-element coords have to be computed since they are now different as for an
                           // element on the same macro-volume.
                           std::vector< Index >                         neighborElementVertexIndices;
                           std::vector< Eigen::Matrix< real_t, 3, 1 > > neighborElementVertexCoords;
                           Eigen::Matrix< real_t, 3, 1 >                neighborOppositeVertexCoords;

                           neighborInfo.macroBoundaryNeighborElementVertexCoords(
                               n, neighborElementVertexIndices, neighborElementVertexCoords, neighborOppositeVertexCoords );

                           localMat.setZero();
                           form_->integrateFacetCoupling( dim,
                                                          neighborInfo.elementVertexCoords(),
                                                          neighborElementVertexCoords,
                                                          neighborInfo.interfaceVertexCoords( n ),
                                                          neighborInfo.oppositeVertexCoords( n ),
                                                          neighborOppositeVertexCoords,
                                                          neighborInfo.outwardNormal( n ),
                                                          srcBasis,
                                                          *dst.getDGFunction()->basis(),
                                                          srcPolyDegree,
                                                          dstPolyDegree,
                                                          localMat );

                           // --- START vertex DoF GL handling at macro-macro boundary -------------------------------------------

                           // Now we need the vertex DoFs (i.e. their indices) from the neighboring element.
                           //
                           // Those are partly on the current macro, and partly on the ghost-layer. This makes things a little
                           // more difficult for the CG element. We have to make sure that the order in which we plug in the
                           // element coords into the form is the same order we put the src vertex DoFs.
                           //
                           // What we have at hand are the local micro-vertices from the perspective of the neighboring macro in
                           // the correct order. Looping over those, we translate the indices to the indices of the micro-vertices
                           // local to the dst macro. One of those is _not_ located on the macro-macro-boundary. This is the
                           // micro-vertex that must be taken from the ghost-layer.

                           Eigen::Matrix< real_t, Eigen::Dynamic, 1 > nSrcDofs;
                           nSrcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );
                           std::vector< uint_t > nSrcDoFArrIndices( numSrcDofs );
                           std::vector< bool >   onGhostLayer( numSrcDofs );

                           if ( !storage->hasGlobalCells() )
                           {
                              // 2D
                              const auto face         = storage->getFace( pid );
                              const auto edgePID      = face->neighborEdges().at( neighborInfo.macroBoundaryID( n ) );
                              const auto neighborFace = storage->getFace(
                                  face->getIndirectNeighborFaceIDsOverEdges().at( neighborInfo.macroBoundaryID( n ) ) );
                              const auto localEdgeIDNeighborFace = neighborFace->edge_index( edgePID );

                              for ( uint_t i = 0; i < neighborElementVertexIndices.size(); i++ )
                              {
                                 const auto nElementVertexIdx = neighborElementVertexIndices[i];

                                 // Check vertex DoF on interface or ghost-layer.
                                 switch ( localEdgeIDNeighborFace )
                                 {
                                 case 0:
                                    onGhostLayer[i] = nElementVertexIdx.y() != 0;
                                    break;
                                 case 1:
                                    onGhostLayer[i] = nElementVertexIdx.x() != 0;
                                    break;
                                 case 2:
                                    onGhostLayer[i] = nElementVertexIdx.x() + nElementVertexIdx.y() !=
                                                      levelinfo::num_microvertices_per_edge( level ) - 1;
                                    break;
                                 }

                                 if ( !onGhostLayer[i] )
                                 {
                                    // If the DoF is not on the ghost-layer (i.e. it is on the interface) we need to obtain the
                                    // logical index on the local macro volume. This is done via index "basis trafo".

                                    std::array< uint_t, 4 > srcBasis;
                                    for ( uint_t ii = 0; ii < 3; ii++ )
                                    {
                                       if ( algorithms::contains( face->neighborVertices(),
                                                                  neighborFace->neighborVertices().at( ii ) ) )
                                       {
                                          srcBasis[ii] = face->vertex_index( neighborFace->neighborVertices().at( ii ) );
                                       }
                                       else
                                       {
                                          srcBasis[ii] = face->vertex_index( face->get_vertex_opposite_to_edge(
                                              face->neighborEdges().at( neighborInfo.macroBoundaryID( n ) ) ) );
                                       }
                                    }
                                    srcBasis[3] = 3;

                                    // Basis trafo to local macro.
                                    const auto localIndex =
                                        indexing::basisConversion( nElementVertexIdx,
                                                                   srcBasis,
                                                                   { 0, 1, 2, 3 },
                                                                   levelinfo::num_microvertices_per_edge( level ) );
                                    nSrcDoFArrIndices[i] = vertexdof::macroface::index( level, localIndex.x(), localIndex.y() );
                                    nSrcDofs[i]          = srcDofMemory[nSrcDoFArrIndices[i]];
                                 }
                                 else
                                 {
                                    // Take DoF from GL memory.
                                    nSrcDoFArrIndices[i] = volumedofspace::indexing::indexNeighborInGhostLayer(
                                        neighborInfo.macroBoundaryID( n ),
                                        elementIdx.x(),
                                        elementIdx.y(),
                                        faceType,
                                        0,
                                        1,
                                        level,
                                        volumedofspace::indexing::VolumeDoFMemoryLayout::AoS );
                                    nSrcDofs[i] = glMemory[neighborInfo.macroBoundaryID( n )][nSrcDoFArrIndices[i]];
                                 }
                              }
                           }
                           else
                           {
                              // 3D
                              WALBERLA_ABORT( "Not implemented for 3D." );
                           }

                           // --- END vertex DoF GL handling at macro-macro boundary ---------------------------------------------

                           if ( mat == nullptr )
                           {
                              // Matrix-vector multiplication.
                              dstDofs += localMat * nSrcDofs;
                           }
                           else
                           {
                              // Sparse assembly.
                              for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                              {
                                 uint_t globalColIdx, globalRowIdx;
                                 if ( dim == 2 )
                                 {
                                    globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                                        elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, dstMemLayout )];
                                 }
                                 else
                                 {
                                    globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                                        elementIdx.x(), elementIdx.y(), elementIdx.z(), cellType, 0, 1, level, dstMemLayout )];
                                 }

                                 if ( !onGhostLayer[srcDofIdx] )
                                 {
                                    globalColIdx = srcDofMemory[nSrcDoFArrIndices[srcDofIdx]];
                                 }
                                 else
                                 {
                                    globalColIdx = glMemory[neighborInfo.macroBoundaryID( n )][nSrcDoFArrIndices[srcDofIdx]];
                                 }

                                 mat->addValue( globalRowIdx, globalColIdx, localMat( 0, srcDofIdx ) );
                              }
                           }
                        }
                        else
                        {
                           /////////////////////////////////////////
                           // ii) micro-interface inside of macro //
                           /////////////////////////////////////////

                           localMat.setZero();
                           form_->integrateFacetCoupling( dim,
                                                          neighborInfo.elementVertexCoords(),
                                                          neighborInfo.neighborElementVertexCoords( n ),
                                                          neighborInfo.interfaceVertexCoords( n ),
                                                          neighborInfo.oppositeVertexCoords( n ),
                                                          neighborInfo.neighborOppositeVertexCoords( n ),
                                                          neighborInfo.outwardNormal( n ),
                                                          srcBasis,
                                                          *dst.getDGFunction()->basis(),
                                                          srcPolyDegree,
                                                          dstPolyDegree,
                                                          localMat );

                           // Now we need the DoFs from the neighboring element.
                           Eigen::Matrix< real_t, Eigen::Dynamic, 1 > nSrcDofs;
                           nSrcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );

                           std::vector< Index > nVertexDoFIndices;
                           if ( dim == 2 )
                           {
                              auto nVertexDoFIndicesArray = facedof::macroface::getMicroVerticesFromMicroFace(
                                  neighborInfo.neighborElementIndices( n ), neighborInfo.neighborFaceType( n ) );
                              nVertexDoFIndices.insert(
                                  nVertexDoFIndices.begin(), nVertexDoFIndicesArray.begin(), nVertexDoFIndicesArray.end() );
                           }
                           else
                           {
                              auto nVertexDoFIndicesArray = celldof::macrocell::getMicroVerticesFromMicroCell(
                                  neighborInfo.neighborElementIndices( n ), neighborInfo.neighborCellType( n ) );
                              nVertexDoFIndices.insert(
                                  nVertexDoFIndices.begin(), nVertexDoFIndicesArray.begin(), nVertexDoFIndicesArray.end() );
                           }

                           for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                           {
                              if ( dim == 2 )
                              {
                                 nSrcDofs( Eigen::Index( srcDofIdx ) ) = srcDofMemory[vertexdof::macroface::index(
                                     level, nVertexDoFIndices[srcDofIdx].x(), nVertexDoFIndices[srcDofIdx].y() )];
                              }
                              else
                              {
                                 nSrcDofs( Eigen::Index( srcDofIdx ) ) =
                                     srcDofMemory[vertexdof::macrocell::index( level,
                                                                               nVertexDoFIndices[srcDofIdx].x(),
                                                                               nVertexDoFIndices[srcDofIdx].y(),
                                                                               nVertexDoFIndices[srcDofIdx].z() )];
                              }
                           }

                           if ( mat == nullptr )
                           {
                              // Matrix-vector multiplication.
                              dstDofs += localMat * nSrcDofs;
                           }
                           else
                           {
                              // TODO: improve this monster
                              std::map< facedof::FaceType, uint_t > invFaceTypeMap;
                              std::map< celldof::CellType, uint_t > invCellTypeMap;

                              for ( uint_t i = 0; i < 2; i++ )
                              {
                                 invFaceTypeMap[facedof::allFaceTypes[i]] = i;
                              }
                              for ( uint_t i = 0; i < 6; i++ )
                              {
                                 invCellTypeMap[celldof::allCellTypes[i]] = i;
                              }

                              uint_t neighborMicroVolType;
                              if ( dim == 2 )
                              {
                                 neighborMicroVolType = invFaceTypeMap[neighborInfo.neighborFaceType( n )];
                              }
                              else
                              {
                                 neighborMicroVolType = invCellTypeMap[neighborInfo.neighborCellType( n )];
                              }
                              // Sparse assembly.
                              for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                              {
                                 if ( dim == 2 )
                                 {
                                    const auto globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                                        elementIdx.x(), elementIdx.y(), faceType, 0, 1, level, dstMemLayout )];
                                    const auto globalColIdx = srcDofMemory[vertexdof::macroface::index(
                                        level, nVertexDoFIndices[srcDofIdx].x(), nVertexDoFIndices[srcDofIdx].y() )];
                                    mat->addValue( globalRowIdx, globalColIdx, localMat( 0, Eigen::Index( srcDofIdx ) ) );
                                 }
                                 else
                                 {
                                    WALBERLA_ABORT( "Not implemented." );
                                 }
                              }
                           }
                        }
                     }
                  } // End loop over neighboring volumes.
               }    // End if( !onlyVolumeIntegrals() )

               if ( mat == nullptr )
               {
                  // TODO: there is only one DoF to write to - remove the loop.

                  // Write DoFs.
                  for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                  {
                     if ( dim == 2 )
                     {
                        if ( updateType == Replace )
                        {
                           dstDofMemory[volumedofspace::indexing::index(
                               elementIdx.x(), elementIdx.y(), faceType, dstDofIdx, numDstDofs, level, dstMemLayout )] =
                               dstDofs( dstDofIdx );
                        }
                        else if ( updateType == Add )
                        {
                           dstDofMemory[volumedofspace::indexing::index(
                               elementIdx.x(), elementIdx.y(), faceType, dstDofIdx, numDstDofs, level, dstMemLayout )] +=
                               dstDofs( dstDofIdx );
                        }
                        else
                        {
                           WALBERLA_ABORT( "Invalid update type." );
                        }
                     }
                     else
                     {
                        if ( updateType == Replace )
                        {
                           dstDofMemory[volumedofspace::indexing::index( elementIdx.x(),
                                                                         elementIdx.y(),
                                                                         elementIdx.z(),
                                                                         cellType,
                                                                         dstDofIdx,
                                                                         numDstDofs,
                                                                         level,
                                                                         dstMemLayout )] = dstDofs( dstDofIdx );
                        }
                        else if ( updateType == Add )
                        {
                           dstDofMemory[volumedofspace::indexing::index( elementIdx.x(),
                                                                         elementIdx.y(),
                                                                         elementIdx.z(),
                                                                         cellType,
                                                                         dstDofIdx,
                                                                         numDstDofs,
                                                                         level,
                                                                         dstMemLayout )] += dstDofs( dstDofIdx );
                        }
                        else
                        {
                           WALBERLA_ABORT( "Invalid update type." );
                        }
                     }
                  }
               }
            }
         }
      }

      WALBERLA_UNUSED( flag );
   }

   std::shared_ptr< Form > form_;
};

typedef P1ToP0Operator< dg::p1_to_p0_div_0_affine_q0 > P1ToP0ConstantDivxOperator;
typedef P1ToP0Operator< dg::p1_to_p0_div_1_affine_q0 > P1ToP0ConstantDivyOperator;
typedef P1ToP0Operator< dg::p1_to_p0_div_2_affine_q0 > P1ToP0ConstantDivzOperator;

typedef P1ToP0Operator< dg::DGVectorLaplaceFormEDGP1_0 > P1ToP0ConstantP1EDGVectorLaplaceXCouplingOperator;
typedef P1ToP0Operator< dg::DGVectorLaplaceFormEDGP1_1 > P1ToP0ConstantP1EDGVectorLaplaceYCouplingOperator;
typedef P1ToP0Operator< dg::DGFormAbort >                P1ToP0ConstantP1EDGVectorLaplaceZCouplingOperator;

typedef P1ToP0Operator< dg::DGVectorMassFormEDGP1_0 > P1ToP0ConstantP1EDGVectorMassXCouplingOperator;
typedef P1ToP0Operator< dg::DGVectorMassFormEDGP1_1 > P1ToP0ConstantP1EDGVectorMassYCouplingOperator;
typedef P1ToP0Operator< dg::DGFormAbort >             P1ToP0ConstantP1EDGVectorMassZCouplingOperator;

typedef P1ToP0Operator< dg::DGDivtFormEDGP1 > P1ToP0ConstantP1EDGVDivergenceCouplingOperator;

} // namespace hyteg