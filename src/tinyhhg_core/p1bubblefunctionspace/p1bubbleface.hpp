#pragma once

#include "tinyhhg_core/levelinfo.hpp"
#include "tinyhhg_core/macros.hpp"
#include "tinyhhg_core/p1bubblefunctionspace/p1bubblememory.hpp"
#include "p1bubblefacecomm.hpp"
#include "p1bubblefaceindex.hpp"

namespace hhg
{
namespace P1BubbleFace
{
//FIXME this can be removed after we are in waberla namespace
using namespace walberla::mpistubs;


inline void allocate(Face& face, size_t memory_id, size_t minLevel, size_t maxLevel)
{
  face.memory.push_back(new FaceP1BubbleFunctionMemory());

  for (size_t level = minLevel; level <= maxLevel; ++level)
  {
    P1Bubble::getFaceFunctionMemory(face, memory_id)->addlevel(level);
  }
}

inline void free(Face& face, size_t memory_id)
{
  delete face.memory[memory_id];
  face.memory[memory_id] = nullptr;
}

template<size_t Level>
inline void interpolate_tmpl(Face& face, size_t memory_id, std::function<real_t(const hhg::Point3D&)>& expr)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;
  Point3D x, x0;

  if (face.edge_orientation[0] == 1)
  {
    x0 = face.edges[0]->v0->coords;
  }
  else
  {
    x0 = face.edges[0]->v1->coords;
  }

  Point3D d0 = face.edge_orientation[0] * face.edges[0]->direction / (walberla::real_c(rowsize-1));
  Point3D d2 = -face.edge_orientation[2] * face.edges[2]->direction / (walberla::real_c(rowsize-1));

  auto& dst = P1Bubble::getFaceFunctionMemory(face, memory_id)->data[Level];

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    x = x0;
    x += i * d2 + d0;

    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      dst[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] = expr(x);
      x += d0;
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, interpolate_tmpl, interpolate)

inline void pull_edges(Face& face, size_t memory_id, size_t level)
{
  auto MPIManager = walberla::mpi::MPIManager::instance();
  walberla::mpi::BufferSystem bs (MPIManager->comm());
  for(Edge* edge : face.edges){
    if(edge->rank == MPIManager->rank()){
      P1BubbleEdge::packData(*edge, memory_id, bs.sendBuffer(face.rank), level, face);
    }
    if(face.rank == MPIManager->rank()){
      bs.setReceiverInfo( walberla::mpi::BufferSystem::onlyRank(edge->rank), true );
    } else {
      bs.setReceiverInfo(walberla::mpi::BufferSystem::noRanks(),false);
    }
    bs.sendAll();
    for(auto i = bs.begin(); i != bs.end(); ++i){
      unpackEdgeData(level,face,memory_id,i.buffer(),*edge);
    }
  }

}

template<size_t Level>
inline void assign_tmpl(Face& face, const std::vector<real_t>& scalars, const std::vector<size_t>& src_ids, size_t dst_id)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      real_t tmp = scalars[0] * P1Bubble::getFaceFunctionMemory(face, src_ids[0])->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)];

      for (size_t k = 1; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] = tmp;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      real_t tmp = scalars[0] * P1Bubble::getFaceFunctionMemory(face, src_ids[0])->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)];

      for (size_t k = 1; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] = tmp;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      real_t tmp = scalars[0] * P1Bubble::getFaceFunctionMemory(face, src_ids[0])->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)];

      for (size_t k = 1; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] = tmp;
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, assign_tmpl, assign)

template<size_t Level>
inline void add_tmpl(Face& face, const std::vector<real_t>& scalars, const std::vector<size_t>& src_ids, size_t dst_id)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      real_t tmp = 0.0;

      for (size_t k = 0; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] += tmp;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      real_t tmp = 0.0;

      for (size_t k = 0; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] += tmp;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      real_t tmp = 0.0;

      for (size_t k = 0; k < src_ids.size(); ++k)
      {
        tmp += scalars[k] * P1Bubble::getFaceFunctionMemory(face, src_ids[k])->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)];
      }
      P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] += tmp;
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, add_tmpl, add)

