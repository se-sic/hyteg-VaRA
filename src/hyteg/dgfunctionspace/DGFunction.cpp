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

#include "hyteg/dgfunctionspace/DGFunction.hpp"

#include "core/DataTypes.h"
#include "core/mpi/MPIWrapper.h"
#include "core/mpi/Reduce.h"

#include "hyteg/geometry/Intersection.hpp"
#include "hyteg/p1functionspace/VertexDoFMacroFace.hpp"
#include "hyteg/volumedofspace/VolumeDoFFunction.hpp"

namespace hyteg {
namespace dg {

using walberla::uint_t;

template < typename ValueType >
DGFunction< ValueType >::DGFunction( const std::string&                         name,
                                     const std::shared_ptr< PrimitiveStorage >& storage,
                                     uint_t                                     minLevel,
                                     uint_t                                     maxLevel,
                                     const std::shared_ptr< DGBasisInfo >&      basis,
                                     int                                        initialPolyDegree,
                                     BoundaryCondition                          boundaryCondition )
: Function< DGFunction< ValueType > >( name, storage, minLevel, maxLevel )
, name_( name )
, storage_( storage )
, minLevel_( minLevel )
, maxLevel_( maxLevel )
, basis_( basis )
, boundaryCondition_( boundaryCondition )
{
   if ( storage->hasGlobalCells() )
   {
      WALBERLA_ABORT( "Not implemented for cells yet." )
   }
   else
   {
      for ( auto pid : storage->getFaceIDs() )
      {
         polyDegreesPerPrimitive_[pid] = uint_c( initialPolyDegree );
      }
   }

   volumeDoFFunction_ = std::make_shared< volumedofspace::VolumeDoFFunction< ValueType > >(
       name,
       storage,
       minLevel,
       maxLevel,
       basis->numDoFsPerElement( uint_c( initialPolyDegree ) ),
       volumedofspace::indexing::VolumeDoFMemoryLayout::SoA );
}

template < typename ValueType >
bool DGFunction< ValueType >::evaluate( const Point3D& coordinates,
                                        uint_t         level,
                                        ValueType&     value,
                                        real_t         searchToleranceRadius ) const
{
   if ( !this->storage_->hasGlobalCells() )
   {
      // 2D

      Point2D coordinates2D( { coordinates[0], coordinates[1] } );

      for ( auto& it : this->getStorage()->getFaces() )
      {
         PrimitiveID faceID = it.first;
         Face&       face   = *it.second;

         const auto polyDegree = polyDegreesPerPrimitive_.at( faceID );
         const auto ndofs      = uint_c( basis_->numDoFsPerElement( polyDegree ) );

         Point2D faceCoodinates0( { face.getCoordinates()[0][0], face.getCoordinates()[0][1] } );
         Point2D faceCoodinates1( { face.getCoordinates()[1][0], face.getCoordinates()[1][1] } );
         Point2D faceCoodinates2( { face.getCoordinates()[2][0], face.getCoordinates()[2][1] } );

         if ( isPointInTriangle( coordinates2D, faceCoodinates0, faceCoodinates1, faceCoodinates2 ) ||
              ( searchToleranceRadius > 0 &&
                circleTriangleIntersection(
                    coordinates2D, searchToleranceRadius, faceCoodinates0, faceCoodinates1, faceCoodinates2 ) ) )
         {
            indexing::Index   elementIndex;
            facedof::FaceType faceType;
            Point2D           localCoordinates;

            volumedofspace::getLocalElementFromCoordinates< ValueType >(
                level, face, coordinates2D, elementIndex, faceType, localCoordinates );

            Eigen::Matrix< real_t, 2, 1 > refPos( localCoordinates[0], localCoordinates[1] );

            std::vector< real_t > dofs( ndofs );
            for ( uint_t i = 0; i < ndofs; i++ )
            {
               dofs[i] = real_t( volumeDoFFunction_->dof( faceID, elementIndex, i, faceType, level ) );
            }

            real_t value_r;
            basis_->evaluate( polyDegree, refPos, dofs, value_r );

            // Eigen::Matrix< real_t, 2, 1 > coords( coordinates2D[0], coordinates2D[1] );
            // basis_->evaluate( polyDegree, affineElementVertices, coords, dofs, value_r );

            value = ValueType( value_r );
            return true;
         }
      }
   }
   else
   {
      WALBERLA_ABORT( "not implemented" );
#if 0
      for ( auto& it : this->getStorage()->getCells() )
      {
         Cell& cell = *it.second;

         if ( isPointInTetrahedron( coordinates,

                                    cell.getCoordinates()[0],
                                    cell.getCoordinates()[1],
                                    cell.getCoordinates()[2],
                                    cell.getCoordinates()[3],
                                    cell.getFaceInwardNormal( 0 ),
                                    cell.getFaceInwardNormal( 1 ),
                                    cell.getFaceInwardNormal( 2 ),
                                    cell.getFaceInwardNormal( 3 ) ) )
         {
            value = vertexdof::macrocell::evaluate< real_t >( level, cell, coordinates, cellDataID_ );
            return true;
         }
      }

      if ( searchToleranceRadius > 0 )
      {
         for ( auto& it : this->getStorage()->getCells() )
         {
            Cell& cell = *it.second;

            if ( sphereTetrahedronIntersection( coordinates,
                                                searchToleranceRadius,
                                                cell.getCoordinates()[0],
                                                cell.getCoordinates()[1],
                                                cell.getCoordinates()[2],
                                                cell.getCoordinates()[3] ) )
            {
               value = vertexdof::macrocell::evaluate< real_t >( level, cell, coordinates, cellDataID_ );
               return true;
            }
         }
      }
#endif
   }

   return false;
}

template < typename ValueType >
void DGFunction< ValueType >::evaluateOnMicroElement( const Point3D&         coordinates,
                                                      uint_t                 level,
                                                      const PrimitiveID&     faceID,
                                                      hyteg::indexing::Index elementIndex,
                                                      facedof::FaceType      faceType,
                                                      ValueType&             value ) const
{
   if ( !this->storage_->hasGlobalCells() )
   {
      // 2D

      Point2D coordinates2D( { coordinates[0], coordinates[1] } );

      const Face& face = *storage_->getFace( faceID );

      const auto polyDegree = polyDegreesPerPrimitive_.at( faceID );
      const auto ndofs      = uint_c( basis_->numDoFsPerElement( polyDegree ) );

      Eigen::Matrix< real_t, 2, 1 > affineCoordinates( { coordinates[0], coordinates[1] } );

      std::array< Eigen::Matrix< real_t, 2, 1 >, 3 > affineElementVertices;
      auto vertexIndices = facedof::macroface::getMicroVerticesFromMicroFace( elementIndex, faceType );
      for ( uint_t i = 0; i < 3; i++ )
      {
         const auto coord              = vertexdof::macroface::coordinateFromIndex( level, face, vertexIndices[i] );
         affineElementVertices[i]( 0 ) = coord[0];
         affineElementVertices[i]( 1 ) = coord[1];
      }

      // trafo from affine to reference space
      Eigen::Matrix< real_t, 2, 2 > A;
      A( 0, 0 )       = ( affineElementVertices[1] - affineElementVertices[0] )( 0 );
      A( 0, 1 )       = ( affineElementVertices[2] - affineElementVertices[0] )( 0 );
      A( 1, 0 )       = ( affineElementVertices[1] - affineElementVertices[0] )( 1 );
      A( 1, 1 )       = ( affineElementVertices[2] - affineElementVertices[0] )( 1 );
      const auto Ainv = A.inverse();

      const Eigen::Matrix< real_t, 2, 1 > affineCoordsTranslated = affineCoordinates - affineElementVertices[0];

      const Eigen::Matrix< real_t, 2, 1 > refPos = Ainv * affineCoordsTranslated;

      std::vector< real_t > dofs( ndofs );
      for ( uint_t i = 0; i < ndofs; i++ )
      {
         dofs[i] = real_t( volumeDoFFunction_->dof( faceID, elementIndex, i, faceType, level ) );
      }

      real_t value_r;
      basis_->evaluate( polyDegree, refPos, dofs, value_r );

      value = ValueType( value_r );
   }
   else
   {
      WALBERLA_ABORT( "not implemented" );
   }
}

template < typename ValueType >
void DGFunction< ValueType >::evaluateLinearFunctional( const std::function< real_t( const Point3D& ) >& f, uint_t level )
{
   if ( storage_->hasGlobalCells() )
   {
      WALBERLA_ABORT( "Linear functional evaluation not implemented." )
   }
   else
   {
      for ( auto& it : this->getStorage()->getFaces() )
      {
         const auto faceID = it.first;
         const auto face   = *it.second;

         const auto degree  = polyDegreesPerPrimitive_.at( faceID );
         const auto numDofs = basis()->numDoFsPerElement( degree );

         auto       dofs      = volumeDoFFunction()->dofMemory( faceID, level );
         const auto memLayout = volumeDoFFunction()->memoryLayout();

         for ( auto faceType : facedof::allFaceTypes )
         {
            for ( const auto& idxIt : facedof::macroface::Iterator( level, faceType ) )
            {
               const std::array< indexing::Index, 3 > vertexIndices =
                   facedof::macroface::getMicroVerticesFromMicroFace( idxIt, faceType );
               std::array< Eigen::Matrix< real_t, 2, 1 >, 3 > elementVertices;
               for ( uint_t i = 0; i < 3; i++ )
               {
                  const auto elementVertex = vertexdof::macroface::coordinateFromIndex( level, face, vertexIndices[i] );
                  elementVertices[i]( 0 )  = elementVertex[0];
                  elementVertices[i]( 1 )  = elementVertex[1];
               }

               std::vector< real_t > dofValues( numDofs );
               basis()->integrateBasisFunction( degree, elementVertices, f, dofValues );

               for ( uint_t i = 0; i < numDofs; i++ )
               {
                  dofs[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )] =
                      ValueType( dofValues[i] );
               }
            }
         }
      }
   }
}

template < typename ValueType >
void DGFunction< ValueType >::enumerate( uint_t level ) const
{
   uint_t counter = numberOfLocalDoFs( *this, level );

   std::vector< uint_t > dofs_per_rank = walberla::mpi::allGather( counter );

   auto startOnRank = ValueType( 0 );

   for ( uint_t i = 0; i < uint_c( walberla::MPIManager::instance()->rank() ); ++i )
   {
      startOnRank += static_cast< ValueType >( dofs_per_rank[i] );
   }

   this->enumerate( level, startOnRank );
   communicate( level );
}

template < typename ValueType >
void DGFunction< ValueType >::enumerate( uint_t level, ValueType& offset ) const
{
   if ( storage_->hasGlobalCells() )
   {
      // 3D
      WALBERLA_ABORT( "enumerate() not implemented in 3D." );
   }
   else
   {
      // 2D
      for ( const auto& it : storage_->getFaces() )
      {
         const auto faceID = it.first;
         const auto face   = *it.second;

         const auto degree  = polyDegreesPerPrimitive_.at( faceID );
         const auto numDofs = basis()->numDoFsPerElement( degree );

         auto       dofs      = volumeDoFFunction()->dofMemory( faceID, level );
         const auto memLayout = volumeDoFFunction()->memoryLayout();

         for ( auto faceType : facedof::allFaceTypes )
         {
            for ( const auto& idxIt : facedof::macroface::Iterator( level, faceType ) )
            {
               for ( uint_t i = 0; i < numDofs; i++ )
               {
                  dofs[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )] =
                      offset++;
               }
            }
         }
      }
   }
}

