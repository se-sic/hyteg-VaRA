/*
 * Copyright (c) 2019 Nils Kohl, Dominik Thoennes.
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

//////////////////////////////////////////////////////////////////////////////
// This file is generated! To fix issues, please fix them in the generator. //
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "core/Macros.h"
#include "hyteg/edgedofspace/EdgeDoFOrientation.hpp"
#include "hyteg/indexing/Common.hpp"
#include <map>
#define RESTRICT WALBERLA_RESTRICT

namespace hyteg {
namespace P2 {
namespace macrocell {
namespace generated {

void sor_3D_macrocell_P2_update_edgedofs_by_type_X(double * RESTRICT _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_X, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_Y(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double * RESTRICT _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_Y, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_Z(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double * RESTRICT _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_Z, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_XY(double const * RESTRICT const _data_edgeCellDst_X, double * RESTRICT _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_XY, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_XZ(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double * RESTRICT _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_XZ, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_YZ(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double const * RESTRICT const _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double * RESTRICT _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_YZ, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);
void sor_3D_macrocell_P2_update_edgedofs_by_type_XYZ(double const * RESTRICT const _data_edgeCellDst_X, double const * RESTRICT const _data_edgeCellDst_XY, double * RESTRICT _data_edgeCellDst_XYZ, double const * RESTRICT const _data_edgeCellDst_XZ, double const * RESTRICT const _data_edgeCellDst_Y, double const * RESTRICT const _data_edgeCellDst_YZ, double const * RESTRICT const _data_edgeCellDst_Z, double const * RESTRICT const _data_edgeCellRhs_XYZ, double const * RESTRICT const _data_vertexCellDst, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > > e2eStencilMap, int level, double relax, std::map< hyteg::edgedof::EdgeDoFOrientation, std::map< hyteg::indexing::IndexIncrement, double > > v2eStencilMap);

} // namespace generated
} // namespace macrocell
} // namespace P2
} // namespace hyteg