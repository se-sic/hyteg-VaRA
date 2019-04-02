
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#include "GeneratedKernelsEdgeToEdgeMacroFace2D.hpp"

namespace hhg {
namespace edgedof {
namespace macroface {
namespace generated {

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_2(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 3; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 3; ctr_1 < 4; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 3; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 5];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 3; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 5];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 5];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 3; ctr_1 < -ctr_2 + 4; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 5];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 3; ctr_2 < 4; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 5];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + ((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 5*ctr_2 + 2*((20) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4];
         _data_edgeFaceDst[ctr_1 + 5*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_3(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 7; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 7; ctr_1 < 8; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 7; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 9];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 7; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 9];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 9];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 7; ctr_1 < -ctr_2 + 8; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 9];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 7; ctr_2 < 8; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 9];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + ((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 9*ctr_2 + 2*((72) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8];
         _data_edgeFaceDst[ctr_1 + 9*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_4(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 15; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 15; ctr_1 < 16; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 15; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 17];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 15; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 17];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 17];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 15; ctr_1 < -ctr_2 + 16; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 17];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 15; ctr_2 < 16; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 17];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + ((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 17*ctr_2 + 2*((272) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16];
         _data_edgeFaceDst[ctr_1 + 17*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_5(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 31; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 32];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 31; ctr_1 < 32; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 32];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 31; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 33];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 32];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 31; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 33];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 32];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 33];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 32];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 31; ctr_1 < -ctr_2 + 32; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 33];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 32];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 32];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 31; ctr_2 < 32; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 33];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + ((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 33*ctr_2 + 2*((1056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 32];
         _data_edgeFaceDst[ctr_1 + 33*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_6(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 63; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 64];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 63; ctr_1 < 64; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 64];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 63; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 65];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 64];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 63; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 65];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 64];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 65];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 64];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 63; ctr_1 < -ctr_2 + 64; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 65];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 64];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 64];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 63; ctr_2 < 64; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 65];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + ((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 65*ctr_2 + 2*((4160) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 64];
         _data_edgeFaceDst[ctr_1 + 65*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_7(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 127; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 128];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 127; ctr_1 < 128; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 128];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 127; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 129];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 128];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 127; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 129];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 128];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 129];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 128];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 127; ctr_1 < -ctr_2 + 128; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 129];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 128];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 128];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 127; ctr_2 < 128; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 129];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + ((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 129*ctr_2 + 2*((16512) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 128];
         _data_edgeFaceDst[ctr_1 + 129*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_8(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 255; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 256];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 255; ctr_1 < 256; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 256];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 255; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 257];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 256];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 255; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 257];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 256];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 257];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 256];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 255; ctr_1 < -ctr_2 + 256; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 257];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 256];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 256];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 255; ctr_2 < 256; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 257];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + ((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 257*ctr_2 + 2*((65792) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 256];
         _data_edgeFaceDst[ctr_1 + 257*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_9(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 511; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 512];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 511; ctr_1 < 512; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 512];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 511; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 513];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 512];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 511; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 513];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 512];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 513];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 512];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 511; ctr_1 < -ctr_2 + 512; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 513];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 512];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 512];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 511; ctr_2 < 512; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 513];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + ((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 513*ctr_2 + 2*((262656) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 512];
         _data_edgeFaceDst[ctr_1 + 513*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_10(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 1023; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1024];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 1023; ctr_1 < 1024; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1024];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 1023; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1024];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 1023; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1024];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1025];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1024];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 1023; ctr_1 < -ctr_2 + 1024; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1024];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 1024];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 1023; ctr_2 < 1024; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1025];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + ((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 1025*ctr_2 + 2*((1049600) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 1024];
         _data_edgeFaceDst[ctr_1 + 1025*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_11(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 2047; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2048];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 2047; ctr_1 < 2048; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2048];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 2047; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2048];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 2047; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2048];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2049];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2048];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 2047; ctr_1 < -ctr_2 + 2048; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2048];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 2048];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 2047; ctr_2 < 2048; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2049];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + ((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 2049*ctr_2 + 2*((4196352) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 2048];
         _data_edgeFaceDst[ctr_1 + 2049*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_12(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 4095; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4096];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 4095; ctr_1 < 4096; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4096];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 4095; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4096];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 4095; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4096];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4097];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4096];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 4095; ctr_1 < -ctr_2 + 4096; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4096];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 4096];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 4095; ctr_2 < 4096; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4097];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + ((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 4097*ctr_2 + 2*((16781312) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 4096];
         _data_edgeFaceDst[ctr_1 + 4097*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_13(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 8191; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8192];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 8191; ctr_1 < 8192; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8192];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 8191; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8192];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 8191; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8192];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8193];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8192];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 8191; ctr_1 < -ctr_2 + 8192; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8192];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 8192];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 8191; ctr_2 < 8192; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8193];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + ((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 8193*ctr_2 + 2*((67117056) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 8192];
         _data_edgeFaceDst[ctr_1 + 8193*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_14(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < 16383; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16384];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = 16383; ctr_1 < 16384; ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16384];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < 16383; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16384];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + 16383; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16384];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16385];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16384];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + 16383; ctr_1 < -ctr_2 + 16384; ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16384];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) + 16384];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = 16383; ctr_2 < 16384; ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16385];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + ((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + 16385*ctr_2 + 2*((268451840) / (2)) - ((ctr_2*(ctr_2 - 1)) / (2)) - 16384];
         _data_edgeFaceDst[ctr_1 + 16385*ctr_2 - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}

static void apply_2D_macroface_edgedof_to_edgedof_replace_level_any(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil, int64_t level)
{
   const double xi_33 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_34 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_35 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_36 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_37 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_75 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_76 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_77 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_78 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_79 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_80 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_81 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_82 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_83 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_84 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_46 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_47 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_48 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_49 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_50 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_121 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_122 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_123 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_124 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_125 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_126 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_127 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_128 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_129 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_130 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_0 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_1 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_2 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_3 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_4 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_5 = _data_edgeToDiagonalEdgeFaceStencil[1];
   const double xi_6 = _data_edgeToDiagonalEdgeFaceStencil[0];
   const double xi_7 = _data_edgeToDiagonalEdgeFaceStencil[4];
   const double xi_8 = _data_edgeToDiagonalEdgeFaceStencil[3];
   const double xi_9 = _data_edgeToDiagonalEdgeFaceStencil[2];
   const double xi_10 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_11 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_12 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_13 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_14 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_98 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_99 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_100 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_101 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_102 = _data_edgeToHorizontalEdgeFaceStencil[2];
   const double xi_103 = _data_edgeToVerticalEdgeFaceStencil[4];
   const double xi_104 = _data_edgeToVerticalEdgeFaceStencil[3];
   const double xi_105 = _data_edgeToVerticalEdgeFaceStencil[1];
   const double xi_106 = _data_edgeToVerticalEdgeFaceStencil[2];
   const double xi_107 = _data_edgeToVerticalEdgeFaceStencil[0];
   const double xi_59 = _data_edgeToHorizontalEdgeFaceStencil[1];
   const double xi_60 = _data_edgeToHorizontalEdgeFaceStencil[0];
   const double xi_61 = _data_edgeToHorizontalEdgeFaceStencil[3];
   const double xi_62 = _data_edgeToHorizontalEdgeFaceStencil[4];
   const double xi_63 = _data_edgeToHorizontalEdgeFaceStencil[2];
   for (int ctr_2 = 0; ctr_2 < 1; ctr_2 += 1)
   {
      // bottom left vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_40 = xi_33*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_41 = xi_34*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_42 = xi_35*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_43 = xi_36*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))];
         const double xi_44 = xi_37*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_40 + xi_41 + xi_42 + xi_43 + xi_44;
      }
      // bottom edge
      for (int ctr_1 = 1; ctr_1 < (1 << (level)) - 1; ctr_1 += 1)
      {
         const double xi_87 = xi_75*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_88 = xi_76*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_89 = xi_77*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_90 = xi_78*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))];
         const double xi_91 = xi_79*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         const double xi_92 = xi_80*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2)) - 1];
         const double xi_93 = xi_81*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1];
         const double xi_94 = xi_82*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_95 = xi_83*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_96 = xi_84*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_87 + xi_88 + xi_89 + xi_90 + xi_91;
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_92 + xi_93 + xi_94 + xi_95 + xi_96;
      }
      // bottom right vertex
      for (int ctr_1 = (1 << (level)) - 1; ctr_1 < (1 << (level)); ctr_1 += 1)
      {
         const double xi_53 = xi_46*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2)) - 1];
         const double xi_54 = xi_47*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1];
         const double xi_55 = xi_48*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_56 = xi_49*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_57 = xi_50*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_53 + xi_54 + xi_55 + xi_56 + xi_57;
      }
   }
   for (int ctr_2 = 1; ctr_2 < (1 << (level)) - 1; ctr_2 += 1)
   {
      // left edge
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_133 = xi_121*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_134 = xi_122*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_135 = xi_123*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_136 = xi_124*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_137 = xi_125*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         const double xi_138 = xi_126*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_139 = xi_127*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_140 = xi_128*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_141 = xi_129*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))];
         const double xi_142 = xi_130*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_133 + xi_134 + xi_135 + xi_136 + xi_137;
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_138 + xi_139 + xi_140 + xi_141 + xi_142;
      }
      // inner triangle
      for (int ctr_1 = 1; ctr_1 < -ctr_2 + (1 << (level)) - 1; ctr_1 += 1)
      {
         const double xi_17 = xi_0*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_18 = xi_1*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_19 = xi_2*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_20 = xi_3*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_21 = xi_4*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         const double xi_22 = xi_5*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_23 = xi_6*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_24 = xi_7*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_25 = xi_8*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2))];
         const double xi_26 = xi_9*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         const double xi_27 = xi_10*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2)) - 1];
         const double xi_28 = xi_11*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1];
         const double xi_29 = xi_12*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_30 = xi_13*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_31 = xi_14*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_17 + xi_18 + xi_19 + xi_20 + xi_21;
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_22 + xi_23 + xi_24 + xi_25 + xi_26;
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_27 + xi_28 + xi_29 + xi_30 + xi_31;
      }
      // diagonal edge
      for (int ctr_1 = -ctr_2 + (1 << (level)) - 1; ctr_1 < -ctr_2 + (1 << (level)); ctr_1 += 1)
      {
         const double xi_113 = xi_98*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_114 = xi_99*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_110 = xi_100*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_111 = xi_101*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_112 = xi_102*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         const double xi_115 = xi_103*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2)) - 1];
         const double xi_116 = xi_104*_data_edgeFaceSrc[ctr_1 + (ctr_2 + 1)*((1 << (level)) + 1) - (((ctr_2 + 1)*(ctr_2 + 2)) / (2)) - 1];
         const double xi_117 = xi_105*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_118 = xi_106*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_119 = xi_107*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_110 + xi_111 + xi_112 + xi_113 + xi_114;
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))] = xi_115 + xi_116 + xi_117 + xi_118 + xi_119;
      }
   }
   for (int ctr_2 = (1 << (level)) - 1; ctr_2 < (1 << (level)); ctr_2 += 1)
   {
      // top vertex
      for (int ctr_1 = 0; ctr_1 < 1; ctr_1 += 1)
      {
         const double xi_66 = xi_59*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_67 = xi_60*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))];
         const double xi_68 = xi_61*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + ((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_69 = xi_62*_data_edgeFaceSrc[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2))];
         const double xi_70 = xi_63*_data_edgeFaceSrc[ctr_1 + (ctr_2 - 1)*((1 << (level)) + 1) - ((ctr_2*(ctr_2 - 1)) / (2)) + 2*((((1 << (level)) + 1)*(1 << (level))) / (2)) + 1];
         _data_edgeFaceDst[ctr_1 + ctr_2*((1 << (level)) + 1) - ((ctr_2*(ctr_2 + 1)) / (2))] = xi_66 + xi_67 + xi_68 + xi_69 + xi_70;
      }
   }
   {
      
   }
}


void apply_2D_macroface_edgedof_to_edgedof_replace(double * _data_edgeFaceDst, double * _data_edgeFaceSrc, double * const _data_edgeToDiagonalEdgeFaceStencil, double * const _data_edgeToHorizontalEdgeFaceStencil, double * const _data_edgeToVerticalEdgeFaceStencil, int64_t level)
{
    switch( level )
    {
    case 2:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_2(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 3:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_3(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 4:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_4(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 5:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_5(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 6:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_6(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 7:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_7(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 8:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_8(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 9:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_9(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 10:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_10(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 11:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_11(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 12:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_12(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 13:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_13(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    case 14:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_14(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil);
        break;
    default:
        apply_2D_macroface_edgedof_to_edgedof_replace_level_any(_data_edgeFaceDst, _data_edgeFaceSrc, _data_edgeToDiagonalEdgeFaceStencil, _data_edgeToHorizontalEdgeFaceStencil, _data_edgeToVerticalEdgeFaceStencil, level);
        break;
    }
}
    

} // namespace generated
} // namespace macroface
} // namespace edgedof
} // namespace hhg