template < typename ValueType >
uint_t DGFunction< ValueType >::getNumberOfLocalDoFs( uint_t level ) const
{
   uint_t ndofs = 0;

   if ( storage_->hasGlobalCells() )
   {
      WALBERLA_ABORT( "getNumberOfLocalDoFs not implemented for 3D." );
   }
   else
   {
      for ( auto& it : this->getStorage()->getFaces() )
      {
         const auto faceID = it.first;
         const auto face   = *it.second;

         const auto numElements       = levelinfo::num_microfaces_per_face( level );
         const auto degree            = polyDegreesPerPrimitive_.at( faceID );
         const auto numDoFsPerElement = basis()->numDoFsPerElement( degree );

         ndofs += numElements * numDoFsPerElement;
      }
   }

   return ndofs;
}

template < typename ValueType >
uint_t DGFunction< ValueType >::getNumberOfGlobalDoFs( uint_t level, const MPI_Comm& communicator, const bool& onRootOnly ) const
{
   uint_t ndofs = getNumberOfLocalDoFs( level );
   if ( onRootOnly )
   {
      walberla::mpi::reduceInplace( ndofs, walberla::mpi::SUM, 0, communicator );
   }
   else
   {
      walberla::mpi::allReduceInplace( ndofs, walberla::mpi::SUM, communicator );
   }
   return ndofs;
}

