
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
namespace P2 {
namespace macrocell {
namespace generated {

void sor_3D_macrocell_P2_update_edgedofs_by_type_Z(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double * RESTRICT _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_Z, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int32_t level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);

} // namespace generated
} // namespace macrocell
} // namespace P2
} // namespace hyteg