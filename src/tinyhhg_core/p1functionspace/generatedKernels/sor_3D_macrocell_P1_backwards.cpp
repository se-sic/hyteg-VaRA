
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "sor_3D_macrocell_P1_backwards.hpp"

namespace hyteg {
namespace vertexdof {
namespace macrocell {
namespace generated {

static void sor_3D_macrocell_P1_backwards_level_any(double * RESTRICT _data_p1CellDst, double const * RESTRICT const _data_p1CellRhs, int32_t level, std::map< hyteg::indexing::IndexIncrement, double > p1CellStencil, double relax)
{
   const double xi_19 = 1.0;
   const double xi_20 = -relax;
   const double xi_1 = p1CellStencil[{ 0, 0, 0 }];
   const double xi_17 = 1 / (xi_1);
   const double xi_2 = p1CellStencil[{ -1, 0, 0 }];
   const double xi_3 = p1CellStencil[{ -1, 0, 1 }];
   const double xi_4 = p1CellStencil[{ -1, 1, -1 }];
   const double xi_5 = p1CellStencil[{ -1, 1, 0 }];
   const double xi_6 = p1CellStencil[{ 0, -1, 0 }];
   const double xi_7 = p1CellStencil[{ 0, -1, 1 }];
   const double xi_8 = p1CellStencil[{ 0, 0, -1 }];
   const double xi_9 = p1CellStencil[{ 0, 0, 1 }];
   const double xi_10 = p1CellStencil[{ 0, 1, -1 }];
   const double xi_11 = p1CellStencil[{ 0, 1, 0 }];
   const double xi_12 = p1CellStencil[{ 1, -1, 0 }];
   const double xi_13 = p1CellStencil[{ 1, -1, 1 }];
   const double xi_14 = p1CellStencil[{ 1, 0, -1 }];
   const double xi_15 = p1CellStencil[{ 1, 0, 0 }];
   for (int ctr_3 = (1 << (level)) - 1; ctr_3 >= 1; ctr_3 += -1)
   {
      for (int ctr_2 = -ctr_3 + (1 << (level)) - 1; ctr_2 >= 1; ctr_2 += -1)
      {
         // cell (inner)
         for (int ctr_1 = -ctr_2 - ctr_3 + (1 << (level)) - 1; ctr_1 >= 1; ctr_1 += -1)
         {
            const double xi_35 = _data_p1CellRhs[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_27 = -xi_2*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_28 = -xi_3*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - 1];
            const double xi_29 = -xi_4*_data_p1CellDst[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) - 1];
            const double xi_30 = -xi_5*_data_p1CellDst[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) - 1];
            const double xi_31 = -xi_6*_data_p1CellDst[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_32 = -xi_7*_data_p1CellDst[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_33 = -xi_8*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_34 = -xi_9*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6))];
            const double xi_21 = -xi_10*_data_p1CellDst[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 3) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6))];
            const double xi_22 = -xi_11*_data_p1CellDst[ctr_1 + (ctr_2 + 1)*(-ctr_3 + (1 << (level)) + 2) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
            const double xi_23 = -xi_12*_data_p1CellDst[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            const double xi_24 = -xi_13*_data_p1CellDst[ctr_1 + (ctr_2 - 1)*(-ctr_3 + (1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) - (((-ctr_3 + (1 << (level)))*(-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)) / (6)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) + 1];
            const double xi_25 = -xi_14*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 3) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)*(-ctr_3 + (1 << (level)) + 4)) / (6)) + 1];
            const double xi_26 = -xi_15*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6)) + 1];
            _data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))] = relax*xi_17*(xi_21 + xi_22 + xi_23 + xi_24 + xi_25 + xi_26 + xi_27 + xi_28 + xi_29 + xi_30 + xi_31 + xi_32 + xi_33 + xi_34 + xi_35) + (xi_19 + xi_20)*_data_p1CellDst[ctr_1 + ctr_2*(-ctr_3 + (1 << (level)) + 2) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*((1 << (level)) + 2)*((1 << (level)) + 3)) / (6)) - (((-ctr_3 + (1 << (level)) + 1)*(-ctr_3 + (1 << (level)) + 2)*(-ctr_3 + (1 << (level)) + 3)) / (6))];
         }
      }
   }
}


void sor_3D_macrocell_P1_backwards(double * RESTRICT _data_p1CellDst, double const * RESTRICT const _data_p1CellRhs, int32_t level, std::map< hyteg::indexing::IndexIncrement, double > p1CellStencil, double relax)
{
    switch( level )
    {

    default:
        sor_3D_macrocell_P1_backwards_level_any(_data_p1CellDst, _data_p1CellRhs, level, p1CellStencil, relax);
        break;
    }
}
    

} // namespace generated
} // namespace macrocell
} // namespace vertexdof
} // namespace hyteg