template < typename ValueType >
void DGFunction< ValueType >::applyDirichletBoundaryConditions( const std::shared_ptr< DGForm >& form, uint_t level )
{
   using indexing::Index;

   if ( storage_->hasGlobalCells() )
   {
      WALBERLA_ABORT( "Dirichlet BCs not implemented for 3D." );
   }
   else
   {
      const int dim = 2;

      for ( const auto& faceIt : this->getStorage()->getFaces() )
      {
         const auto faceId = faceIt.first;
         const auto face   = *faceIt.second;

         const auto polyDegree = polynomialDegree( faceId );
         const auto numDofs    = basis()->numDoFsPerElement( uint_c( polyDegree ) );
         const auto dofMemory  = volumeDoFFunction()->dofMemory( faceId, level );
         const auto memLayout  = volumeDoFFunction()->memoryLayout();

         for ( auto faceType : facedof::allFaceTypes )
         {
            for ( auto elementIdx : facedof::macroface::Iterator( level, faceType ) )
            {
               volumedofspace::indexing::ElementNeighborInfo neighborInfo(
                   elementIdx, faceType, level, boundaryCondition_, faceId, storage_ );

               for ( uint_t n = 0; n < 3; n++ )
               {
                  if ( neighborInfo.onMacroBoundary( n ) && neighborInfo.neighborBoundaryType( n ) == DirichletBoundary )
                  {
                     Eigen::Matrix< real_t, Eigen::Dynamic, Eigen::Dynamic > localMat;
                     localMat.resize( Eigen::Index( numDofs ), 1 );
                     localMat.setZero();
                     form->integrateRHSDirichletBoundary( dim,
                                                          neighborInfo.elementVertexCoords(),
                                                          neighborInfo.interfaceVertexCoords( n ),
                                                          neighborInfo.oppositeVertexCoords( n ),
                                                          neighborInfo.outwardNormal( n ),
                                                          *basis(),
                                                          polyDegree,
                                                          localMat );

                     for ( uint_t dofIdx = 0; dofIdx < numDofs; dofIdx++ )
                     {
                        dofMemory[volumedofspace::indexing::index(
                            elementIdx.x(), elementIdx.y(), faceType, dofIdx, numDofs, level, memLayout )] +=
                            ValueType( localMat( Eigen::Index( dofIdx ), 0 ) );
                     }
                  }
               }
            }
         }
      }
   }
}

