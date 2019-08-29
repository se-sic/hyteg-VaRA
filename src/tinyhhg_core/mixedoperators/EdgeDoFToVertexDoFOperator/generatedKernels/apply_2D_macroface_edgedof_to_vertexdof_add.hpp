
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

namespace hhg {
namespace EdgeDoFToVertexDoF {
namespace generated {

void apply_2D_macroface_edgedof_to_vertexdof_add(double const * RESTRICT const _data_edgeFaceSrc_X, double const * RESTRICT const _data_edgeFaceSrc_XY, double const * RESTRICT const _data_edgeFaceSrc_Y, double const * RESTRICT const _data_edgeToVertexFaceStencil, double * RESTRICT _data_p1FaceDst, int32_t level);

} // namespace generated
} // namespace EdgeDoFToVertexDoF
} // namespace hhg