template<size_t Level>
inline real_t dot_tmpl(Face& face, size_t lhs_id, size_t rhs_id)
{
  real_t sp = 0.0;
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  auto& lhs_data = P1Bubble::getFaceFunctionMemory(face, lhs_id)->data[Level];
  auto& rhs_data = P1Bubble::getFaceFunctionMemory(face, rhs_id)->data[Level];

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      sp += lhs_data[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] * rhs_data[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)];
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      sp += lhs_data[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] * rhs_data[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)];
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      sp += lhs_data[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] * rhs_data[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)];
    }
    --inner_rowsize;
  }

  return sp;
}

SPECIALIZE(real_t, dot_tmpl, dot)

template<size_t Level>
inline void apply_tmpl(Face& face, size_t opr_id, size_t src_id, size_t dst_id, UpdateType update)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  auto& opr_data = P1Bubble::getFaceStencilMemory(face, opr_id)->data[Level];

  auto& face_vertex_stencil = opr_data[0];
  auto& face_gray_stencil = opr_data[1];
  auto& face_blue_stencil = opr_data[2];

  auto& src = P1Bubble::getFaceFunctionMemory(face, src_id)->data[Level];
  auto& dst = P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level];

  real_t tmp;

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      tmp = face_vertex_stencil[CoordsVertex::VERTEX_C] * src[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)];

      for (auto neighbor : CoordsVertex::neighbors)
      {
        tmp += face_vertex_stencil[neighbor] * src[CoordsVertex::index<Level>(i, j, neighbor)];
      }

      if (update == Replace) {
        dst[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] = tmp;
      } else if (update == Add) {
        dst[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] += tmp;
      }
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      tmp = face_gray_stencil[CoordsCellGray::CELL_GRAY_C] * src[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)];

      for (auto neighbor : CoordsCellGray::neighbors)
      {
        tmp += face_gray_stencil[neighbor] * src[CoordsCellGray::index<Level>(i, j, neighbor)];
      }

      if (update == Replace) {
        dst[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] = tmp;
      } else if (update == Add) {
        dst[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] += tmp;
      }
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      tmp = face_blue_stencil[CoordsCellBlue::CELL_BLUE_C] * src[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)];

      for (auto neighbor : CoordsCellBlue::neighbors)
      {
        tmp += face_blue_stencil[neighbor] * src[CoordsCellBlue::index<Level>(i, j, neighbor)];
      }

      if (update == Replace) {
        dst[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] = tmp;
      } else if (update == Add) {
        dst[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] += tmp;
      }
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, apply_tmpl, apply)

