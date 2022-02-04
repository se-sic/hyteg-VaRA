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

#include "hyteg/celldofspace/CellDoFIndexing.hpp"
#include "hyteg/dgfunctionspace/DGFunction.hpp"
#include "hyteg/functions/Function.hpp"
#include "hyteg/indexing/Common.hpp"
#include "hyteg/indexing/MacroCellIndexing.hpp"
#include "hyteg/indexing/MacroEdgeIndexing.hpp"
#include "hyteg/indexing/MacroFaceIndexing.hpp"
#include "hyteg/memory/FunctionMemory.hpp"
#include "hyteg/operators/Operator.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"
#include "hyteg/solvers/Smoothables.hpp"

namespace hyteg {
namespace dg {

using walberla::int_c;
using walberla::real_t;

class DGOperator : public Operator< DGFunction< real_t >, DGFunction< real_t > >,
                   public WeightedJacobiSmoothable< DGFunction< real_t > >,
                   public OperatorWithInverseDiagonal< DGFunction< real_t > >
{
 public:
   DGOperator( const std::shared_ptr< PrimitiveStorage >& storage,
               uint_t                                     minLevel,
               uint_t                                     maxLevel,
               const std::shared_ptr< DGForm >&           form );

   void apply( const DGFunction< real_t >& src,
               const DGFunction< real_t >& dst,
               size_t                      level,
               DoFType                     flag,
               UpdateType                  updateType ) const override;

   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const DGFunction< idx_t >&                  src,
                  const DGFunction< idx_t >&                  dst,
                  size_t                                      level,
                  DoFType                                     flag ) const override;

   void smooth_jac( const DGFunction< real_t >& dst,
                    const DGFunction< real_t >& rhs,
                    const DGFunction< real_t >& tmp,
                    real_t                      relax,
                    size_t                      level,
                    DoFType                     flag ) const override;

   [[nodiscard]] std::shared_ptr< DGFunction< real_t > > getInverseDiagonalValues() const override;

