/*
 * Copyright (c) 2017-2019 Daniel Drzisga, Dominik Thoennes, Marcus Mohr, Nils Kohl.
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
#pragma once

#include <functional>
#include <array>

#include "core/Abort.h"

#include "hyteg/types/Matrix.hpp"

namespace hyteg {
namespace fenics {

using walberla::real_c;

enum ElementType
{
   GRAY,
   BLUE
};

/// Use this UFCOperator to assemble the zero-matrix.
class NoAssemble {
 public:
  void tabulate_tensor(double *,
                       const double * const *,
                       const double *,
                       int) const { }
};

/// Use this UFCOperator to indicate that no assembly is defined at all.
class UndefinedAssembly {
public:
    void tabulate_tensor(double *,
                         const double * const *,
                         const double *,
                         int) const { WALBERLA_ABORT( "Assembly undefined." ); }
};

/// Dummy UFCOperator for a 10x10 (i.e. tet, P2) stiffness matrix
class Dummy10x10Assembly
{
public:

    Dummy10x10Assembly() : stiffnessMatrix_( Matrix10r::Zero() ) {}
    Dummy10x10Assembly( const double & constant ) : stiffnessMatrix_( Matrix10r::Constant(constant) ) {}

    void tabulate_tensor(double * A,
                         const double * const *,
                         const double *,
                         int) const
    {
      for ( uint_t i = 0; i < 100; i++ )
        A[i] = stiffnessMatrix_.data()[i];
    }

private:

    Matrix10r stiffnessMatrix_;
};


typedef std::function<void(double *,
                      const double * const *,
                      const double *,
                      int cell_orientation)> TabulateTensor;

  /// The P2DoFMap maps a pair of vertex indices to a corresponding local
  /// index for a degree of freedom using the FEniCS indexing for a
  /// P2 element on a tetrahedron.
  ///
  /// There are two cases:
  ///
  /// (a) Both vertex indices are identical, then the map stores the
  ///     index of the dof associated with this vertex.
  ///
  /// (b) The two vertex indices are different, then the map stores
  ///     the index of the dof associated with the midpoint of the
  ///     tet's edge given by those two vertices.
  ///
  /// P2DoFMap[0][0] = 0;
  /// P2DoFMap[0][1] = 9;
  /// P2DoFMap[0][2] = 8;
  /// P2DoFMap[0][3] = 7;
  ///
  /// P2DoFMap[1][0] = 9;
  /// P2DoFMap[1][1] = 1;
  /// P2DoFMap[1][2] = 6;
  /// P2DoFMap[1][3] = 5;
  ///
  /// P2DoFMap[2][0] = 8;
  /// P2DoFMap[2][1] = 6;
  /// P2DoFMap[2][2] = 2;
  /// P2DoFMap[2][3] = 4;
  ///
  /// P2DoFMap[3][0] = 7;
  /// P2DoFMap[3][1] = 5;
  /// P2DoFMap[3][2] = 4;
  /// P2DoFMap[3][3] = 3;
  // wait for C++17
  // constexpr static std::array< std::array<uint_t,4>, 4 > P2DoFMap =
  const std::array< std::array<int,4>, 4 > P2DoFMap =
    { { { 0, 9, 8, 7 },
        { 9, 1, 6, 5 },
        { 8, 6, 2, 4 },
        { 7, 5, 4, 3 } } };

  /// The P2DoFMapTriangle maps a pair of vertex indices to a corresponding
  /// local index for a degree of freedom using the FEniCS indexing for a
  /// P2 element on a triangle.
  ///
  /// There are two cases:
  ///
  /// (a) Both vertex indices are identical, then the map stores the
  ///     index of the dof associated with this vertex.
  ///
  /// (b) The two vertex indices are different, then the map stores
  ///     the index of the dof associated with the midpoint of the
  ///     tet's edge given by those two vertices.
  ///
  /// P2DoFMapTriangle[0][0] = 0;
  /// P2DoFMapTriangle[0][1] = 5;
  /// P2DoFMapTriangle[0][2] = 4;
  ///
  /// P2DoFMapTriangle[1][0] = 5;
  /// P2DoFMapTriangle[1][1] = 1;
  /// P2DoFMapTriangle[1][2] = 3;
  ///
  /// P2DoFMapTriangle[2][0] = 4;
  /// P2DoFMapTriangle[2][1] = 3;
  /// P2DoFMapTriangle[2][2] = 2;
  //
  // wait for C++17
  // constexpr static std::array< std::array<uint_t,3>, 3 > P2DoFMapTriangle =
  const std::array< std::array<int,3>, 3 > P2DoFMapTriangle =
    { { { 0, 5, 4 },
        { 5, 1, 3 },
        { 4, 3, 2 } } };

} // namespace fenics
} // namespace hyteg