//template<size_t Level>
//inline void smooth_gs_tmpl(Face& face, size_t opr_id, size_t dst_id, size_t rhs_id)
//{
//  using namespace CoordsVertex;
//  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
//  size_t inner_rowsize = rowsize;
//
//  real_t* opr_data = getFaceStencilMemory(face, opr_id)->data[Level];
//  real_t* dst = getFaceP1BubbleFunctionMemory(face, dst_id)->data[Level];
//  real_t* rhs = getFaceP1BubbleFunctionMemory(face, rhs_id)->data[Level];
//
//  real_t tmp;
//
//  for (size_t i = 1; i < rowsize - 2; ++i)
//  {
//    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
//    {
//      tmp = rhs[index<Level>(i, j, VERTEX_C)];
//
//      for (auto neighbor : neighbors)
//      {
//        tmp -= opr_data[neighbor] * dst[index<Level>(i, j, neighbor)];
//      }
//
//      dst[index<Level>(i, j, VERTEX_C)] = tmp / opr_data[VERTEX_C];
//    }
//    --inner_rowsize;
//  }
//}
//
//SPECIALIZE(void, smooth_gs_tmpl, smooth_gs)
//
//template<size_t Level>
//inline void prolongate_tmpl(Face& face, size_t memory_id)
//{
//  using namespace CoordsVertex;
//  size_t N_c = levelinfo::num_microvertices_per_edge(Level);
//  size_t N_c_i = N_c;
//
//  real_t* v_f = getFaceP1BubbleFunctionMemory(face, memory_id)->data[Level+1];
//  real_t* v_c = getFaceP1BubbleFunctionMemory(face, memory_id)->data[Level];
//
//  size_t j;
//
//  for (size_t i = 1; i < N_c-1; ++i)
//  {
//    for (j = 1; j < N_c_i-2; ++j)
//    {
//      v_f[index<Level+1>(2*i, 2*j, VERTEX_C)] = v_c[index<Level>(i, j, VERTEX_C)];
//      v_f[index<Level+1>(2*i - 1, 2*j - 1, VERTEX_C)] = 0.5 * (v_c[index<Level>(i-1, j, VERTEX_C)] + v_c[index<Level>(i, j-1, VERTEX_C)]);
//      v_f[index<Level+1>(2*i - 1, 2*j, VERTEX_C)] = 0.5 * (v_c[index<Level>(i, j, VERTEX_C)] + v_c[index<Level>(i-1, j, VERTEX_C)]);
//      v_f[index<Level+1>(2*i, 2*j - 1, VERTEX_C)] = 0.5 * (v_c[index<Level>(i, j, VERTEX_C)] + v_c[index<Level>(i, j-1, VERTEX_C)]);
//    }
//
//    v_f[index<Level+1>(2*i - 1, 2*j - 1, VERTEX_C)] = 0.5 * (v_c[index<Level>(i-1, j, VERTEX_C)] + v_c[index<Level>(i, j-1, VERTEX_C)]);
//    v_f[index<Level+1>(2*i - 1, 2*j, VERTEX_C)] = 0.5 * (v_c[index<Level>(i, j, VERTEX_C)] + v_c[index<Level>(i-1, j, VERTEX_C)]);
//    v_f[index<Level+1>(2*i, 2*j - 1, VERTEX_C)] = 0.5 * (v_c[index<Level>(i, j, VERTEX_C)] + v_c[index<Level>(i, j-1, VERTEX_C)]);
//
//    --N_c_i;
//  }
//}
//
//SPECIALIZE(void, prolongate_tmpl, prolongate)
//
//template<size_t Level>
//inline void restrict_tmpl(Face& face, size_t memory_id)
//{
//  using namespace CoordsVertex;
//  size_t N_c = levelinfo::num_microvertices_per_edge(Level-1);
//  size_t N_c_i = N_c;
//
//  real_t* v_f = getFaceP1BubbleFunctionMemory(face, memory_id)->data[Level];
//  real_t* v_c = getFaceP1BubbleFunctionMemory(face, memory_id)->data[Level-1];
//
//  real_t tmp;
//
//  for (size_t i = 1; i < N_c - 2; ++i)
//  {
//    for (size_t j = 1; j < N_c_i - 2; ++j)
//    {
//      tmp = v_f[index<Level>(2*i, 2*j, VERTEX_C)];
//
//      for (auto neighbor : neighbors)
//      {
//        tmp += 0.5 * v_f[index<Level>(2*i, 2*j, neighbor)];
//      }
//
//      v_c[index<Level-1>(i, j, VERTEX_C)] = tmp;
//    }
//
//    --N_c_i;
//  }
//}
//
//SPECIALIZE(void, restrict_tmpl, restrict)
//
///// Checks if a given index is a the boundary of the face
///// \param index The index which should be checked
///// \param length Size of the triangle in the first dimension
//bool is_boundary(size_t index, size_t length)
//{
//  if(index < length) return true;
//  while(index >= length){
//    index -= length;
//    length--;
//  }
//  return(index == 0 || index == (length -1));
//}
//
//inline void printmatrix(Face& face, size_t opr_id, size_t src_id, size_t level)

template<size_t Level>
inline void printFunctionMemory(Face& face, uint_t memory_id){
  using namespace std;
  auto& faceMemory = hhg::P1Bubble::getFaceFunctionMemory(face, 0)->data[Level];
  uint_t verticesPerDge = hhg::levelinfo::num_microvertices_per_edge(Level);
  cout << setfill('=') << setw(100) << "" << endl;
  cout << face << std::left << setprecision(1) << fixed << setfill(' ') << endl;
  std::cout << "Cell Blue: " << std::endl;
  for (size_t i = 0; i < verticesPerDge-2; ++i) {
    for (size_t j = 0; j < verticesPerDge-2 - i; ++j) {
      cout << setw(5) << faceMemory[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] << "|";
    }
    std::cout << std::endl;
  }
  cout << "Cell Gray: " << std::endl;
  for (size_t i = 0; i < verticesPerDge-1; ++i) {
    for (size_t j = 0; j < verticesPerDge-1 - i; ++j) {
      cout << setw(5) << faceMemory[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] << "|";
    }
    std::cout << std::endl;
  }
  cout << "Vertices: " << std::endl;
  for (size_t i = 0; i < verticesPerDge; ++i) {
    for (size_t j = 0; j < verticesPerDge - i; ++j) {
      cout << setw(5) << faceMemory[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] << "|";
    }
    std::cout << std::endl;
  }
  cout << setw(100) << setfill(' ') << endl;

}