 private:
   /// \brief Helper function that can be used to either apply the operator, or to assemble the sparse matrix.
   ///
   /// Since about 99% of the implementation is equal, it makes sense to fuse that here.
   ///
   /// Which operation is performed depends on the pointer to the sparse matrix proxy and the value type.
   /// If the pointer is a nullptr, apply is executed.
   /// If the value type is not idx_t, apply is executed.
   template < typename VType >
   inline void assembleAndOrApply( const DGFunction< VType >&                  src,
                                   const DGFunction< VType >&                  dst,
                                   size_t                                      level,
                                   DoFType                                     flag,
                                   const std::shared_ptr< SparseMatrixProxy >& mat,
                                   UpdateType                                  updateType = Replace ) const
   {
      using indexing::Index;

      WALBERLA_CHECK( updateType == Replace );

      if ( this->getStorage()->hasGlobalCells() )
      {
         WALBERLA_ABORT( "DG apply not implemented in 3D." );
      }
      else
      {
         for ( const auto& faceIt : this->getStorage()->getFaces() )
         {
            const auto faceId = faceIt.first;
            const auto face   = *faceIt.second;

            const auto srcPolyDegree = src.polynomialDegree( faceId );
            const auto dstPolyDegree = dst.polynomialDegree( faceId );

            const auto numSrcDofs = src.basis()->numDoFsPerElement( srcPolyDegree );
            const auto numDstDofs = dst.basis()->numDoFsPerElement( dstPolyDegree );

            const auto srcDofMemory = src.volumeDoFFunction()->dofMemory( faceId, level );
            auto       dstDofMemory = dst.volumeDoFFunction()->dofMemory( faceId, level );

            const auto srcMemLayout = src.volumeDoFFunction()->memoryLayout();
            const auto dstMemLayout = dst.volumeDoFFunction()->memoryLayout();

            for ( auto faceType : facedof::allFaceTypes )
            {
               for ( auto elementIdx : facedof::macroface::Iterator( level, faceType ) )
               {
                  const auto vertexIndicesVolume = facedof::macroface::getMicroVerticesFromMicroFace( elementIdx, faceType );

                  std::array< Eigen::Matrix< real_t, 2, 1 >, 3 > vertexCoordsVolume;
                  for ( uint_t i = 0; i < 3; i++ )
                  {
                     const auto coord = vertexdof::macroface::coordinateFromIndex( level, face, vertexIndicesVolume[i] );
                     vertexCoordsVolume[i]( 0 ) = coord[0];
                     vertexCoordsVolume[i]( 1 ) = coord[1];
                  }

                  // We only write to the DoFs in the current volume, let's prepare a temporary vector for that.
                  Eigen::Matrix< real_t, Eigen::Dynamic, 1 > dstDofs;
                  dstDofs.resize( numDstDofs, Eigen::NoChange_t::NoChange );
                  dstDofs.setZero();

                  /////////////////////////
                  // Volume contribution //
                  /////////////////////////

                  Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic > localMat;
                  form_->integrateVolume(
                      vertexCoordsVolume, *src.basis(), *dst.basis(), srcPolyDegree, dstPolyDegree, localMat );

                  // Volume DoFs are source.
                  Eigen::Matrix< real_t, Eigen::Dynamic, 1 > srcDofs;
                  srcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );

                  for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                  {
                     srcDofs( srcDofIdx ) = srcDofMemory[volumedofspace::indexing::index(
                         elementIdx.x(), elementIdx.y(), faceType, srcDofIdx, numSrcDofs, level, srcMemLayout )];
                  }

                  ////////////////////////////////
                  // MatVec or sparse assembly? //
                  ////////////////////////////////

                  if ( !std::is_same_v< VType, idx_t > || mat == nullptr )
                  {
                     // Matrix-vector multiplication.
                     dstDofs += localMat * srcDofs;
                  }
                  else
                  {
                     // Sparse assembly.
                     for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                     {
                        for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                        {
                           const auto globalRowIdx = dstDofMemory[volumedofspace::indexing::index(
                               elementIdx.x(), elementIdx.y(), faceType, dstDofIdx, numDstDofs, level, dstMemLayout )];
                           const auto globalColIdx = srcDofMemory[volumedofspace::indexing::index(
                               elementIdx.x(), elementIdx.y(), faceType, srcDofIdx, numSrcDofs, level, srcMemLayout )];
                           mat->addValue( globalRowIdx, globalColIdx, localMat( dstDofIdx, srcDofIdx ) );
                        }
                     }
                  }

                  /////////////////////////////
                  // Interface contributions //
                  /////////////////////////////

                  // TODO: This should be done in a more clever and less hardcoded way.

                  WALBERLA_CHECK_EQUAL(
                      walberla::mpi::MPIManager::instance()->numProcesses(), 1, "Parallel execution not supported." );
                  WALBERLA_CHECK_EQUAL(
                      storage_->getNumberOfLocalFaces(), 1, "Currently the implementation does not support macro-interfaces." );

                  // If the current element shares a boundary with the macro-element we need to handle that.
                  if ( facedof::macroface::sharesBoundaryWithMacro( elementIdx, faceType, level ) )
                  {
                     // TODO: handle macro-interfaces
                     // TODO: handle Dirichlet & Neumann boundaries
                  }
                  else
                  {
                     // TODO: all these coord computations can be executed _once_ and then the coordinates can be incremented by h

                     // All micro-interfaces are 'inner' interfaces. So no boundary handling of macro-interface handling required.
                     std::array< Index, 3 >                                          neighborElementIndices;
                     std::array< std::array< Eigen::Matrix< real_t, 2, 1 >, 3 >, 3 > neighborElementVertexCoords;
                     std::array< std::array< Index, 2 >, 3 >                         interfaceVertexIndices;
                     std::array< std::array< Eigen::Matrix< real_t, 2, 1 >, 2 >, 3 > interfaceVertexCoords;

                     facedof::FaceType nFaceType;

                     if ( faceType == facedof::FaceType::GRAY )
                     {
                        nFaceType = facedof::FaceType::BLUE;

                        neighborElementIndices[0] = Index( elementIdx.x() - 1, elementIdx.y(), 0 );
                        neighborElementIndices[1] = Index( elementIdx.x(), elementIdx.y() - 1, 0 );
                        neighborElementIndices[2] = Index( elementIdx.x(), elementIdx.y(), 0 );

                        interfaceVertexIndices[0][0] = Index( elementIdx.x(), elementIdx.y(), 0 );
                        interfaceVertexIndices[0][1] = Index( elementIdx.x(), elementIdx.y() + 1, 0 );

                        interfaceVertexIndices[1][0] = Index( elementIdx.x(), elementIdx.y(), 0 );
                        interfaceVertexIndices[1][1] = Index( elementIdx.x() + 1, elementIdx.y(), 0 );

                        interfaceVertexIndices[2][0] = Index( elementIdx.x() + 1, elementIdx.y(), 0 );
                        interfaceVertexIndices[2][1] = Index( elementIdx.x(), elementIdx.y() + 1, 0 );
                     }
                     else
                     {
                        nFaceType = facedof::FaceType::GRAY;

                        neighborElementIndices[0] = Index( elementIdx.x() + 1, elementIdx.y(), 0 );
                        neighborElementIndices[1] = Index( elementIdx.x(), elementIdx.y() + 1, 0 );
                        neighborElementIndices[2] = Index( elementIdx.x(), elementIdx.y(), 0 );

                        interfaceVertexIndices[0][0] = Index( elementIdx.x() + 1, elementIdx.y(), 0 );
                        interfaceVertexIndices[0][1] = Index( elementIdx.x() + 1, elementIdx.y() + 1, 0 );

                        interfaceVertexIndices[1][0] = Index( elementIdx.x(), elementIdx.y() + 1, 0 );
                        interfaceVertexIndices[1][1] = Index( elementIdx.x() + 1, elementIdx.y() + 1, 0 );

                        interfaceVertexIndices[2][0] = Index( elementIdx.x() + 1, elementIdx.y(), 0 );
                        interfaceVertexIndices[2][1] = Index( elementIdx.x(), elementIdx.y() + 1, 0 );
                     }

                     // Looping over neighbor elements.
                     for ( uint_t n = 0; n < 3; n++ )
                     {
                        const auto vertexIndices =
                            facedof::macroface::getMicroVerticesFromMicroFace( neighborElementIndices[n], nFaceType );

                        for ( uint_t i = 0; i < 3; i++ )
                        {
                           const auto coord = vertexdof::macroface::coordinateFromIndex( level, face, vertexIndices[i] );
                           neighborElementVertexCoords[n][i]( 0 ) = coord[0];
                           neighborElementVertexCoords[n][i]( 1 ) = coord[1];
                        }

                        for ( uint_t i = 0; i < 2; i++ )
                        {
                           const auto coord =
                               vertexdof::macroface::coordinateFromIndex( level, face, interfaceVertexIndices[n][i] );
                           interfaceVertexCoords[n][i]( 0 ) = coord[0];
                           interfaceVertexCoords[n][i]( 1 ) = coord[1];
                        }

                        localMat.setZero();
                        form_->integrateFacetInner( vertexCoordsVolume,
                                                    interfaceVertexCoords[n],
                                                    *src.basis(),
                                                    *dst.basis(),
                                                    srcPolyDegree,
                                                    dstPolyDegree,
                                                    localMat );

                        if ( !std::is_same_v< VType, idx_t > || mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * srcDofs;
                        }
                        else
                        {
                           // TODO: assembly
                        }

                        localMat.setZero();
                        form_->integrateFacetCoupling( vertexCoordsVolume,
                                                       neighborElementVertexCoords[n],
                                                       interfaceVertexCoords[n],
                                                       *src.basis(),
                                                       *dst.basis(),
                                                       srcPolyDegree,
                                                       dstPolyDegree,
                                                       localMat );

                        // Now we need the DoFs from the neighboring element.
                        Eigen::Matrix< real_t, Eigen::Dynamic, 1 > nSrcDofs;
                        nSrcDofs.resize( numSrcDofs, Eigen::NoChange_t::NoChange );

                        for ( uint_t srcDofIdx = 0; srcDofIdx < numSrcDofs; srcDofIdx++ )
                        {
                           nSrcDofs( srcDofIdx ) = srcDofMemory[volumedofspace::indexing::index( neighborElementIndices[n].x(),
                                                                                                 neighborElementIndices[n].y(),
                                                                                                 nFaceType,
                                                                                                 srcDofIdx,
                                                                                                 numSrcDofs,
                                                                                                 level,
                                                                                                 srcMemLayout )];
                        }

                        if ( !std::is_same_v< VType, idx_t > || mat == nullptr )
                        {
                           // Matrix-vector multiplication.
                           dstDofs += localMat * nSrcDofs;
                        }
                        else
                        {
                           // TODO: assembly
                        }
                     }
                  }

                  if ( !std::is_same_v< VType, idx_t > || mat == nullptr )
                  {
                     // Write DoFs.
                     for ( uint_t dstDofIdx = 0; dstDofIdx < numDstDofs; dstDofIdx++ )
                     {
                        dstDofMemory[volumedofspace::indexing::index(
                            elementIdx.x(), elementIdx.y(), faceType, dstDofIdx, numDstDofs, level, dstMemLayout )] =
                            dstDofs( dstDofIdx );
                     }
                  }
               }
            }
         }
      }

      WALBERLA_UNUSED( flag );
   }

   std::shared_ptr< DGForm > form_;
};

} // namespace dg
} // namespace hyteg