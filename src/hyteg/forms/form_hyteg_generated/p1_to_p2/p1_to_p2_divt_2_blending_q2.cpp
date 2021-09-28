/*
 * Copyright (c) 2017-2021 Nils Kohl.
 *
 * This file is part of HyTeG
 * (see https://i10git.cs.fau.de/hyteg/hyteg).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * The entire file was generated with the HyTeG form generator.
 * 
 * Software:
 *
 * - quadpy version: 0.16.5
 *
 * Avoid modifying this file. If buggy, consider fixing the generator itself.
 */

#include "p1_to_p2_divt_2_blending_q2.hpp"

namespace hyteg {
namespace forms {

   void p1_to_p2_divt_2_blending_q2::integrateAll( const std::array< Point3D, 3 >& , Matrix< real_t, 6, 3 >&  ) const
   {
      
   }

   void p1_to_p2_divt_2_blending_q2::integrateRow0( const std::array< Point3D, 3 >& , Matrix< real_t, 1, 3 >&  ) const
   {
      
   }

   void p1_to_p2_divt_2_blending_q2::integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 4 >& elMat ) const
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_0_2 = coords[0][2];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_1_2 = coords[1][2];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t p_affine_2_2 = coords[2][2];
      real_t p_affine_3_0 = coords[3][0];
      real_t p_affine_3_1 = coords[3][1];
      real_t p_affine_3_2 = coords[3][2];
      real_t Blending_DF_Tetrahedron_0_0 = 0;
      real_t Blending_DF_Tetrahedron_0_1 = 0;
      real_t Blending_DF_Tetrahedron_0_2 = 0;
      real_t Blending_DF_Tetrahedron_0_3 = 0;
      real_t Blending_DF_Tetrahedron_0_4 = 0;
      real_t Blending_DF_Tetrahedron_0_5 = 0;
      real_t Blending_DF_Tetrahedron_0_6 = 0;
      real_t Blending_DF_Tetrahedron_0_7 = 0;
      real_t Blending_DF_Tetrahedron_0_8 = 0;
      real_t Blending_DF_Tetrahedron_1_0 = 0;
      real_t Blending_DF_Tetrahedron_1_1 = 0;
      real_t Blending_DF_Tetrahedron_1_2 = 0;
      real_t Blending_DF_Tetrahedron_1_3 = 0;
      real_t Blending_DF_Tetrahedron_1_4 = 0;
      real_t Blending_DF_Tetrahedron_1_5 = 0;
      real_t Blending_DF_Tetrahedron_1_6 = 0;
      real_t Blending_DF_Tetrahedron_1_7 = 0;
      real_t Blending_DF_Tetrahedron_1_8 = 0;
      real_t Blending_DF_Tetrahedron_2_0 = 0;
      real_t Blending_DF_Tetrahedron_2_1 = 0;
      real_t Blending_DF_Tetrahedron_2_2 = 0;
      real_t Blending_DF_Tetrahedron_2_3 = 0;
      real_t Blending_DF_Tetrahedron_2_4 = 0;
      real_t Blending_DF_Tetrahedron_2_5 = 0;
      real_t Blending_DF_Tetrahedron_2_6 = 0;
      real_t Blending_DF_Tetrahedron_2_7 = 0;
      real_t Blending_DF_Tetrahedron_2_8 = 0;
      real_t Blending_DF_Tetrahedron_3_0 = 0;
      real_t Blending_DF_Tetrahedron_3_1 = 0;
      real_t Blending_DF_Tetrahedron_3_2 = 0;
      real_t Blending_DF_Tetrahedron_3_3 = 0;
      real_t Blending_DF_Tetrahedron_3_4 = 0;
      real_t Blending_DF_Tetrahedron_3_5 = 0;
      real_t Blending_DF_Tetrahedron_3_6 = 0;
      real_t Blending_DF_Tetrahedron_3_7 = 0;
      real_t Blending_DF_Tetrahedron_3_8 = 0;
      Blending_DF_Tetrahedron( 0.13819660112501042*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.58541019662496829*p_affine_3_0, 0.13819660112501042*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.58541019662496829*p_affine_3_1, 0.13819660112501042*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.58541019662496829*p_affine_3_2, &Blending_DF_Tetrahedron_0_0, &Blending_DF_Tetrahedron_0_1, &Blending_DF_Tetrahedron_0_2, &Blending_DF_Tetrahedron_0_3, &Blending_DF_Tetrahedron_0_4, &Blending_DF_Tetrahedron_0_5, &Blending_DF_Tetrahedron_0_6, &Blending_DF_Tetrahedron_0_7, &Blending_DF_Tetrahedron_0_8 );
      Blending_DF_Tetrahedron( 0.13819660112501048*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.58541019662496829*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.13819660112501048*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.58541019662496829*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.13819660112501048*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.58541019662496829*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_1_0, &Blending_DF_Tetrahedron_1_1, &Blending_DF_Tetrahedron_1_2, &Blending_DF_Tetrahedron_1_3, &Blending_DF_Tetrahedron_1_4, &Blending_DF_Tetrahedron_1_5, &Blending_DF_Tetrahedron_1_6, &Blending_DF_Tetrahedron_1_7, &Blending_DF_Tetrahedron_1_8 );
      Blending_DF_Tetrahedron( 0.13819660112501053*p_affine_0_0 + 0.58541019662496829*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.13819660112501053*p_affine_0_1 + 0.58541019662496829*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.13819660112501053*p_affine_0_2 + 0.58541019662496829*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_2_0, &Blending_DF_Tetrahedron_2_1, &Blending_DF_Tetrahedron_2_2, &Blending_DF_Tetrahedron_2_3, &Blending_DF_Tetrahedron_2_4, &Blending_DF_Tetrahedron_2_5, &Blending_DF_Tetrahedron_2_6, &Blending_DF_Tetrahedron_2_7, &Blending_DF_Tetrahedron_2_8 );
      Blending_DF_Tetrahedron( 0.58541019662496807*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.58541019662496807*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.58541019662496807*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_3_0, &Blending_DF_Tetrahedron_3_1, &Blending_DF_Tetrahedron_3_2, &Blending_DF_Tetrahedron_3_3, &Blending_DF_Tetrahedron_3_4, &Blending_DF_Tetrahedron_3_5, &Blending_DF_Tetrahedron_3_6, &Blending_DF_Tetrahedron_3_7, &Blending_DF_Tetrahedron_3_8 );
      real_t tmp_0 = 0.13819660112501042;
      real_t tmp_1 = 0.55278640450004235;
      real_t tmp_2 = 0.55278640450004235;
      real_t tmp_3 = 2.3416407864998732;
      real_t tmp_4 = tmp_1 + tmp_2 + tmp_3 - 3.0;
      real_t tmp_5 = -p_affine_0_0;
      real_t tmp_6 = p_affine_1_0 + tmp_5;
      real_t tmp_7 = -p_affine_0_1;
      real_t tmp_8 = p_affine_2_1 + tmp_7;
      real_t tmp_9 = tmp_6*tmp_8;
      real_t tmp_10 = p_affine_2_0 + tmp_5;
      real_t tmp_11 = p_affine_1_1 + tmp_7;
      real_t tmp_12 = tmp_10*tmp_11;
      real_t tmp_13 = -tmp_12 + tmp_9;
      real_t tmp_14 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_4;
      real_t tmp_15 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_3;
      real_t tmp_16 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_5;
      real_t tmp_17 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_3;
      real_t tmp_18 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_5;
      real_t tmp_19 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_4;
      real_t tmp_20 = Blending_DF_Tetrahedron_0_6*tmp_16 - Blending_DF_Tetrahedron_0_6*tmp_19 + Blending_DF_Tetrahedron_0_7*tmp_17 - Blending_DF_Tetrahedron_0_7*tmp_18 + Blending_DF_Tetrahedron_0_8*tmp_14 - Blending_DF_Tetrahedron_0_8*tmp_15;
      real_t tmp_21 = -p_affine_0_2;
      real_t tmp_22 = p_affine_3_2 + tmp_21;
      real_t tmp_23 = p_affine_3_1 + tmp_7;
      real_t tmp_24 = p_affine_1_2 + tmp_21;
      real_t tmp_25 = tmp_10*tmp_24;
      real_t tmp_26 = p_affine_3_0 + tmp_5;
      real_t tmp_27 = p_affine_2_2 + tmp_21;
      real_t tmp_28 = tmp_11*tmp_27;
      real_t tmp_29 = tmp_27*tmp_6;
      real_t tmp_30 = tmp_24*tmp_8;
      real_t tmp_31 = 1.0 / (-tmp_12*tmp_22 + tmp_22*tmp_9 + tmp_23*tmp_25 - tmp_23*tmp_29 + tmp_26*tmp_28 - tmp_26*tmp_30);
      real_t tmp_32 = tmp_31/tmp_20;
      real_t tmp_33 = tmp_32*(tmp_14 - tmp_15);
      real_t tmp_34 = tmp_25 - tmp_29;
      real_t tmp_35 = tmp_32*(tmp_17 - tmp_18);
      real_t tmp_36 = tmp_28 - tmp_30;
      real_t tmp_37 = tmp_32*(tmp_16 - tmp_19);
      real_t tmp_38 = tmp_13*tmp_33 + tmp_34*tmp_35 + tmp_36*tmp_37;
      real_t tmp_39 = tmp_11*tmp_26 - tmp_23*tmp_6;
      real_t tmp_40 = tmp_22*tmp_6 - tmp_24*tmp_26;
      real_t tmp_41 = -tmp_11*tmp_22 + tmp_23*tmp_24;
      real_t tmp_42 = tmp_33*tmp_39 + tmp_35*tmp_40 + tmp_37*tmp_41;
      real_t tmp_43 = tmp_10*tmp_23 - tmp_26*tmp_8;
      real_t tmp_44 = -tmp_10*tmp_22 + tmp_26*tmp_27;
      real_t tmp_45 = tmp_22*tmp_8 - tmp_23*tmp_27;
      real_t tmp_46 = tmp_33*tmp_43 + tmp_35*tmp_44 + tmp_37*tmp_45;
      real_t tmp_47 = p_affine_0_0*p_affine_1_1;
      real_t tmp_48 = p_affine_0_0*p_affine_1_2;
      real_t tmp_49 = p_affine_2_1*p_affine_3_2;
      real_t tmp_50 = p_affine_0_1*p_affine_1_0;
      real_t tmp_51 = p_affine_0_1*p_affine_1_2;
      real_t tmp_52 = p_affine_2_2*p_affine_3_0;
      real_t tmp_53 = p_affine_0_2*p_affine_1_0;
      real_t tmp_54 = p_affine_0_2*p_affine_1_1;
      real_t tmp_55 = p_affine_2_0*p_affine_3_1;
      real_t tmp_56 = p_affine_2_2*p_affine_3_1;
      real_t tmp_57 = p_affine_2_0*p_affine_3_2;
      real_t tmp_58 = p_affine_2_1*p_affine_3_0;
      real_t tmp_59 = std::abs(p_affine_0_0*tmp_49 - p_affine_0_0*tmp_56 + p_affine_0_1*tmp_52 - p_affine_0_1*tmp_57 + p_affine_0_2*tmp_55 - p_affine_0_2*tmp_58 - p_affine_1_0*tmp_49 + p_affine_1_0*tmp_56 - p_affine_1_1*tmp_52 + p_affine_1_1*tmp_57 - p_affine_1_2*tmp_55 + p_affine_1_2*tmp_58 + p_affine_2_0*tmp_51 - p_affine_2_0*tmp_54 - p_affine_2_1*tmp_48 + p_affine_2_1*tmp_53 + p_affine_2_2*tmp_47 - p_affine_2_2*tmp_50 - p_affine_3_0*tmp_51 + p_affine_3_0*tmp_54 + p_affine_3_1*tmp_48 - p_affine_3_1*tmp_53 - p_affine_3_2*tmp_47 + p_affine_3_2*tmp_50);
      real_t tmp_60 = 0.041666666666666657*tmp_59*std::abs(tmp_20);
      real_t tmp_61 = tmp_60*(-tmp_38*tmp_4 - tmp_4*tmp_42 - tmp_4*tmp_46);
      real_t tmp_62 = 0.13819660112501048;
      real_t tmp_63 = 0.55278640450004235;
      real_t tmp_64 = 2.3416407864998732;
      real_t tmp_65 = 0.55278640450004235;
      real_t tmp_66 = tmp_63 + tmp_64 + tmp_65 - 3.0;
      real_t tmp_67 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_4;
      real_t tmp_68 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_3;
      real_t tmp_69 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_5;
      real_t tmp_70 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_3;
      real_t tmp_71 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_5;
      real_t tmp_72 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_4;
      real_t tmp_73 = Blending_DF_Tetrahedron_1_6*tmp_69 - Blending_DF_Tetrahedron_1_6*tmp_72 + Blending_DF_Tetrahedron_1_7*tmp_70 - Blending_DF_Tetrahedron_1_7*tmp_71 + Blending_DF_Tetrahedron_1_8*tmp_67 - Blending_DF_Tetrahedron_1_8*tmp_68;
      real_t tmp_74 = tmp_31/tmp_73;
      real_t tmp_75 = tmp_74*(tmp_67 - tmp_68);
      real_t tmp_76 = tmp_74*(tmp_70 - tmp_71);
      real_t tmp_77 = tmp_74*(tmp_69 - tmp_72);
      real_t tmp_78 = tmp_13*tmp_75 + tmp_34*tmp_76 + tmp_36*tmp_77;
      real_t tmp_79 = tmp_39*tmp_75 + tmp_40*tmp_76 + tmp_41*tmp_77;
      real_t tmp_80 = tmp_43*tmp_75 + tmp_44*tmp_76 + tmp_45*tmp_77;
      real_t tmp_81 = 0.041666666666666657*tmp_59*std::abs(tmp_73);
      real_t tmp_82 = tmp_81*(-tmp_66*tmp_78 - tmp_66*tmp_79 - tmp_66*tmp_80);
      real_t tmp_83 = 0.13819660112501053;
      real_t tmp_84 = 2.3416407864998732;
      real_t tmp_85 = 0.55278640450004235;
      real_t tmp_86 = 0.55278640450004235;
      real_t tmp_87 = tmp_84 + tmp_85 + tmp_86 - 3.0;
      real_t tmp_88 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_4;
      real_t tmp_89 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_3;
      real_t tmp_90 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_5;
      real_t tmp_91 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_3;
      real_t tmp_92 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_5;
      real_t tmp_93 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_4;
      real_t tmp_94 = Blending_DF_Tetrahedron_2_6*tmp_90 - Blending_DF_Tetrahedron_2_6*tmp_93 + Blending_DF_Tetrahedron_2_7*tmp_91 - Blending_DF_Tetrahedron_2_7*tmp_92 + Blending_DF_Tetrahedron_2_8*tmp_88 - Blending_DF_Tetrahedron_2_8*tmp_89;
      real_t tmp_95 = tmp_31/tmp_94;
      real_t tmp_96 = tmp_95*(tmp_88 - tmp_89);
      real_t tmp_97 = tmp_95*(tmp_91 - tmp_92);
      real_t tmp_98 = tmp_95*(tmp_90 - tmp_93);
      real_t tmp_99 = tmp_13*tmp_96 + tmp_34*tmp_97 + tmp_36*tmp_98;
      real_t tmp_100 = tmp_39*tmp_96 + tmp_40*tmp_97 + tmp_41*tmp_98;
      real_t tmp_101 = tmp_43*tmp_96 + tmp_44*tmp_97 + tmp_45*tmp_98;
      real_t tmp_102 = 0.041666666666666657*tmp_59*std::abs(tmp_94);
      real_t tmp_103 = tmp_102*(-tmp_100*tmp_87 - tmp_101*tmp_87 - tmp_87*tmp_99);
      real_t tmp_104 = 0.58541019662496807;
      real_t tmp_105 = 0.55278640450004235;
      real_t tmp_106 = 0.55278640450004235;
      real_t tmp_107 = 0.55278640450004235;
      real_t tmp_108 = tmp_105 + tmp_106 + tmp_107 - 3.0;
      real_t tmp_109 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_4;
      real_t tmp_110 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_3;
      real_t tmp_111 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_5;
      real_t tmp_112 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_3;
      real_t tmp_113 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_5;
      real_t tmp_114 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_4;
      real_t tmp_115 = Blending_DF_Tetrahedron_3_6*tmp_111 - Blending_DF_Tetrahedron_3_6*tmp_114 + Blending_DF_Tetrahedron_3_7*tmp_112 - Blending_DF_Tetrahedron_3_7*tmp_113 + Blending_DF_Tetrahedron_3_8*tmp_109 - Blending_DF_Tetrahedron_3_8*tmp_110;
      real_t tmp_116 = tmp_31/tmp_115;
      real_t tmp_117 = tmp_116*(tmp_109 - tmp_110);
      real_t tmp_118 = tmp_116*(tmp_112 - tmp_113);
      real_t tmp_119 = tmp_116*(tmp_111 - tmp_114);
      real_t tmp_120 = tmp_117*tmp_13 + tmp_118*tmp_34 + tmp_119*tmp_36;
      real_t tmp_121 = tmp_117*tmp_39 + tmp_118*tmp_40 + tmp_119*tmp_41;
      real_t tmp_122 = tmp_117*tmp_43 + tmp_118*tmp_44 + tmp_119*tmp_45;
      real_t tmp_123 = 0.041666666666666657*tmp_59*std::abs(tmp_115);
      real_t tmp_124 = tmp_123*(-tmp_108*tmp_120 - tmp_108*tmp_121 - tmp_108*tmp_122);
      real_t tmp_125 = tmp_0*tmp_60;
      real_t tmp_126 = tmp_46*(tmp_1 - 1.0);
      real_t tmp_127 = tmp_62*tmp_81;
      real_t tmp_128 = tmp_80*(tmp_63 - 1.0);
      real_t tmp_129 = tmp_102*tmp_83;
      real_t tmp_130 = tmp_101*(tmp_84 - 1.0);
      real_t tmp_131 = tmp_104*tmp_123;
      real_t tmp_132 = tmp_122*(tmp_105 - 1.0);
      real_t tmp_133 = tmp_126*tmp_60;
      real_t tmp_134 = tmp_128*tmp_81;
      real_t tmp_135 = tmp_102*tmp_130;
      real_t tmp_136 = tmp_123*tmp_132;
      real_t tmp_137 = tmp_42*(tmp_2 - 1.0);
      real_t tmp_138 = tmp_79*(tmp_64 - 1.0);
      real_t tmp_139 = tmp_100*(tmp_85 - 1.0);
      real_t tmp_140 = tmp_121*(tmp_106 - 1.0);
      real_t tmp_141 = tmp_137*tmp_60;
      real_t tmp_142 = tmp_138*tmp_81;
      real_t tmp_143 = tmp_102*tmp_139;
      real_t tmp_144 = tmp_123*tmp_140;
      real_t tmp_145 = tmp_38*(tmp_3 - 1.0);
      real_t tmp_146 = tmp_78*(tmp_65 - 1.0);
      real_t tmp_147 = tmp_99*(tmp_86 - 1.0);
      real_t tmp_148 = tmp_120*(tmp_107 - 1.0);
      real_t tmp_149 = tmp_145*tmp_60;
      real_t tmp_150 = tmp_146*tmp_81;
      real_t tmp_151 = tmp_102*tmp_147;
      real_t tmp_152 = tmp_123*tmp_148;
      real_t tmp_153 = tmp_2*tmp_38;
      real_t tmp_154 = tmp_3*tmp_42;
      real_t tmp_155 = tmp_60*(-tmp_153 - tmp_154);
      real_t tmp_156 = tmp_64*tmp_78;
      real_t tmp_157 = tmp_65*tmp_79;
      real_t tmp_158 = tmp_81*(-tmp_156 - tmp_157);
      real_t tmp_159 = tmp_85*tmp_99;
      real_t tmp_160 = tmp_100*tmp_86;
      real_t tmp_161 = tmp_102*(-tmp_159 - tmp_160);
      real_t tmp_162 = tmp_106*tmp_120;
      real_t tmp_163 = tmp_107*tmp_121;
      real_t tmp_164 = tmp_123*(-tmp_162 - tmp_163);
      real_t tmp_165 = tmp_1*tmp_38;
      real_t tmp_166 = tmp_3*tmp_46;
      real_t tmp_167 = tmp_60*(-tmp_165 - tmp_166);
      real_t tmp_168 = tmp_63*tmp_78;
      real_t tmp_169 = tmp_65*tmp_80;
      real_t tmp_170 = tmp_81*(-tmp_168 - tmp_169);
      real_t tmp_171 = tmp_84*tmp_99;
      real_t tmp_172 = tmp_101*tmp_86;
      real_t tmp_173 = tmp_102*(-tmp_171 - tmp_172);
      real_t tmp_174 = tmp_105*tmp_120;
      real_t tmp_175 = tmp_107*tmp_122;
      real_t tmp_176 = tmp_123*(-tmp_174 - tmp_175);
      real_t tmp_177 = tmp_1*tmp_42;
      real_t tmp_178 = tmp_2*tmp_46;
      real_t tmp_179 = tmp_60*(-tmp_177 - tmp_178);
      real_t tmp_180 = tmp_63*tmp_79;
      real_t tmp_181 = tmp_64*tmp_80;
      real_t tmp_182 = tmp_81*(-tmp_180 - tmp_181);
      real_t tmp_183 = tmp_100*tmp_84;
      real_t tmp_184 = tmp_101*tmp_85;
      real_t tmp_185 = tmp_102*(-tmp_183 - tmp_184);
      real_t tmp_186 = tmp_105*tmp_121;
      real_t tmp_187 = tmp_106*tmp_122;
      real_t tmp_188 = tmp_123*(-tmp_186 - tmp_187);
      real_t tmp_189 = -tmp_2;
      real_t tmp_190 = 4.0 - tmp_1;
      real_t tmp_191 = tmp_60*(tmp_154 + tmp_166 - tmp_38*(tmp_189 + tmp_190 - 4.6832815729997463));
      real_t tmp_192 = -tmp_64;
      real_t tmp_193 = 4.0 - tmp_63;
      real_t tmp_194 = tmp_81*(tmp_157 + tmp_169 - tmp_78*(tmp_192 + tmp_193 - 1.1055728090000847));
      real_t tmp_195 = -tmp_85;
      real_t tmp_196 = 4.0 - tmp_84;
      real_t tmp_197 = tmp_102*(tmp_160 + tmp_172 - tmp_99*(tmp_195 + tmp_196 - 1.1055728090000847));
      real_t tmp_198 = -tmp_106;
      real_t tmp_199 = 4.0 - tmp_105;
      real_t tmp_200 = tmp_123*(-tmp_120*(tmp_198 + tmp_199 - 1.1055728090000847) + tmp_163 + tmp_175);
      real_t tmp_201 = -tmp_3;
      real_t tmp_202 = tmp_60*(tmp_153 + tmp_178 - tmp_42*(tmp_190 + tmp_201 - 1.1055728090000847));
      real_t tmp_203 = -tmp_65;
      real_t tmp_204 = tmp_81*(tmp_156 + tmp_181 - tmp_79*(tmp_193 + tmp_203 - 4.6832815729997463));
      real_t tmp_205 = -tmp_86;
      real_t tmp_206 = tmp_102*(-tmp_100*(tmp_196 + tmp_205 - 1.1055728090000847) + tmp_159 + tmp_184);
      real_t tmp_207 = -tmp_107;
      real_t tmp_208 = tmp_123*(-tmp_121*(tmp_199 + tmp_207 - 1.1055728090000847) + tmp_162 + tmp_187);
      real_t tmp_209 = tmp_60*(tmp_165 + tmp_177 - tmp_46*(tmp_189 + tmp_201 + 2.8944271909999153));
      real_t tmp_210 = tmp_81*(tmp_168 + tmp_180 - tmp_80*(tmp_192 + tmp_203 + 2.8944271909999153));
      real_t tmp_211 = tmp_102*(-tmp_101*(tmp_195 + tmp_205 - 0.68328157299974634) + tmp_171 + tmp_183);
      real_t tmp_212 = tmp_123*(-tmp_122*(tmp_198 + tmp_207 + 2.8944271909999153) + tmp_174 + tmp_186);
      real_t a_0_0 = tmp_0*tmp_61 + tmp_103*tmp_83 + tmp_104*tmp_124 + tmp_62*tmp_82;
      real_t a_0_1 = 0.58541019662496829*tmp_103 + 0.13819660112501059*tmp_124 + 0.13819660112501059*tmp_61 + 0.13819660112501059*tmp_82;
      real_t a_0_2 = 0.13819660112501059*tmp_103 + 0.13819660112501059*tmp_124 + 0.13819660112501059*tmp_61 + 0.58541019662496829*tmp_82;
      real_t a_0_3 = 0.13819660112501059*tmp_103 + 0.13819660112501059*tmp_124 + 0.58541019662496829*tmp_61 + 0.13819660112501059*tmp_82;
      real_t a_1_0 = -tmp_125*tmp_126 - tmp_127*tmp_128 - tmp_129*tmp_130 - tmp_131*tmp_132;
      real_t a_1_1 = -0.13819660112501059*tmp_133 - 0.13819660112501059*tmp_134 - 0.58541019662496829*tmp_135 - 0.13819660112501059*tmp_136;
      real_t a_1_2 = -0.13819660112501059*tmp_133 - 0.58541019662496829*tmp_134 - 0.13819660112501059*tmp_135 - 0.13819660112501059*tmp_136;
      real_t a_1_3 = -0.58541019662496829*tmp_133 - 0.13819660112501059*tmp_134 - 0.13819660112501059*tmp_135 - 0.13819660112501059*tmp_136;
      real_t a_2_0 = -tmp_125*tmp_137 - tmp_127*tmp_138 - tmp_129*tmp_139 - tmp_131*tmp_140;
      real_t a_2_1 = -0.13819660112501059*tmp_141 - 0.13819660112501059*tmp_142 - 0.58541019662496829*tmp_143 - 0.13819660112501059*tmp_144;
      real_t a_2_2 = -0.13819660112501059*tmp_141 - 0.58541019662496829*tmp_142 - 0.13819660112501059*tmp_143 - 0.13819660112501059*tmp_144;
      real_t a_2_3 = -0.58541019662496829*tmp_141 - 0.13819660112501059*tmp_142 - 0.13819660112501059*tmp_143 - 0.13819660112501059*tmp_144;
      real_t a_3_0 = -tmp_125*tmp_145 - tmp_127*tmp_146 - tmp_129*tmp_147 - tmp_131*tmp_148;
      real_t a_3_1 = -0.13819660112501059*tmp_149 - 0.13819660112501059*tmp_150 - 0.58541019662496829*tmp_151 - 0.13819660112501059*tmp_152;
      real_t a_3_2 = -0.13819660112501059*tmp_149 - 0.58541019662496829*tmp_150 - 0.13819660112501059*tmp_151 - 0.13819660112501059*tmp_152;
      real_t a_3_3 = -0.58541019662496829*tmp_149 - 0.13819660112501059*tmp_150 - 0.13819660112501059*tmp_151 - 0.13819660112501059*tmp_152;
      real_t a_4_0 = tmp_0*tmp_155 + tmp_104*tmp_164 + tmp_158*tmp_62 + tmp_161*tmp_83;
      real_t a_4_1 = 0.13819660112501059*tmp_155 + 0.13819660112501059*tmp_158 + 0.58541019662496829*tmp_161 + 0.13819660112501059*tmp_164;
      real_t a_4_2 = 0.13819660112501059*tmp_155 + 0.58541019662496829*tmp_158 + 0.13819660112501059*tmp_161 + 0.13819660112501059*tmp_164;
      real_t a_4_3 = 0.58541019662496829*tmp_155 + 0.13819660112501059*tmp_158 + 0.13819660112501059*tmp_161 + 0.13819660112501059*tmp_164;
      real_t a_5_0 = tmp_0*tmp_167 + tmp_104*tmp_176 + tmp_170*tmp_62 + tmp_173*tmp_83;
      real_t a_5_1 = 0.13819660112501059*tmp_167 + 0.13819660112501059*tmp_170 + 0.58541019662496829*tmp_173 + 0.13819660112501059*tmp_176;
      real_t a_5_2 = 0.13819660112501059*tmp_167 + 0.58541019662496829*tmp_170 + 0.13819660112501059*tmp_173 + 0.13819660112501059*tmp_176;
      real_t a_5_3 = 0.58541019662496829*tmp_167 + 0.13819660112501059*tmp_170 + 0.13819660112501059*tmp_173 + 0.13819660112501059*tmp_176;
      real_t a_6_0 = tmp_0*tmp_179 + tmp_104*tmp_188 + tmp_182*tmp_62 + tmp_185*tmp_83;
      real_t a_6_1 = 0.13819660112501059*tmp_179 + 0.13819660112501059*tmp_182 + 0.58541019662496829*tmp_185 + 0.13819660112501059*tmp_188;
      real_t a_6_2 = 0.13819660112501059*tmp_179 + 0.58541019662496829*tmp_182 + 0.13819660112501059*tmp_185 + 0.13819660112501059*tmp_188;
      real_t a_6_3 = 0.58541019662496829*tmp_179 + 0.13819660112501059*tmp_182 + 0.13819660112501059*tmp_185 + 0.13819660112501059*tmp_188;
      real_t a_7_0 = tmp_0*tmp_191 + tmp_104*tmp_200 + tmp_194*tmp_62 + tmp_197*tmp_83;
      real_t a_7_1 = 0.13819660112501059*tmp_191 + 0.13819660112501059*tmp_194 + 0.58541019662496829*tmp_197 + 0.13819660112501059*tmp_200;
      real_t a_7_2 = 0.13819660112501059*tmp_191 + 0.58541019662496829*tmp_194 + 0.13819660112501059*tmp_197 + 0.13819660112501059*tmp_200;
      real_t a_7_3 = 0.58541019662496829*tmp_191 + 0.13819660112501059*tmp_194 + 0.13819660112501059*tmp_197 + 0.13819660112501059*tmp_200;
      real_t a_8_0 = tmp_0*tmp_202 + tmp_104*tmp_208 + tmp_204*tmp_62 + tmp_206*tmp_83;
      real_t a_8_1 = 0.13819660112501059*tmp_202 + 0.13819660112501059*tmp_204 + 0.58541019662496829*tmp_206 + 0.13819660112501059*tmp_208;
      real_t a_8_2 = 0.13819660112501059*tmp_202 + 0.58541019662496829*tmp_204 + 0.13819660112501059*tmp_206 + 0.13819660112501059*tmp_208;
      real_t a_8_3 = 0.58541019662496829*tmp_202 + 0.13819660112501059*tmp_204 + 0.13819660112501059*tmp_206 + 0.13819660112501059*tmp_208;
      real_t a_9_0 = tmp_0*tmp_209 + tmp_104*tmp_212 + tmp_210*tmp_62 + tmp_211*tmp_83;
      real_t a_9_1 = 0.13819660112501059*tmp_209 + 0.13819660112501059*tmp_210 + 0.58541019662496829*tmp_211 + 0.13819660112501059*tmp_212;
      real_t a_9_2 = 0.13819660112501059*tmp_209 + 0.58541019662496829*tmp_210 + 0.13819660112501059*tmp_211 + 0.13819660112501059*tmp_212;
      real_t a_9_3 = 0.58541019662496829*tmp_209 + 0.13819660112501059*tmp_210 + 0.13819660112501059*tmp_211 + 0.13819660112501059*tmp_212;
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
      (elMat(1, 0)) = a_1_0;
      (elMat(1, 1)) = a_1_1;
      (elMat(1, 2)) = a_1_2;
      (elMat(1, 3)) = a_1_3;
      (elMat(2, 0)) = a_2_0;
      (elMat(2, 1)) = a_2_1;
      (elMat(2, 2)) = a_2_2;
      (elMat(2, 3)) = a_2_3;
      (elMat(3, 0)) = a_3_0;
      (elMat(3, 1)) = a_3_1;
      (elMat(3, 2)) = a_3_2;
      (elMat(3, 3)) = a_3_3;
      (elMat(4, 0)) = a_4_0;
      (elMat(4, 1)) = a_4_1;
      (elMat(4, 2)) = a_4_2;
      (elMat(4, 3)) = a_4_3;
      (elMat(5, 0)) = a_5_0;
      (elMat(5, 1)) = a_5_1;
      (elMat(5, 2)) = a_5_2;
      (elMat(5, 3)) = a_5_3;
      (elMat(6, 0)) = a_6_0;
      (elMat(6, 1)) = a_6_1;
      (elMat(6, 2)) = a_6_2;
      (elMat(6, 3)) = a_6_3;
      (elMat(7, 0)) = a_7_0;
      (elMat(7, 1)) = a_7_1;
      (elMat(7, 2)) = a_7_2;
      (elMat(7, 3)) = a_7_3;
      (elMat(8, 0)) = a_8_0;
      (elMat(8, 1)) = a_8_1;
      (elMat(8, 2)) = a_8_2;
      (elMat(8, 3)) = a_8_3;
      (elMat(9, 0)) = a_9_0;
      (elMat(9, 1)) = a_9_1;
      (elMat(9, 2)) = a_9_2;
      (elMat(9, 3)) = a_9_3;
   }

   void p1_to_p2_divt_2_blending_q2::integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 4 >& elMat ) const
   {
      real_t p_affine_0_0 = coords[0][0];
      real_t p_affine_0_1 = coords[0][1];
      real_t p_affine_0_2 = coords[0][2];
      real_t p_affine_1_0 = coords[1][0];
      real_t p_affine_1_1 = coords[1][1];
      real_t p_affine_1_2 = coords[1][2];
      real_t p_affine_2_0 = coords[2][0];
      real_t p_affine_2_1 = coords[2][1];
      real_t p_affine_2_2 = coords[2][2];
      real_t p_affine_3_0 = coords[3][0];
      real_t p_affine_3_1 = coords[3][1];
      real_t p_affine_3_2 = coords[3][2];
      real_t Blending_DF_Tetrahedron_0_0 = 0;
      real_t Blending_DF_Tetrahedron_0_1 = 0;
      real_t Blending_DF_Tetrahedron_0_2 = 0;
      real_t Blending_DF_Tetrahedron_0_3 = 0;
      real_t Blending_DF_Tetrahedron_0_4 = 0;
      real_t Blending_DF_Tetrahedron_0_5 = 0;
      real_t Blending_DF_Tetrahedron_0_6 = 0;
      real_t Blending_DF_Tetrahedron_0_7 = 0;
      real_t Blending_DF_Tetrahedron_0_8 = 0;
      real_t Blending_DF_Tetrahedron_1_0 = 0;
      real_t Blending_DF_Tetrahedron_1_1 = 0;
      real_t Blending_DF_Tetrahedron_1_2 = 0;
      real_t Blending_DF_Tetrahedron_1_3 = 0;
      real_t Blending_DF_Tetrahedron_1_4 = 0;
      real_t Blending_DF_Tetrahedron_1_5 = 0;
      real_t Blending_DF_Tetrahedron_1_6 = 0;
      real_t Blending_DF_Tetrahedron_1_7 = 0;
      real_t Blending_DF_Tetrahedron_1_8 = 0;
      real_t Blending_DF_Tetrahedron_2_0 = 0;
      real_t Blending_DF_Tetrahedron_2_1 = 0;
      real_t Blending_DF_Tetrahedron_2_2 = 0;
      real_t Blending_DF_Tetrahedron_2_3 = 0;
      real_t Blending_DF_Tetrahedron_2_4 = 0;
      real_t Blending_DF_Tetrahedron_2_5 = 0;
      real_t Blending_DF_Tetrahedron_2_6 = 0;
      real_t Blending_DF_Tetrahedron_2_7 = 0;
      real_t Blending_DF_Tetrahedron_2_8 = 0;
      real_t Blending_DF_Tetrahedron_3_0 = 0;
      real_t Blending_DF_Tetrahedron_3_1 = 0;
      real_t Blending_DF_Tetrahedron_3_2 = 0;
      real_t Blending_DF_Tetrahedron_3_3 = 0;
      real_t Blending_DF_Tetrahedron_3_4 = 0;
      real_t Blending_DF_Tetrahedron_3_5 = 0;
      real_t Blending_DF_Tetrahedron_3_6 = 0;
      real_t Blending_DF_Tetrahedron_3_7 = 0;
      real_t Blending_DF_Tetrahedron_3_8 = 0;
      Blending_DF_Tetrahedron( 0.13819660112501042*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.58541019662496829*p_affine_3_0, 0.13819660112501042*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.58541019662496829*p_affine_3_1, 0.13819660112501042*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.58541019662496829*p_affine_3_2, &Blending_DF_Tetrahedron_0_0, &Blending_DF_Tetrahedron_0_1, &Blending_DF_Tetrahedron_0_2, &Blending_DF_Tetrahedron_0_3, &Blending_DF_Tetrahedron_0_4, &Blending_DF_Tetrahedron_0_5, &Blending_DF_Tetrahedron_0_6, &Blending_DF_Tetrahedron_0_7, &Blending_DF_Tetrahedron_0_8 );
      Blending_DF_Tetrahedron( 0.13819660112501048*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.58541019662496829*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.13819660112501048*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.58541019662496829*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.13819660112501048*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.58541019662496829*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_1_0, &Blending_DF_Tetrahedron_1_1, &Blending_DF_Tetrahedron_1_2, &Blending_DF_Tetrahedron_1_3, &Blending_DF_Tetrahedron_1_4, &Blending_DF_Tetrahedron_1_5, &Blending_DF_Tetrahedron_1_6, &Blending_DF_Tetrahedron_1_7, &Blending_DF_Tetrahedron_1_8 );
      Blending_DF_Tetrahedron( 0.13819660112501053*p_affine_0_0 + 0.58541019662496829*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.13819660112501053*p_affine_0_1 + 0.58541019662496829*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.13819660112501053*p_affine_0_2 + 0.58541019662496829*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_2_0, &Blending_DF_Tetrahedron_2_1, &Blending_DF_Tetrahedron_2_2, &Blending_DF_Tetrahedron_2_3, &Blending_DF_Tetrahedron_2_4, &Blending_DF_Tetrahedron_2_5, &Blending_DF_Tetrahedron_2_6, &Blending_DF_Tetrahedron_2_7, &Blending_DF_Tetrahedron_2_8 );
      Blending_DF_Tetrahedron( 0.58541019662496807*p_affine_0_0 + 0.13819660112501059*p_affine_1_0 + 0.13819660112501059*p_affine_2_0 + 0.13819660112501059*p_affine_3_0, 0.58541019662496807*p_affine_0_1 + 0.13819660112501059*p_affine_1_1 + 0.13819660112501059*p_affine_2_1 + 0.13819660112501059*p_affine_3_1, 0.58541019662496807*p_affine_0_2 + 0.13819660112501059*p_affine_1_2 + 0.13819660112501059*p_affine_2_2 + 0.13819660112501059*p_affine_3_2, &Blending_DF_Tetrahedron_3_0, &Blending_DF_Tetrahedron_3_1, &Blending_DF_Tetrahedron_3_2, &Blending_DF_Tetrahedron_3_3, &Blending_DF_Tetrahedron_3_4, &Blending_DF_Tetrahedron_3_5, &Blending_DF_Tetrahedron_3_6, &Blending_DF_Tetrahedron_3_7, &Blending_DF_Tetrahedron_3_8 );
      real_t tmp_0 = 0.44721359549995809;
      real_t tmp_1 = -p_affine_0_0;
      real_t tmp_2 = p_affine_1_0 + tmp_1;
      real_t tmp_3 = -p_affine_0_1;
      real_t tmp_4 = p_affine_2_1 + tmp_3;
      real_t tmp_5 = tmp_2*tmp_4;
      real_t tmp_6 = p_affine_2_0 + tmp_1;
      real_t tmp_7 = p_affine_1_1 + tmp_3;
      real_t tmp_8 = tmp_6*tmp_7;
      real_t tmp_9 = tmp_5 - tmp_8;
      real_t tmp_10 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_4;
      real_t tmp_11 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_3;
      real_t tmp_12 = Blending_DF_Tetrahedron_0_1*Blending_DF_Tetrahedron_0_5;
      real_t tmp_13 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_3;
      real_t tmp_14 = Blending_DF_Tetrahedron_0_0*Blending_DF_Tetrahedron_0_5;
      real_t tmp_15 = Blending_DF_Tetrahedron_0_2*Blending_DF_Tetrahedron_0_4;
      real_t tmp_16 = Blending_DF_Tetrahedron_0_6*tmp_12 - Blending_DF_Tetrahedron_0_6*tmp_15 + Blending_DF_Tetrahedron_0_7*tmp_13 - Blending_DF_Tetrahedron_0_7*tmp_14 + Blending_DF_Tetrahedron_0_8*tmp_10 - Blending_DF_Tetrahedron_0_8*tmp_11;
      real_t tmp_17 = -p_affine_0_2;
      real_t tmp_18 = p_affine_3_2 + tmp_17;
      real_t tmp_19 = p_affine_3_1 + tmp_3;
      real_t tmp_20 = p_affine_1_2 + tmp_17;
      real_t tmp_21 = tmp_20*tmp_6;
      real_t tmp_22 = p_affine_3_0 + tmp_1;
      real_t tmp_23 = p_affine_2_2 + tmp_17;
      real_t tmp_24 = tmp_23*tmp_7;
      real_t tmp_25 = tmp_2*tmp_23;
      real_t tmp_26 = tmp_20*tmp_4;
      real_t tmp_27 = 1.0 / (tmp_18*tmp_5 - tmp_18*tmp_8 + tmp_19*tmp_21 - tmp_19*tmp_25 + tmp_22*tmp_24 - tmp_22*tmp_26);
      real_t tmp_28 = tmp_27/tmp_16;
      real_t tmp_29 = tmp_28*(tmp_10 - tmp_11);
      real_t tmp_30 = tmp_21 - tmp_25;
      real_t tmp_31 = tmp_28*(tmp_13 - tmp_14);
      real_t tmp_32 = tmp_24 - tmp_26;
      real_t tmp_33 = tmp_28*(tmp_12 - tmp_15);
      real_t tmp_34 = -tmp_19*tmp_2 + tmp_22*tmp_7;
      real_t tmp_35 = tmp_18*tmp_2 - tmp_20*tmp_22;
      real_t tmp_36 = -tmp_18*tmp_7 + tmp_19*tmp_20;
      real_t tmp_37 = tmp_19*tmp_6 - tmp_22*tmp_4;
      real_t tmp_38 = -tmp_18*tmp_6 + tmp_22*tmp_23;
      real_t tmp_39 = tmp_18*tmp_4 - tmp_19*tmp_23;
      real_t tmp_40 = p_affine_0_0*p_affine_1_1;
      real_t tmp_41 = p_affine_0_0*p_affine_1_2;
      real_t tmp_42 = p_affine_2_1*p_affine_3_2;
      real_t tmp_43 = p_affine_0_1*p_affine_1_0;
      real_t tmp_44 = p_affine_0_1*p_affine_1_2;
      real_t tmp_45 = p_affine_2_2*p_affine_3_0;
      real_t tmp_46 = p_affine_0_2*p_affine_1_0;
      real_t tmp_47 = p_affine_0_2*p_affine_1_1;
      real_t tmp_48 = p_affine_2_0*p_affine_3_1;
      real_t tmp_49 = p_affine_2_2*p_affine_3_1;
      real_t tmp_50 = p_affine_2_0*p_affine_3_2;
      real_t tmp_51 = p_affine_2_1*p_affine_3_0;
      real_t tmp_52 = std::abs(p_affine_0_0*tmp_42 - p_affine_0_0*tmp_49 + p_affine_0_1*tmp_45 - p_affine_0_1*tmp_50 + p_affine_0_2*tmp_48 - p_affine_0_2*tmp_51 - p_affine_1_0*tmp_42 + p_affine_1_0*tmp_49 - p_affine_1_1*tmp_45 + p_affine_1_1*tmp_50 - p_affine_1_2*tmp_48 + p_affine_1_2*tmp_51 + p_affine_2_0*tmp_44 - p_affine_2_0*tmp_47 - p_affine_2_1*tmp_41 + p_affine_2_1*tmp_46 + p_affine_2_2*tmp_40 - p_affine_2_2*tmp_43 - p_affine_3_0*tmp_44 + p_affine_3_0*tmp_47 + p_affine_3_1*tmp_41 - p_affine_3_1*tmp_46 - p_affine_3_2*tmp_40 + p_affine_3_2*tmp_43);
      real_t tmp_53 = 0.041666666666666657*tmp_52*(-tmp_0*(tmp_29*tmp_34 + tmp_31*tmp_35 + tmp_33*tmp_36) - tmp_0*(tmp_29*tmp_37 + tmp_31*tmp_38 + tmp_33*tmp_39) - tmp_0*(tmp_29*tmp_9 + tmp_30*tmp_31 + tmp_32*tmp_33))*std::abs(tmp_16);
      real_t tmp_54 = 0.44721359549995809;
      real_t tmp_55 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_4;
      real_t tmp_56 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_3;
      real_t tmp_57 = Blending_DF_Tetrahedron_1_1*Blending_DF_Tetrahedron_1_5;
      real_t tmp_58 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_3;
      real_t tmp_59 = Blending_DF_Tetrahedron_1_0*Blending_DF_Tetrahedron_1_5;
      real_t tmp_60 = Blending_DF_Tetrahedron_1_2*Blending_DF_Tetrahedron_1_4;
      real_t tmp_61 = Blending_DF_Tetrahedron_1_6*tmp_57 - Blending_DF_Tetrahedron_1_6*tmp_60 + Blending_DF_Tetrahedron_1_7*tmp_58 - Blending_DF_Tetrahedron_1_7*tmp_59 + Blending_DF_Tetrahedron_1_8*tmp_55 - Blending_DF_Tetrahedron_1_8*tmp_56;
      real_t tmp_62 = tmp_27/tmp_61;
      real_t tmp_63 = tmp_62*(tmp_55 - tmp_56);
      real_t tmp_64 = tmp_62*(tmp_58 - tmp_59);
      real_t tmp_65 = tmp_62*(tmp_57 - tmp_60);
      real_t tmp_66 = 0.041666666666666657*tmp_52*(-tmp_54*(tmp_30*tmp_64 + tmp_32*tmp_65 + tmp_63*tmp_9) - tmp_54*(tmp_34*tmp_63 + tmp_35*tmp_64 + tmp_36*tmp_65) - tmp_54*(tmp_37*tmp_63 + tmp_38*tmp_64 + tmp_39*tmp_65))*std::abs(tmp_61);
      real_t tmp_67 = 0.44721359549995787;
      real_t tmp_68 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_4;
      real_t tmp_69 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_3;
      real_t tmp_70 = Blending_DF_Tetrahedron_2_1*Blending_DF_Tetrahedron_2_5;
      real_t tmp_71 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_3;
      real_t tmp_72 = Blending_DF_Tetrahedron_2_0*Blending_DF_Tetrahedron_2_5;
      real_t tmp_73 = Blending_DF_Tetrahedron_2_2*Blending_DF_Tetrahedron_2_4;
      real_t tmp_74 = Blending_DF_Tetrahedron_2_6*tmp_70 - Blending_DF_Tetrahedron_2_6*tmp_73 + Blending_DF_Tetrahedron_2_7*tmp_71 - Blending_DF_Tetrahedron_2_7*tmp_72 + Blending_DF_Tetrahedron_2_8*tmp_68 - Blending_DF_Tetrahedron_2_8*tmp_69;
      real_t tmp_75 = tmp_27/tmp_74;
      real_t tmp_76 = tmp_75*(tmp_68 - tmp_69);
      real_t tmp_77 = tmp_75*(tmp_71 - tmp_72);
      real_t tmp_78 = tmp_75*(tmp_70 - tmp_73);
      real_t tmp_79 = 0.041666666666666657*tmp_52*(-tmp_67*(tmp_30*tmp_77 + tmp_32*tmp_78 + tmp_76*tmp_9) - tmp_67*(tmp_34*tmp_76 + tmp_35*tmp_77 + tmp_36*tmp_78) - tmp_67*(tmp_37*tmp_76 + tmp_38*tmp_77 + tmp_39*tmp_78))*std::abs(tmp_74);
      real_t tmp_80 = -1.3416407864998727;
      real_t tmp_81 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_4;
      real_t tmp_82 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_3;
      real_t tmp_83 = Blending_DF_Tetrahedron_3_1*Blending_DF_Tetrahedron_3_5;
      real_t tmp_84 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_3;
      real_t tmp_85 = Blending_DF_Tetrahedron_3_0*Blending_DF_Tetrahedron_3_5;
      real_t tmp_86 = Blending_DF_Tetrahedron_3_2*Blending_DF_Tetrahedron_3_4;
      real_t tmp_87 = Blending_DF_Tetrahedron_3_6*tmp_83 - Blending_DF_Tetrahedron_3_6*tmp_86 + Blending_DF_Tetrahedron_3_7*tmp_84 - Blending_DF_Tetrahedron_3_7*tmp_85 + Blending_DF_Tetrahedron_3_8*tmp_81 - Blending_DF_Tetrahedron_3_8*tmp_82;
      real_t tmp_88 = tmp_27/tmp_87;
      real_t tmp_89 = tmp_88*(tmp_81 - tmp_82);
      real_t tmp_90 = tmp_88*(tmp_84 - tmp_85);
      real_t tmp_91 = tmp_88*(tmp_83 - tmp_86);
      real_t tmp_92 = 0.041666666666666657*tmp_52*(-tmp_80*(tmp_30*tmp_90 + tmp_32*tmp_91 + tmp_89*tmp_9) - tmp_80*(tmp_34*tmp_89 + tmp_35*tmp_90 + tmp_36*tmp_91) - tmp_80*(tmp_37*tmp_89 + tmp_38*tmp_90 + tmp_39*tmp_91))*std::abs(tmp_87);
      real_t a_0_0 = 0.13819660112501042*tmp_53 + 0.13819660112501048*tmp_66 + 0.13819660112501053*tmp_79 + 0.58541019662496807*tmp_92;
      real_t a_0_1 = 0.13819660112501059*tmp_53 + 0.13819660112501059*tmp_66 + 0.58541019662496829*tmp_79 + 0.13819660112501059*tmp_92;
      real_t a_0_2 = 0.13819660112501059*tmp_53 + 0.58541019662496829*tmp_66 + 0.13819660112501059*tmp_79 + 0.13819660112501059*tmp_92;
      real_t a_0_3 = 0.58541019662496829*tmp_53 + 0.13819660112501059*tmp_66 + 0.13819660112501059*tmp_79 + 0.13819660112501059*tmp_92;
      (elMat(0, 0)) = a_0_0;
      (elMat(0, 1)) = a_0_1;
      (elMat(0, 2)) = a_0_2;
      (elMat(0, 3)) = a_0_3;
   }

   void p1_to_p2_divt_2_blending_q2::Blending_DF_Triangle( real_t in_0, real_t in_1, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3 ) const
   {
      Point3D  mappedPt( {in_0, in_1, 0} );
      Matrix2r DPsi;
      geometryMap_->evalDF( mappedPt, DPsi );
      *out_0 = DPsi( 0, 0 );
      *out_1 = DPsi( 0, 1 );
      *out_2 = DPsi( 1, 0 );
      *out_3 = DPsi( 1, 1 );
   }

   void p1_to_p2_divt_2_blending_q2::Blending_DF_Tetrahedron( real_t in_0, real_t in_1, real_t in_2, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3, real_t * out_4, real_t * out_5, real_t * out_6, real_t * out_7, real_t * out_8 ) const
   {
      Point3D  mappedPt( {in_0, in_1, in_2} );
      Matrix3r DPsi;
      geometryMap_->evalDF( mappedPt, DPsi );
      *out_0 = DPsi( 0, 0 );
      *out_1 = DPsi( 0, 1 );
      *out_2 = DPsi( 0, 2 );
      *out_3 = DPsi( 1, 0 );
      *out_4 = DPsi( 1, 1 );
      *out_5 = DPsi( 1, 2 );
      *out_6 = DPsi( 2, 0 );
      *out_7 = DPsi( 2, 1 );
      *out_8 = DPsi( 2, 2 );
   }

} // namespace forms
} // namespace hyteg
