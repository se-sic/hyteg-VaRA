#pragma once

#include "tinyhhg_core/levelinfo.hpp"
#include "tinyhhg_core/p1bubblefunctionspace/p1bubblememory.hpp"
#include "p1bubbleedgeindex.hpp"

namespace hhg {
namespace P1BubbleEdge {

using walberla::uint_t;

/*!
 * Packs data on the edge into the \ref sendBuffer.
 * Only packs data owned by edge but not halo data
 * @param edge Edge
 * @param sendBuffer Buffer to pack into
 * @param memory_id Memory id of the data
 * @param level Multigrid level
 */
inline void packData(Edge &edge, uint_t memory_id, walberla::mpi::SendBuffer &sendBuffer, uint_t level) {
  auto& edge_data = P1Bubble::getEdgeFunctionMemory(edge, memory_id)->data[level];
  uint_t rowsize = levelinfo::num_microvertices_per_edge(level);
  //TODO change to index function
  for (uint_t i = 0; i < rowsize; ++i) {
    sendBuffer << edge_data[i];
  }
}

/*!
 * Packs for \ref vertex data on the edge into the \ref sendBuffer.
 * @param edge Edge
 * @param sendBuffer Buffer to pack into
 * @param memory_id Memory id of the data
 * @param level Multigrid level
 * @param vertex Vertex to send to
 */
inline void packDataforVertex(Edge &edge, uint_t memory_id, walberla::mpi::SendBuffer &sendBuffer, uint_t level, const Vertex &vertex) {
  auto& edge_data = P1Bubble::getEdgeFunctionMemory(edge, memory_id)->data[level];
  uint_t rowsize = levelinfo::num_microvertices_per_edge(level);
  uint_t vertex_id = edge.vertex_index(vertex);
  if(vertex_id == 0){
    sendBuffer << edge_data[0];
  } else if(vertex_id == 1){
    sendBuffer << edge_data[levelinfo::num_microvertices_per_edge(level)-1];
  } else {
    WALBERLA_LOG_WARNING("Vertex: " << vertex << " is not contained in Edge: " << edge);
  }
}


template<size_t Level>
inline void unpackFaceData_tmpl(Edge &edge, uint_t memory_id, walberla::mpi::RecvBuffer &recvBuffer, const Face &face)
{
  auto &edge_data = P1Bubble::getEdgeFunctionMemory(edge, memory_id)->data[Level];
  uint_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  uint_t pos = edge.face_index(face);
  EdgeCoordsVertex::DirVertex dir;
  //the first edge is the south edge and the second the north edge
  if(pos == 0)
  {
    dir = EdgeCoordsVertex::VERTEX_SE;
  }
  else if(pos == 1)
  {
    dir = EdgeCoordsVertex::VERTEX_N;
  }
  for (uint_t i = 0; i < rowsize -1; ++i)
  {
    recvBuffer >> edge_data[EdgeCoordsVertex::index<Level>(i,dir)];
  }
}
SPECIALIZE(void, unpackFaceData_tmpl, unpackFaceData)

template<size_t Level>
inline void unpackVertexData_tmpl(Edge &edge, uint_t memory_id, walberla::mpi::RecvBuffer &recvBuffer, const Vertex &vertex)
{
  auto &edge_data = P1Bubble::getEdgeFunctionMemory(edge, memory_id)->data[Level];
  uint_t nbr_edges = vertex.edges.size();
  uint_t edge_id = vertex.edge_index(edge);
  uint_t vertex_id = edge.vertex_index(vertex);
  //position in edge memory
  uint_t pos;
  EdgeCoordsVertex::DirVertex dir1;
  EdgeCoordsVertex::DirVertex dir2;
  if(vertex_id == 0){
    dir1 = EdgeCoordsVertex::CELL_GRAY_NE;
    dir2 = EdgeCoordsVertex::CELL_GRAY_SE;
    pos = 0;
  } else if(vertex_id == 1) {
    pos = levelinfo::num_microvertices_per_edge(Level) - 1;
    dir1 = EdgeCoordsVertex::CELL_GRAY_NW;
    dir2 = EdgeCoordsVertex::CELL_GRAY_SW;
  } else {
    WALBERLA_LOG_WARNING("vertex " << vertex << " is not contained in edge")
  }
  recvBuffer >> edge_data[EdgeCoordsVertex::index<Level>(pos,EdgeCoordsVertex::VERTEX_C)];
  //remove unneeded data
  if(edge_id > 1) {
    for (uint_t i = 0; i < edge_id - 1; ++i) {
      auto dump = NULL;
      recvBuffer >> dump;
    }
  }
  recvBuffer >> edge_data[EdgeCoordsVertex::index<Level>(pos,dir1)];
  recvBuffer >> edge_data[EdgeCoordsVertex::index<Level>(pos,dir2)];
}

SPECIALIZE(void, unpackVertexData_tmpl, unpackVertexData)

}// namespace P1BubbleEdg8e
}// namespace hhg
