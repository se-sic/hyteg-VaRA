
//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "all.hpp"
#include "core/DataTypes.h"
#include "core/Macros.h"
#include "tinyhhg_core/edgedofspace/EdgeDoFIndexing.hpp"
#include <map>
#define RESTRICT WALBERLA_RESTRICT

namespace hhg {
namespace EdgeDoFToVertexDoF {
namespace generated {

void apply_3D_macrocell_edgedof_to_vertexdof_add(double const * RESTRICT const _data_edgeCellSrc_X, double const * RESTRICT const _data_edgeCellSrc_XY, double const * RESTRICT const _data_edgeCellSrc_XYZ, double const * RESTRICT const _data_edgeCellSrc_XZ, double const * RESTRICT const _data_edgeCellSrc_Y, double const * RESTRICT const _data_edgeCellSrc_YZ, double const * RESTRICT const _data_edgeCellSrc_Z, double * RESTRICT _data_vertexCellDst, std::map< hhg::edgedof::EdgeDoFOrientation, std::map< hhg::indexing::IndexIncrement, double > > e2vStencilMap, int64_t level);

} // namespace generated
} // namespace EdgeDoFToVertexDoF
} // namespace hhg