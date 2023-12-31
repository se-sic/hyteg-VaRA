/*
 * Copyright (c) 2017-2022 Dominik Thoennes, Marcus Mohr, Nils Kohl.
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

#include "hyteg/sparseassembly/DirichletBCs.hpp"

#include "P1DGEP0StokesFunction.hpp"

namespace hyteg {

void applyDirichletBC( const EGP0StokesFunction< idx_t >& numerator, std::vector< idx_t >& mat, uint_t level )
{
   applyDirichletBC( numerator.uvw(), mat, level );
}

} // namespace hyteg
