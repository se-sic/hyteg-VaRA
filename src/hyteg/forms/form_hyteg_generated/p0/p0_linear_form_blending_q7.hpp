/*
 * Copyright (c) 2017-2022 Nils Kohl.
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
 * Avoid modifying this file. If buggy, consider fixing the generator itself.
 */

#pragma once

#include "hyteg/geometry/GeometryMap.hpp"
#include "hyteg/forms/form_hyteg_base/P0FormHyTeG.hpp"

namespace hyteg {
namespace forms {

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p0_linear_form_blending_q7
/// - description: Implements a linear form of type: (k(x), psi) where psi a test function and k = k(x) a scalar, external function.
/// - trial space: Lagrange, degree: 0
/// - test space:  Lagrange, degree: 0
///
class p0_linear_form_blending_q7 : public P0FormHyTeG
{

 public:

   p0_linear_form_blending_q7() { WALBERLA_ABORT("Not implemented."); }

   p0_linear_form_blending_q7( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_2D_k, std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_k )
   : callback_Scalar_Variable_Coefficient_2D_k(_callback_Scalar_Variable_Coefficient_2D_k)
   , callback_Scalar_Variable_Coefficient_3D_k(_callback_Scalar_Variable_Coefficient_3D_k)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_2D_k;
   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_k;


 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (1, 1)
   /// - quadrature rule:                        Gatermann | points: 12, degree: 7, test tolerance: 1.4445166104262934e-15
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              124     202       0       0     13             97                36
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 1 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (1, 1)
   /// - quadrature rule:                        Gatermann | points: 12, degree: 7, test tolerance: 1.4445166104262934e-15
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              124     202       0       0     13             97                36
   ///
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 1 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (1, 1)
   /// - quadrature rule:                        Keast 8 | points: 31, degree: 7, test tolerance: 1.19e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              694    1148       0       0     32            435                93
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 1 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (1, 1)
   /// - quadrature rule:                        Keast 8 | points: 31, degree: 7, test tolerance: 1.19e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              694    1148       0       0     32            435                93
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 1 >& elMat ) const override;

 private:

   void Blending_DF_Triangle_blend( real_t in_0, real_t in_1, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3 ) const;

   void Blending_F_Triangle_blend( real_t in_0, real_t in_1, real_t * out_0, real_t * out_1 ) const;

   void Scalar_Variable_Coefficient_2D_k( real_t in_0, real_t in_1, real_t * out_0 ) const;

   void Blending_DF_Tetrahedron_blend( real_t in_0, real_t in_1, real_t in_2, real_t * out_0, real_t * out_1, real_t * out_2, real_t * out_3, real_t * out_4, real_t * out_5, real_t * out_6, real_t * out_7, real_t * out_8 ) const;

   void Blending_F_Tetrahedron_blend( real_t in_0, real_t in_1, real_t in_2, real_t * out_0, real_t * out_1, real_t * out_2 ) const;

   void Scalar_Variable_Coefficient_3D_k( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

} // namespace forms
} // namespace hyteg
