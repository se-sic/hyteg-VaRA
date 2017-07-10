#pragma once

#include "tinyhhg_core/support.hpp"
#include "tinyhhg_core/primitives/vertex.hpp"
#include "tinyhhg_core/primitives/edge.hpp"
#include "tinyhhg_core/primitives/face.hpp"

#include "tinyhhg_core/levelinfo.hpp"

#include "core/logging/Logging.h"

#include <string>
#include <map>


namespace hhg
{

class VertexP1BubbleStencilMemory
  :public VertexMemory
{
public:
  VertexP1BubbleStencilMemory() : VertexMemory(MemoryType::P1BubbleFunction) { ; }

  std::map<size_t, std::unique_ptr<real_t[]>> data;
  size_t num_deps_;

  inline std::unique_ptr<real_t[]>& addlevel(size_t level, size_t num_deps)
  {
    if (data.count(level)>0)
      WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      this->num_deps_ = num_deps;
      data[level] = hhg::make_unique<real_t[]>(getSize(level));
    }
    return data[level];
  }

  inline size_t getSize(size_t level)
  {
    return levelinfo::num_microvertices_per_vertex(level) + num_deps_;
  }
};


class VertexP1BubbleFunctionMemory
  :public VertexMemory
{
public:
  VertexP1BubbleFunctionMemory() : VertexMemory(MemoryType::P1BubbleStencil) { ; }

  std::map<size_t, std::unique_ptr<real_t[]>> data;
  size_t num_deps_;

  inline std::unique_ptr<real_t[]>& addlevel(size_t level, size_t num_deps)
  {
    if (data.count(level)>0)
      WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      this->num_deps_ = num_deps;
      data[level] = hhg::make_unique<real_t[]>(getSize(level));
    }
    return data[level];
  }

  inline size_t getSize(size_t level)
  {
    return levelinfo::num_microvertices_per_vertex(level) + num_deps_ * 2;
  }
};


class EdgeP1BubbleStencilMemory
  :public EdgeMemory
{
public:
  EdgeP1BubbleStencilMemory() : EdgeMemory(MemoryType::P1BubbleStencil) { ; }

  std::map<size_t, std::unique_ptr<real_t[]>> data;

  inline std::unique_ptr<real_t[]>& addlevel(size_t level)
  {
    //WALBERLA_LOG_DEVEL("EdgeStencilMemory, kind = " + std::to_string(this->type));
    if (data.count(level)>0)
      WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      data[level] = hhg::make_unique<real_t[]>(getSize(level));
    }
    return data[level];
  }

  inline size_t getSize(size_t /*level*/)
  {
    return 13;
  }
};


class EdgeP1BubbleFunctionMemory
  :public EdgeMemory
{
public:
  EdgeP1BubbleFunctionMemory() : EdgeMemory(MemoryType::P1BubbleFunction) { ; }

  std::map<size_t, std::unique_ptr<real_t[]>> data;
  size_t num_deps_;

  inline std::unique_ptr<real_t[]>& addlevel(size_t level, size_t num_deps)
  {
    if (data.count(level)>0)
    WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      this->num_deps_ = num_deps;
      data[level] = hhg::make_unique<real_t[]>(getSize(level));
    }
    return data[level];
  }

  inline size_t getSize(size_t level)
  {
    size_t num_vertex_dofs = levelinfo::num_microvertices_per_edge(level);
    num_vertex_dofs = num_vertex_dofs + num_deps_*(num_vertex_dofs-1);

    size_t num_cell_dofs = num_deps_ * (2 * levelinfo::num_microedges_per_edge(level) - 1);

    return num_vertex_dofs + num_cell_dofs;
  }
};


class FaceP1BubbleStencilMemory
  :public FaceMemory
{
public:
  FaceP1BubbleStencilMemory() : FaceMemory(MemoryType::P1BubbleStencil) { ; }

  typedef std::array<std::unique_ptr<real_t[]>, 3> StencilStack;

  std::map<size_t, StencilStack> data;

  inline StencilStack& addlevel(size_t level)
  {
    if (data.count(level)>0)
      WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      data[level] = StencilStack{hhg::make_unique<real_t[]>(getVertexStencilSize(level)),
                                 hhg::make_unique<real_t[]>(getGrayStencilSize(level)),
                                 hhg::make_unique<real_t[]>(getBlueStencilSize(level))};
    }
    return data[level];
  }

  inline size_t getVertexStencilSize(size_t /*level*/)
  {
    return 13;
  }

  inline size_t getGrayStencilSize(size_t /*level*/)
  {
    return 4;
  }

  inline size_t getBlueStencilSize(size_t /*level*/)
  {
    return 4;
  }
};


class FaceP1BubbleFunctionMemory
  :public FaceMemory
{
public:
  FaceP1BubbleFunctionMemory() : FaceMemory(MemoryType::P1BubbleFunction) { ; }

  std::map<size_t, std::unique_ptr<real_t[]>> data;

  inline std::unique_ptr<real_t[]>& addlevel(size_t level)
  {
    if (data.count(level)>0)
      WALBERLA_LOG_WARNING("Level already exists.")
    else
    {
      data[level] = hhg::make_unique<real_t[]>(getSize(level));
    }
    return data[level];
  }

  inline size_t getSize(size_t level)
  {
    return levelinfo::num_microvertices_per_face(level) + levelinfo::num_microfaces_per_face(level);
  }
};

namespace P1Bubble {

inline VertexP1BubbleStencilMemory *getVertexStencilMemory(const Vertex &vertex, size_t id) {
  return static_cast<VertexP1BubbleStencilMemory *>(vertex.memory[id]);
}

inline VertexP1BubbleFunctionMemory *getVertexFunctionMemory(Vertex &vertex, size_t id) {
#ifndef NDEBUG
  if (vertex.memory.size() <= id) WALBERLA_LOG_WARNING("Memory ID is out of range");
  if (vertex.memory[id]->type != MemoryType::P1BubbleFunction) {
    WALBERLA_LOG_WARNING("Trying to convert something to VertexP1Memory which is not of the right type");
  }
#endif // !

  return static_cast<VertexP1BubbleFunctionMemory *>(vertex.memory[id]);
}

inline EdgeP1BubbleStencilMemory *getEdgeStencilMemory(const Edge &edge, size_t id) {
  return static_cast<EdgeP1BubbleStencilMemory *>(edge.memory[id]);
}

inline EdgeP1BubbleFunctionMemory *getEdgeFunctionMemory(const Edge &edge, size_t id) {
  return static_cast<EdgeP1BubbleFunctionMemory *>(edge.memory[id]);
}

inline FaceP1BubbleStencilMemory *getFaceStencilMemory(const Face &face, size_t id) {
  return static_cast<FaceP1BubbleStencilMemory *>(face.memory[id]);
}

inline FaceP1BubbleFunctionMemory *getFaceFunctionMemory(const Face &face, size_t id) {
  return static_cast<FaceP1BubbleFunctionMemory *>(face.memory[id]);
}

}
}