template < typename ValueType >
void DGFunction< ValueType >::toVector( const DGFunction< idx_t >&            numerator,
                                        const std::shared_ptr< VectorProxy >& vec,
                                        uint_t                                level,
                                        DoFType                               flag ) const
{
   if ( this->getStorage()->hasGlobalCells() )
   {
      // 3D
      WALBERLA_ABORT( "enumerate() not implemented in 3D." );
   }
   else
   {
      // 2D
      for ( const auto& it : this->getStorage()->getFaces() )
      {
         const auto faceID = it.first;
         const auto face   = *it.second;

         const auto degree  = polynomialDegree( faceID );
         const auto numDofs = basis()->numDoFsPerElement( uint_c( degree ) );

         const auto indices   = numerator.volumeDoFFunction()->dofMemory( faceID, level );
         const auto dofs      = volumeDoFFunction()->dofMemory( faceID, level );
         const auto memLayout = volumeDoFFunction()->memoryLayout();

         for ( auto faceType : facedof::allFaceTypes )
         {
            for ( const auto& idxIt : facedof::macroface::Iterator( level, faceType ) )
            {
               for ( uint_t i = 0; i < numDofs; i++ )
               {
                  const auto vectorIdx =
                      indices[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )];
                  const auto value =
                      dofs[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )];
                  vec->setValue( uint_c( vectorIdx ), real_t( value ) );
               }
            }
         }
      }
   }

   WALBERLA_UNUSED( flag );
}

template < typename ValueType >
void DGFunction< ValueType >::fromVector( const DGFunction< idx_t >&            numerator,
                                          const std::shared_ptr< VectorProxy >& vec,
                                          uint_t                                level,
                                          DoFType                               flag ) const
{
   if ( this->getStorage()->hasGlobalCells() )
   {
      // 3D
      WALBERLA_ABORT( "enumerate() not implemented in 3D." );
   }
   else
   {
      // 2D
      for ( const auto& it : this->getStorage()->getFaces() )
      {
         const auto faceID = it.first;
         const auto face   = *it.second;

         const auto degree  = polynomialDegree( faceID );
         const auto numDofs = basis()->numDoFsPerElement( uint_c( degree ) );

         const auto indices   = numerator.volumeDoFFunction()->dofMemory( faceID, level );
         auto       dofs      = volumeDoFFunction()->dofMemory( faceID, level );
         const auto memLayout = volumeDoFFunction()->memoryLayout();

         for ( auto faceType : facedof::allFaceTypes )
         {
            for ( const auto& idxIt : facedof::macroface::Iterator( level, faceType ) )
            {
               for ( uint_t i = 0; i < numDofs; i++ )
               {
                  const auto vectorIdx =
                      indices[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )];
                  const auto value = vec->getValue( uint_c( vectorIdx ) );
                  dofs[volumedofspace::indexing::index( idxIt.x(), idxIt.y(), faceType, i, numDofs, level, memLayout )] =
                      ValueType( value );
               }
            }
         }
      }
   }

   WALBERLA_UNUSED( flag );
}

/// explicit instantiation
template class DGFunction< double >;
template class DGFunction< float >;
template class DGFunction< int32_t >;
template class DGFunction< int64_t >;

} // namespace dg

void applyDirichletBC( const dg::DGFunction< idx_t >& numerator, std::vector< idx_t >& mat, uint_t level )
{
   WALBERLA_LOG_WARNING_ON_ROOT( "DGFunction: BCs are not applied to sparse matrix." );
   WALBERLA_UNUSED( numerator );
   WALBERLA_UNUSED( mat );
   WALBERLA_UNUSED( level );
}

} // namespace hyteg