#pragma once

#include "tinyhhg_core/primitivedata/PrimitiveDataHandling.hpp"
#include "P1ToBubbleMemory.hpp"

namespace hhg {

class FaceP1ToBubbleStencilMemoryDataHandling : public OnlyInitializeDataHandling< FaceP1ToBubbleStencilMemory, Face >
{
 public:

  FaceP1ToBubbleStencilMemoryDataHandling( const uint_t & minLevel, const uint_t & maxLevel ) : minLevel_( minLevel ), maxLevel_( maxLevel ) {}

  std::shared_ptr< FaceP1ToBubbleStencilMemory > initialize( const Face * const face ) const {
    auto faceP1ToBubbleFunctionMemory = std::make_shared< FaceP1ToBubbleStencilMemory >();
    for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
    {
      faceP1ToBubbleFunctionMemory->addlevel( level );
    }
    return faceP1ToBubbleFunctionMemory;
  }

 private:

  uint_t minLevel_;
  uint_t maxLevel_;

};

}