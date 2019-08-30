
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "add_2D_macroface_vertexdof_2_rhsfunctions.hpp"

namespace hyteg {
namespace vertexdof {
namespace macroface {
namespace generated {

static void add_2D_macroface_vertexdof_2_rhs_functions_level_any(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1, int32_t level)
{
   for (int ctr_2 = 1; ctr_2 < (1 << (level)); ctr_2 += 1)
   {
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
      {
         const double xi_3 = c0*_data_p1FaceSrc0[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_4 = c1*_data_p1FaceSrc1[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_5 = _data_p1FaceDst[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_p1FaceDst[ctr_1 + ctr_2*((1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_3 + xi_4 + xi_5;
      }
   }
}


void add_2D_macroface_vertexdof_2_rhs_functions(double * RESTRICT _data_p1FaceDst, double * RESTRICT _data_p1FaceSrc0, double * RESTRICT _data_p1FaceSrc1, double c0, double c1, int32_t level)
{
    switch( level )
    {

    default:
        add_2D_macroface_vertexdof_2_rhs_functions_level_any(_data_p1FaceDst, _data_p1FaceSrc0, _data_p1FaceSrc1, c0, c1, level);
        break;
    }
}
    

} // namespace generated
} // namespace macroface
} // namespace vertexdof
} // namespace hyteg