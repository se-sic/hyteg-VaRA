
#pragma once

#include "hyteg/primitives/Primitive.hpp"
#include "hyteg/types/pointnd.hpp"
#include "hyteg/types/flags.hpp"
#include "core/logging/Logging.h"

namespace hyteg {

class Cell : public Primitive
{
public:

  /// Creates a macro-cell instance
  ///
  /// \param primitiveID ID of this macro-cell
  /// \param vertexIDs neighbor macro-vertex IDs
  /// \param edgeIDs neighbor macro-edge IDs
  /// \param faceIDs neighbor macro-face IDs
  /// \param coordinates absolute coordinates of the four vertices of this macro-cell
  /// \param edgeLocalVertexToCellLocalVertexMaps Maps for each edge of the macro-cell that map the local vertex ID (one of 0, 1) of the edge
  ///                                             to the corresponding local vertex ID (one of 0, 1, 2, 3) of this macro-cell. \n
  ///                                             Refer to the documentation for detailed illustrations of that mapping.
  /// \param faceLocalVertexToCellLocalVertexMaps Maps for each face of the macro-cell that map the local vertex ID (one of 0, 1, 2) of the face
  ///                                             to the corresponding local vertex ID (one of 0, 1, 2, 3) of this macro-cell. \n
  ///                                             Refer to the documentation for detailed illustrations of that mapping.
  Cell( const PrimitiveID                & primitiveID,
        const std::vector< PrimitiveID > & vertexIDs,
        const std::vector< PrimitiveID > & edgeIDs,
        const std::vector< PrimitiveID > & faceIDs,
        const std::array< Point3D, 4 >   & coordinates,
        const std::array< std::map< uint_t, uint_t >, 6 > & edgeLocalVertexToCellLocalVertexMaps,
        const std::array< std::map< uint_t, uint_t >, 4 > & faceLocalVertexToCellLocalVertexMaps );

  Cell( walberla::mpi::RecvBuffer & recvBuffer ) : Primitive( recvBuffer ) { deserializeSubclass( recvBuffer ); }

  virtual void getLowerDimNeighbors ( std::vector< PrimitiveID > & lowerDimNeighbors )  const { getNeighborFaces( lowerDimNeighbors ); }
  virtual void getHigherDimNeighbors( std::vector< PrimitiveID > & higherDimNeighbors ) const { higherDimNeighbors.clear(); }

  virtual const std::vector< PrimitiveID > & getLowerDimNeighbors()  const { return neighborFaces(); }
  virtual const std::vector< PrimitiveID > & getHigherDimNeighbors() const { WALBERLA_ASSERT_EQUAL( getNumNeighborCells(), 0 ); return neighborCells(); }

  virtual uint_t getNumLowerDimNeighbors()  const { return getNumNeighborFaces(); }
  virtual uint_t getNumHigherDimNeighbors() const { return 0; }

  /// Returns a pointer to the data that belongs to the passed \ref PrimitiveDataID.
  /// \param index the \ref PrimitiveDataID of the data that should be returned
  template< typename DataType >
  DataType* getData( const PrimitiveDataID< DataType, Cell > & index ) const
  {
    return genericGetData< DataType >( index );
  }

  const std::array< Point3D, 4 > &                    getCoordinates()                             const { return coordinates_; }
  const std::array< std::map< uint_t, uint_t >, 6 > & getEdgeLocalVertexToCellLocalVertexMaps()    const { return edgeLocalVertexToCellLocalVertexMaps_; }
  const std::array< std::map< uint_t, uint_t >, 4 > & getFaceLocalVertexToCellLocalVertexMaps()    const { return faceLocalVertexToCellLocalVertexMaps_; }
        uint_t                                        getLocalVertexID( const PrimitiveID & vertexID ) const;
        uint_t                                        getLocalEdgeID  ( const PrimitiveID & edgeID )   const;
        uint_t                                        getLocalFaceID  ( const PrimitiveID & faceID )   const;


protected:

  /// Not public in order to guarantee that data is only added through the governing structure.
  /// This ensures valid DataIDs.
  template< typename DataType, typename DataHandlingType >
  inline void addData( const PrimitiveDataID< DataType, Cell > & index,
                       const std::shared_ptr< DataHandlingType > & dataHandling )
  {
    genericAddData( index, dataHandling, this );
  }

  virtual void   serializeSubclass ( walberla::mpi::SendBuffer & sendBuffer ) const;
  virtual void deserializeSubclass ( walberla::mpi::RecvBuffer & recvBuffer );

private:

  std::array< Point3D, 4 > coordinates_;
  std::array< std::map< uint_t, uint_t >, 6 > edgeLocalVertexToCellLocalVertexMaps_;
  std::array< std::map< uint_t, uint_t >, 4 > faceLocalVertexToCellLocalVertexMaps_;

};

}