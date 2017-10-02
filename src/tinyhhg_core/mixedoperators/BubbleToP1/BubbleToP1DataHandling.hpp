#pragma once

#include "tinyhhg_core/primitivedata/PrimitiveDataHandling.hpp"
#include "BubbleToP1Memory.hpp"

namespace hhg {

class VertexBubbleToP1StencilMemoryDataHandling : public OnlyInitializeDataHandling< VertexBubbleToP1StencilMemory, Vertex >
{
 public:

  VertexBubbleToP1StencilMemoryDataHandling( const uint_t & minLevel, const uint_t & maxLevel ) : minLevel_( minLevel ), maxLevel_( maxLevel ) {}

  std::shared_ptr< VertexBubbleToP1StencilMemory > initialize( const Vertex * const vertex ) const {
    auto vertexBubbleToP1FunctionMemory = std::make_shared< VertexBubbleToP1StencilMemory >();
    for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
    {
      vertexBubbleToP1FunctionMemory->addlevel( level, vertex->getNumNeighborFaces() );
    }
    return vertexBubbleToP1FunctionMemory;
  }

 private:

  uint_t minLevel_;
  uint_t maxLevel_;

};

class EdgeBubbleToP1StencilMemoryDataHandling : public OnlyInitializeDataHandling< EdgeBubbleToP1StencilMemory, Edge >
{
 public:

  EdgeBubbleToP1StencilMemoryDataHandling( const uint_t & minLevel, const uint_t & maxLevel ) : minLevel_( minLevel ), maxLevel_( maxLevel ) {}

  std::shared_ptr< EdgeBubbleToP1StencilMemory > initialize( const Edge * const edge ) const {
    auto edgeBubbleToP1FunctionMemory = std::make_shared< EdgeBubbleToP1StencilMemory >();
    for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
    {
      edgeBubbleToP1FunctionMemory->addlevel( level );
    }
    return edgeBubbleToP1FunctionMemory;
  }

 private:

  uint_t minLevel_;
  uint_t maxLevel_;

};

class FaceBubbleToP1StencilMemoryDataHandling : public OnlyInitializeDataHandling< FaceBubbleToP1StencilMemory, Face >
{
 public:

  FaceBubbleToP1StencilMemoryDataHandling( const uint_t & minLevel, const uint_t & maxLevel ) : minLevel_( minLevel ), maxLevel_( maxLevel ) {}

  std::shared_ptr< FaceBubbleToP1StencilMemory > initialize( const Face * const face ) const {
    auto faceBubbleToP1FunctionMemory = std::make_shared< FaceBubbleToP1StencilMemory >();
    for ( uint_t level = minLevel_; level <= maxLevel_; level++ )
    {
      faceBubbleToP1FunctionMemory->addlevel( level );
    }
    return faceBubbleToP1FunctionMemory;
  }

 private:

  uint_t minLevel_;
  uint_t maxLevel_;

};

}