
#pragma once

#include "tinyhhg_core/primitivedata/PrimitiveDataID.hpp"
#include "tinyhhg_core/primitivedata/PrimitiveDataHandling.hpp"
#include "core/NonCopyable.h"
#include "tinyhhg_core/primitiveid.hpp"

#include <memory>
#include <vector>

namespace hhg {

// to removed when moving to walberla namespace
using walberla::NonCopyable;

namespace internal {

class PrimitiveData : private NonCopyable
{
public:

  template< typename DataType >
  PrimitiveData( DataType* ptr ) : ptr_( ptr )
  {
    WALBERLA_ASSERT_NOT_NULLPTR( ptr );
  }

  template< typename DataType >
  DataType* get()
  {
    return static_cast< DataType* >( ptr_ );
  }

private:

  void *ptr_;

};

class ConstPrimitiveData : private NonCopyable
{
public:

  template< typename DataType >
  ConstPrimitiveData( const DataType* ptr ) : ptr_( ptr )
  {
    WALBERLA_ASSERT_NOT_NULLPTR( ptr );
  }

  template< typename DataType >
  const DataType* get()
  {
    return static_cast< const DataType* >( ptr_ );
  }

private:

  const void *ptr_;

};

}

class PrimitiveID;

/// \brief Base class for primitive geometries
/// \author Nils Kohl (nils.kohl@fau.de)
///
/// The Primitive class is intended to be used as a base class for primitives like vertices or edges.
///
/// It is able to store arbitrary data structures (e.g. from the standard library or custom classes)
/// that can, however only be added through a governing structure, for example the \ref PrimitiveStorage class.
/// Using the respective \ref PrimitiveDataID a pointer to the data can be obtained.
///
/// For more details on the data handling refer to \ref PrimitiveDataHandling.
///
class Primitive : private NonCopyable
{
public:

  friend class PrimitiveStorage;

  typedef internal::PrimitiveData PrimitiveData;
  typedef internal::ConstPrimitiveData ConstPrimitiveData;

  /// Returns a pointer to the data that belongs to the passed \ref PrimitiveDataID.
  /// \param index the \ref PrimitiveDataID of the data that should be returned
  template< typename DataType >
  DataType* getData( const PrimitiveDataID< DataType > & index )
  {
    return data_[ index ].first->template get< DataType >();
  }

  /// Returns a pointer to the \ref PrimitiveDataHandling that belongs to the passed \ref PrimitiveDataID.
  /// \param index the \ref PrimitiveDataID of the data handling that should be returned
  template< typename DataType >
  PrimitiveDataHandling< DataType >* getDataHandling( const PrimitiveDataID< DataType > & index )
  {
    return data_[ index ].second->template get< PrimitiveDataHandling< DataType > >();
  }

  uint_t getNumberOfDataEntries() const
  {
    return data_.size();
  }

private:

  /// Must stay private in order to guarantee that data is only added through the governing structure.
  /// This ensures valid DataIDs.
  template< typename DataType >
  inline void addData( const PrimitiveDataID< DataType > & index,
                       const PrimitiveDataHandling< DataType > & dataHandling );

  /// Holds a pointer to the actual data in the first entry and a pointer to the respective datahandling in the second entry.
  /// This way it is possible to loop over the data to for example serialize all registered data.
  std::vector< std::pair< PrimitiveData*, ConstPrimitiveData* > > data_;

  PrimitiveID primitiveID_;

};

template< typename DataType >
void Primitive::addData( const PrimitiveDataID< DataType > & index,
		         const PrimitiveDataHandling< DataType > & dataHandling )
{
 if( data_.size() <= index )
 {
   data_.resize( index + 1, std::pair< PrimitiveData*, ConstPrimitiveData* >( NULL, NULL ) );
 }

 data_[index].first = new PrimitiveData( dataHandling.initialize( NULL ) );
 data_[index].second = new ConstPrimitiveData( &dataHandling );
}



} // namespace hhg

