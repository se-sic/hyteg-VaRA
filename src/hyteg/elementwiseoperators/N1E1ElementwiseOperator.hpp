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

#include "hyteg/celldofspace/CellDoFIndexing.hpp"
#include "hyteg/forms/N1E1LinearCombinationForm.hpp"
#include "hyteg/forms/form_hyteg_manual/N1E1FormCurlCurl.hpp"
#include "hyteg/forms/form_hyteg_manual/N1E1FormMass.hpp"
#include "hyteg/n1e1functionspace/N1E1Indexing.hpp"
#include "hyteg/n1e1functionspace/N1E1VectorFunction.hpp"
#include "hyteg/p1functionspace/VertexDoFIndexing.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroCell.hpp"
#include "hyteg/solvers/Smoothables.hpp"
#include "hyteg/sparseassembly/SparseMatrixProxy.hpp"

namespace hyteg {
namespace n1e1 {

using walberla::real_t;

template < class N1E1FormType >
class N1E1ElementwiseOperator : public Operator< N1E1VectorFunction< real_t >, N1E1VectorFunction< real_t > >,
                                public OperatorWithInverseDiagonal< N1E1VectorFunction< real_t > >
{
 public:
   N1E1ElementwiseOperator( const std::shared_ptr< PrimitiveStorage >& storage, size_t minLevel, size_t maxLevel );

   N1E1ElementwiseOperator( const std::shared_ptr< PrimitiveStorage >& storage,
                            size_t                                     minLevel,
                            size_t                                     maxLevel,
                            const N1E1FormType&                        form,
                            const bool                                 needsInverseDiagEntries = true );

   void apply( const N1E1VectorFunction< real_t >& src,
               const N1E1VectorFunction< real_t >& dst,
               size_t                              level,
               DoFType                             flag,
               UpdateType                          updateType = Replace ) const override final;

   /// \brief Pre-computes the local stiffness matrices for each (micro-)element and stores them all in memory.
   ///
   /// If this method is called, all subsequent calls to apply() or smooth_*() use the stored element matrices.
   /// If the local element matrices need to be recomputed again, simply call this method again.
   void computeAndStoreLocalElementMatrices();

   /// Trigger (re)computation of diagonal matrix entries (central operator weights)
   /// Allocates the required memory if the function was not yet allocated.
   void                                            computeDiagonalOperatorValues();
   std::shared_ptr< N1E1VectorFunction< real_t > > getDiagonalValues() const;

   /// Trigger (re)computation of inverse diagonal matrix entries (central operator weights)
   /// Allocates the required memory if the function was not yet allocated.
   void                                            computeInverseDiagonalOperatorValues() override;
   std::shared_ptr< N1E1VectorFunction< real_t > > getInverseDiagonalValues() const override;

   /// Assemble operator as sparse matrix.
   ///
   /// \param mat   a sparse matrix proxy
   /// \param src   N1E1VectorFunction for determining column indices
   /// \param dst   N1E1VectorFunction for determining row indices
   /// \param level level in mesh hierarchy for which local operator is to be assembled
   /// \param flag  ignored
   ///
   /// \note src and dst are legal to and often will be the same function object
   void toMatrix( const std::shared_ptr< SparseMatrixProxy >& mat,
                  const N1E1VectorFunction< idx_t >&          src,
                  const N1E1VectorFunction< idx_t >&          dst,
                  uint_t                                      level,
                  DoFType                                     flag ) const override;

   N1E1FormType getForm() const;

 private:
   void computeDiagonalOperatorValues( bool invert );
   void computeLocalDiagonal( const Cell&             cell,
                              const uint_t            level,
                              const indexing::Index&  microCell,
                              const celldof::CellType cType,
                              const real_t* const     edgeDirsData,
                              real_t* const           diagData );

   void localMatrixAssembly3D( const std::shared_ptr< SparseMatrixProxy >& mat,
                               const Cell&                                 cell,
                               const uint_t                                level,
                               const indexing::Index&                      microCell,
                               const celldof::CellType                     cType,
                               const idx_t* const                          srcEdgeIdx,
                               const idx_t* const                          dstEdgeIdx,
                               const real_t* const                         edgeDirsData ) const;

   /// \brief Returns a reference to the precomputed element matrix of the specified micro cell.
   /// Probably crashes if local element matrices have not been precomputed.
   Matrix6r& localElementMatrix3D( const Cell& cell, uint_t level, const indexing::Index& microCell, celldof::CellType cType )
   {
      WALBERLA_ASSERT( storage_->hasGlobalCells(), "Retriveing local element matrix for 3D in 2D run. Why?" )
      const auto idx = celldof::macrocell::index( level, microCell.x(), microCell.y(), microCell.z(), cType );
      WALBERLA_ASSERT( localElementMatrices3D_.count( cell.getID() ) > 0 )
      WALBERLA_ASSERT( localElementMatrices3D_.at( cell.getID() ).count( level ) > 0 )
      WALBERLA_ASSERT( localElementMatrices3D_.at( cell.getID() ).at( level ).size() > 0 )
      return localElementMatrices3D_[cell.getID()][level][idx];
   }

   /// \brief Returns a const reference to the precomputed element matrix of the specified micro cell.
   /// Probably crashes if local element matrices have not been precomputed.
   const Matrix6r&
       localElementMatrix3D( const Cell& cell, uint_t level, const indexing::Index& microCell, celldof::CellType cType ) const
   {
      WALBERLA_ASSERT( storage_->hasGlobalCells(), "Retriveing local element matrix for 3D in 2D run. Why?" )
      const auto idx = celldof::macrocell::index( level, microCell.x(), microCell.y(), microCell.z(), cType );
      WALBERLA_ASSERT( localElementMatrices3D_.count( cell.getID() ) > 0 )
      WALBERLA_ASSERT( localElementMatrices3D_.at( cell.getID() ).count( level ) > 0 )
      WALBERLA_ASSERT( localElementMatrices3D_.at( cell.getID() ).at( level ).size() > 0 )
      return localElementMatrices3D_.at( cell.getID() ).at( level ).at( idx );
   }

   N1E1FormType form_;

   std::shared_ptr< N1E1VectorFunction< real_t > > diagonalValues_;
   std::shared_ptr< N1E1VectorFunction< real_t > > inverseDiagonalValues_;

   // TODO this is possible without allocating a new function
   N1E1VectorFunction< real_t > edgeDirs_;

   /// Pre-computed local element matrices.
   /// localElementMatrices3D_[macroCellID][level][cellIdx] = mat6x6
   std::map< PrimitiveID, std::map< uint_t, std::vector< Matrix6r > > > localElementMatrices3D_;
   bool                                                                 localElementMatricesPrecomputed_;
};

template < class N1E1FormType >
void assembleLocalElementMatrix3D( const Cell&            cell,
                                   uint_t                 level,
                                   const indexing::Index& microCell,
                                   celldof::CellType      cType,
                                   N1E1FormType           form,
                                   const real_t* const    edgeDirsData,
                                   Matrix6r&              elMat )
{
   // determine coordinates of vertices of micro-element
   std::array< indexing::Index, 4 > verts = n1e1::macrocell::getMicroVerticesFromMicroCell( microCell, cType );
   std::array< Point3D, 4 >         coords;
   for ( uint_t k = 0; k < 4; ++k )
   {
      coords[k] = vertexdof::macrocell::coordinateFromIndex( level, cell, verts[k] );
   }

   // determine edge orienations
   std::array< int, 6 >    edgeDirections;
   std::array< uint_t, 6 > edgeDoFIndices;
   n1e1::getEdgeDoFDataIndicesFromMicroCellFEniCSOrdering( microCell, cType, level, edgeDoFIndices );
   for ( uint_t i = 0; i < 6; ++i )
   {
      edgeDirections[i] = numeric_cast< int >( edgeDirsData[edgeDoFIndices[i]] );
   }

   // assemble local element matrix
   form.setGeometryMap( cell.getGeometryMap() );
   form.integrateAll( coords, edgeDirections, elMat );
}

/// compute product of element local vector with element matrix
///
/// \param level          level on which we operate in mesh hierarchy
/// \param microCell      index associated with the current element = micro-cell
/// \param cType          type of micro-cell (WHITE_UP, BLUE_DOWN, ...)
/// \param srcEdgeData    pointer to DoF data on micro-edges (for reading data)
/// \param dstEdgeData    pointer to DoF data on micro-edges (for writing data)
/// \param elMat          the 6x6 element matrix to be multiplied
///
/// \note The src and dst data arrays must not be identical.
void localMatrixVectorMultiply3D( uint_t                 level,
                                  const indexing::Index& microCell,
                                  celldof::CellType      cType,
                                  const real_t* const    srcEdgeData,
                                  real_t* const          dstEdgeData,
                                  const Matrix6r&        elMat );

using N1E1ElementwiseCurlCurlOperator          = N1E1ElementwiseOperator< N1E1Form_curl_curl >;
using N1E1ElementwiseMassOperator              = N1E1ElementwiseOperator< N1E1Form_mass >;
using N1E1ElementwiseLinearCombinationOperator = N1E1ElementwiseOperator< N1E1LinearCombinationForm >;

} // namespace n1e1
} // namespace hyteg
