
#pragma once

#include "core/logging/Logging.h"
#include "tinyhhg_core/primitives/Primitive.hpp"
#include "tinyhhg_core/primitives/vertex.hpp"
#include "tinyhhg_core/primitives/edge.hpp"
#include "tinyhhg_core/primitives/face.hpp"
#include "tinyhhg_core/primitivedata/PrimitiveDataID.hpp"
#include "tinyhhg_core/primitivestorage/SetupPrimitiveStorage.hpp"

#include <map>
#include <vector>

namespace hhg {

class PrimitiveStorage : private walberla::NonCopyable
{
public:

        PrimitiveStorage( const SetupPrimitiveStorage & setupStorage ) :
          primitiveDataHandlers_( 0 )
        {}

        PrimitiveID addVertex();

  const Vertex* getVertex( const PrimitiveID & id ) const;
        Vertex* getVertex( const PrimitiveID & id );

  bool primitiveExistsLocally( const PrimitiveID & id ) const;

  template< typename DataType >
  inline PrimitiveDataID< DataType, Primitive > addPrimitiveData( const PrimitiveDataHandling< DataType, Primitive > & dataHandling,
  						       const std::string & identifier );

  template< typename DataType >
  inline PrimitiveDataID< DataType, Vertex > addVertexData( const PrimitiveDataHandling< DataType, Vertex > & dataHandling,
						    const std::string & identifier );

  template< typename DataType >
  inline PrimitiveDataID< DataType, Edge > addEdgeData( const PrimitiveDataHandling< DataType, Edge > & dataHandling,
  						  const std::string & identifier );

  template< typename DataType >
  inline PrimitiveDataID< DataType, Face > addFaceData( const PrimitiveDataHandling< DataType, Face > & dataHandling,
  						  const std::string & identifier );

private:

  template< typename DataType, typename PrimitiveType >
  inline PrimitiveDataID< DataType, PrimitiveType > generateDataID();

  template< typename DataType,
            typename PrimitiveType,
	    typename = typename std::enable_if< std::is_base_of< Primitive, PrimitiveType >::value >::type >
  inline void addPrimitiveData( const PrimitiveDataHandling< DataType, PrimitiveType > & dataHandling,
				const std::string & identifier,
				const std::map< PrimitiveID::IDType, PrimitiveType* > & primitives,
				const PrimitiveDataID< DataType, PrimitiveType > & dataID );

  std::map< PrimitiveID::IDType, Vertex* > vertices_;
  std::map< PrimitiveID::IDType, Edge*  >  edges_;
  std::map< PrimitiveID::IDType, Face* >   faces_;

  uint_t primitiveDataHandlers_;

};


template< typename DataType >
PrimitiveDataID< DataType, Primitive > PrimitiveStorage::addPrimitiveData( const PrimitiveDataHandling< DataType, Primitive > & dataHandling,
						                const std::string & identifier )
{
  WALBERLA_LOG_PROGRESS( "Adding data to all primitives (\"" << identifier << "\")" );
  PrimitiveDataID< DataType, Primitive > dataID = generateDataID< DataType, Primitive >();
  std::map< PrimitiveID::IDType, Primitive* > primitives;
  primitives.insert( vertices_.begin(), vertices_.end() );
  primitives.insert( edges_.begin(), edges_.end() );
  primitives.insert( faces_.begin(), faces_.end() );
  addPrimitiveData( dataHandling, identifier, primitives, dataID );
  return dataID;

}


template< typename DataType >
PrimitiveDataID< DataType, Vertex > PrimitiveStorage::addVertexData( const PrimitiveDataHandling< DataType, Vertex > & dataHandling,
						             const std::string & identifier )
{
  WALBERLA_LOG_PROGRESS( "Adding data to vertices (\"" << identifier << "\")" );
  PrimitiveDataID< DataType, Vertex > dataID = generateDataID< DataType, Vertex >();
  addPrimitiveData( dataHandling, identifier, vertices_, dataID );
  return dataID;
}


template< typename DataType >
PrimitiveDataID< DataType, Edge > PrimitiveStorage::addEdgeData( const PrimitiveDataHandling< DataType, Edge > & dataHandling,
						           const std::string & identifier )
{
  WALBERLA_LOG_PROGRESS( "Adding data to edges (\"" << identifier << "\")" );
  PrimitiveDataID< DataType, Edge > dataID = generateDataID< DataType, Edge >();
  addPrimitiveData( dataHandling, identifier, edges_, dataID );
  return dataID;
}


template< typename DataType >
PrimitiveDataID< DataType, Face > PrimitiveStorage::addFaceData( const PrimitiveDataHandling< DataType, Face > & dataHandling,
						             const std::string & identifier )
{
  WALBERLA_LOG_PROGRESS( "Adding data to faces (\"" << identifier << "\")" );
  PrimitiveDataID< DataType, Face > dataID = generateDataID< DataType, Face >();
  addPrimitiveData( dataHandling, identifier, faces_, dataID );
  return dataID;
}


template< typename DataType, typename PrimitiveType >
PrimitiveDataID< DataType, PrimitiveType > PrimitiveStorage::generateDataID()
{
#ifndef NDEBUG
  for ( auto it = vertices_.begin(); it != vertices_.end(); it++ )
  {
    WALBERLA_ASSERT_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
  }
  for ( auto it = edges_.begin(); it != edges_.end(); it++ )
  {
    WALBERLA_ASSERT_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
  }
  for ( auto it = faces_.begin(); it != faces_.end(); it++ )
  {
    WALBERLA_ASSERT_EQUAL( primitiveDataHandlers_, it->second->getNumberOfDataEntries() );
  }
#endif

  return PrimitiveDataID< DataType, PrimitiveType >( primitiveDataHandlers_++ );
}


template< typename DataType,
          typename PrimitiveType,
	  typename >
void PrimitiveStorage::addPrimitiveData( const PrimitiveDataHandling< DataType, PrimitiveType > & dataHandling,
					 const std::string & identifier,
					 const std::map< PrimitiveID::IDType, PrimitiveType* > & primitives,
					 const PrimitiveDataID< DataType, PrimitiveType > & dataID )
{
#ifndef NDEBUG
  for ( auto it = primitives.begin(); it != primitives.end(); it++ )
  {
    WALBERLA_ASSERT_EQUAL( primitiveDataHandlers_ - 1, it->second->getNumberOfDataEntries() );
  }
#endif

  for ( auto it = primitives.begin(); it != primitives.end(); it++ )
  {
    it->second->addData( dataID, dataHandling );
  }
}


} // namespace hhg