template<size_t Level>
inline void enumerate_tmpl(Face& face, size_t memory_id, size_t& num)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      P1Bubble::getFaceFunctionMemory(face, memory_id)->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] = num++;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      P1Bubble::getFaceFunctionMemory(face, memory_id)->data[Level][CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)] = num++;
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      P1Bubble::getFaceFunctionMemory(face, memory_id)->data[Level][CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)] = num++;
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, enumerate_tmpl, enumerate)

template<size_t Level>
inline void enumerate_p1_tmpl(Face& face, size_t memory_id, size_t& num)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      P1Bubble::getFaceFunctionMemory(face, memory_id)->data[Level][CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)] = num++;
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, enumerate_p1_tmpl, enumerate_p1)

template<size_t Level>
inline void saveOperator_tmpl(Face& face, std::ostream& out, size_t opr_id, size_t src_id, size_t dst_id, DoFType flag)
{
  size_t rowsize = levelinfo::num_microvertices_per_edge(Level);
  size_t inner_rowsize = rowsize;

  auto& opr_data = P1Bubble::getFaceStencilMemory(face, opr_id)->data[Level];

  auto& face_vertex_stencil = opr_data[0];
  auto& face_gray_stencil = opr_data[1];
  auto& face_blue_stencil = opr_data[2];

  auto& src = P1Bubble::getFaceFunctionMemory(face, src_id)->data[Level];
  auto& dst = P1Bubble::getFaceFunctionMemory(face, dst_id)->data[Level];

  for (size_t i = 1; i < rowsize - 2; ++i)
  {
    for (size_t j = 1; j  < inner_rowsize - 2; ++j)
    {
      out << fmt::format("{}\t{}\t{}\n", dst[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)], src[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)], face_vertex_stencil[CoordsVertex::VERTEX_C]);

      for (auto neighbor : CoordsVertex::neighbors)
      {
        out << fmt::format("{}\t{}\t{}\n", dst[CoordsVertex::index<Level>(i, j, CoordsVertex::VERTEX_C)], src[CoordsVertex::index<Level>(i, j, neighbor)], face_vertex_stencil[neighbor]);
      }
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 1; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 1; ++j)
    {
      // TODO: how to do this better?
      if ((i == 0 && j == 0) || (i == 0 && j == rowsize - 2) || (i == rowsize - 2 && j == 0)) {
        continue;
      }

      out << fmt::format("{}\t{}\t{}\n", dst[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)], src[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)], face_gray_stencil[CoordsCellGray::CELL_GRAY_C]);

      for (auto neighbor : CoordsCellGray::neighbors)
      {
        out << fmt::format("{}\t{}\t{}\n", dst[CoordsCellGray::index<Level>(i, j, CoordsCellGray::CELL_GRAY_C)], src[CoordsCellGray::index<Level>(i, j, neighbor)], face_gray_stencil[neighbor]);
      }
    }
    --inner_rowsize;
  }

  inner_rowsize = rowsize;

  for (size_t i = 0; i < rowsize - 2; ++i)
  {
    for (size_t j = 0; j  < inner_rowsize - 2; ++j)
    {
      out << fmt::format("{}\t{}\t{}\n", dst[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)], src[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)], face_blue_stencil[CoordsCellBlue::CELL_BLUE_C]);

      for (auto neighbor : CoordsCellBlue::neighbors)
      {
        out << fmt::format("{}\t{}\t{}\n", dst[CoordsCellBlue::index<Level>(i, j, CoordsCellBlue::CELL_BLUE_C)], src[CoordsCellBlue::index<Level>(i, j, neighbor)], face_blue_stencil[neighbor]);
      }
    }
    --inner_rowsize;
  }
}

SPECIALIZE(void, saveOperator_tmpl, saveOperator)

}// namespace P1BubbleFace
}// namespace hhg
