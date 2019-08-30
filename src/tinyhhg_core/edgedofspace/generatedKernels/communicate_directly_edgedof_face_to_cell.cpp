
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "communicate_directly_edgedof_face_to_cell.hpp"

namespace hyteg {
namespace edgedof {
namespace comm {
namespace generated {

void communicate_directly_edgedof_face_to_cell(double * RESTRICT _data_edge_cell_dst_X, double * RESTRICT _data_edge_cell_dst_XY, double * RESTRICT _data_edge_cell_dst_XZ, double * RESTRICT _data_edge_cell_dst_Y, double * RESTRICT _data_edge_cell_dst_YZ, double * RESTRICT _data_edge_cell_dst_Z, double const * RESTRICT const _data_edge_face_src_X, double const * RESTRICT const _data_edge_face_src_XY, double const * RESTRICT const _data_edge_face_src_Y, int32_t level, int64_t neighbor_cell_local_vertex_id_0, int64_t neighbor_cell_local_vertex_id_1, int64_t neighbor_cell_local_vertex_id_2)
{
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((1) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_012(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((1) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_013(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((1) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_021(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_023(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((1) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_031(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_032(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((1) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_102(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((1) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_103(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((1) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_120(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_123(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((1) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_130(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_0)) && ((2) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_132(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((1) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_201(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_203(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((1) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_210(_data_edge_cell_dst_X, _data_edge_cell_dst_XY, _data_edge_cell_dst_Y, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_2)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_213(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_230(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_0)) && ((3) == (neighbor_cell_local_vertex_id_1)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_231(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((1) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_301(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_302(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((1) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_310(_data_edge_cell_dst_X, _data_edge_cell_dst_XZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_1)) && ((2) == (neighbor_cell_local_vertex_id_2)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_312(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((0) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_320(_data_edge_cell_dst_Y, _data_edge_cell_dst_YZ, _data_edge_cell_dst_Z, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
   if (((1) == (neighbor_cell_local_vertex_id_2)) && ((2) == (neighbor_cell_local_vertex_id_1)) && ((3) == (neighbor_cell_local_vertex_id_0)))
   {
      
      communicate_directly_edgedof_face_to_cell_impl_321(_data_edge_cell_dst_XY, _data_edge_cell_dst_XZ, _data_edge_cell_dst_YZ, _data_edge_face_src_X, _data_edge_face_src_XY, _data_edge_face_src_Y, level);
      
      return;
   } 
}


} // namespace generated
} // namespace comm
} // namespace edgedof
} // namespace hyteg