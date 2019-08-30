
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "all.hpp"
#include "core/Macros.h"
#include "tinyhhg_core/edgedofspace/EdgeDoFOrientation.hpp"
#include "tinyhhg_core/indexing/Common.hpp"
#include <map>
#define RESTRICT WALBERLA_RESTRICT

namespace hyteg {
namespace vertexdof {
namespace macroface {
namespace generated {

void sor_3D_macroface_P1_impl_031_032(double * RESTRICT _data_vertexFaceDst, double * RESTRICT _data_vertexFaceDst_gl0, double * RESTRICT _data_vertexFaceDst_gl1, double const * RESTRICT const _data_vertexFaceRhs, int32_t level, double relax, std::map< hyteg::indexing::IndexIncrement, double > v2v_cell_stencil_fused_face_0, std::map< hyteg::indexing::IndexIncrement, double > v2v_cell_stencil_fused_face_1);

} // namespace generated
} // namespace macroface
} // namespace vertexdof
} // namespace hyteg