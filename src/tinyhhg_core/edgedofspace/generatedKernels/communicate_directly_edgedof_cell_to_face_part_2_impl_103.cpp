
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "communicate_directly_edgedof_cell_to_face_part_2_impl_103.hpp"

namespace hhg {
namespace edgedof {
namespace comm {
namespace generated {

static void communicate_directly_edgedof_cell_to_face_part_2_impl_103_level_any(double const * RESTRICT const _data_edge_cell_src_XY, double const * RESTRICT const _data_edge_cell_src_Y, double const * RESTRICT const _data_edge_cell_src_YZ, double * RESTRICT _data_edge_face_dst_gl0_XZ, double * RESTRICT _data_edge_face_dst_gl0_YZ, double * RESTRICT _data_edge_face_dst_gl0_Z, int32_t level)
{
   {
      for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
      {
         // bottom left vertex
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
         // bottom edge
         for (int ctr_1 = 1; ctr_1 < (1 << (level)) - 1; ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
         // bottom right vertex
         for (int ctr_1 = (1 << (level)) - 1; ctr_1 < (1 << (level)); ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
      }
      for (int ctr_2 = 1; ctr_2 < (1 << (level)) - 1; ctr_2 += 1)
      {
         // left edge
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
         // inner triangle
         for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)) - 1; ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
         // diagonal edge
         for (int ctr_1 = -ctr_2 + (1 << (level)) - 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
      }
      for (int ctr_2 = (1 << (level)) - 1; ctr_2 < (1 << (level)); ctr_2 += 1)
      {
         // top vertex
         for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
         {
            _data_edge_face_dst_gl0_Z[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_XY[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_XZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_Y[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
            _data_edge_face_dst_gl0_YZ[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = _data_edge_cell_src_YZ[-ctr_1 - ctr_2 - ((0) / (2)) - (((-ctr_2 + (1 << (level)))*(-ctr_2 + (1 << (level)) + 1)*(-ctr_2 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*(1 << (level))) / (6)) + (1 << (level)) - 1];
         }
      }
   }
}


void communicate_directly_edgedof_cell_to_face_part_2_impl_103(double const * RESTRICT const _data_edge_cell_src_XY, double const * RESTRICT const _data_edge_cell_src_Y, double const * RESTRICT const _data_edge_cell_src_YZ, double * RESTRICT _data_edge_face_dst_gl0_XZ, double * RESTRICT _data_edge_face_dst_gl0_YZ, double * RESTRICT _data_edge_face_dst_gl0_Z, int32_t level)
{
    switch( level )
    {

    default:
        communicate_directly_edgedof_cell_to_face_part_2_impl_103_level_any(_data_edge_cell_src_XY, _data_edge_cell_src_Y, _data_edge_cell_src_YZ, _data_edge_face_dst_gl0_XZ, _data_edge_face_dst_gl0_YZ, _data_edge_face_dst_gl0_Z, level);
        break;
    }
}
    

} // namespace generated
} // namespace comm
} // namespace edgedof
} // namespace hhg