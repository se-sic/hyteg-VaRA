#ifndef FACE_HPP
#define FACE_HPP

#include <tinyhhg_core/types/pointnd.hpp>
#include <tinyhhg_core/types/flags.hpp>
#include <tinyhhg_core/primitives/Primitive.hpp>
#include <core/DataTypes.h>
#include <core/Deprecated.h>

#include <array>
#include <vector>

namespace hhg
{

class Edge;
class FaceMemory;

class Face : public Primitive
{
public:
  WALBERLA_DEPRECATED( Face(size_t id, Edge* edges[3]) );

  size_t vertex_index(const Vertex& vertex) const;
  size_t edge_index(const Edge& edge) const;

  std::vector<Edge*> adjacent_edges(const Vertex& vertex) const;
  Vertex* get_vertex_opposite_to_edge(const Edge& edge) const;

  size_t id;
  walberla::uint_t rank;
  DoFType type;
  real_t area;
  Edge* edges[3];
  std::vector<Vertex*> vertices;
  std::array<int, 3> edge_orientation;
  std::array<Point3D, 3> coords;

  std::vector<FaceMemory*> memory;

  friend std::ostream &operator<<(std::ostream &os, const Face &face);

  /// Returns a pointer to the data that belongs to the passed \ref PrimitiveDataID.
  /// \param index the \ref PrimitiveDataID of the data that should be returned
  template< typename DataType >
  DataType* getData( const PrimitiveDataID< DataType, Face > & index ) const
  {
    return genericGetData< DataType >( index );
  }
};

class FaceMemory
{
public:
  const MemoryType type;
  virtual ~FaceMemory() { }

protected:
  FaceMemory(MemoryType t) : type(t) { ; }
};
}

#endif /* FACE_HPP */
