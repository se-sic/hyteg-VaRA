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
 * Software:
 *
 * - quadpy version: 0.16.5
 *
 * Avoid modifying this file. If buggy, consider fixing the generator itself.
 */

#pragma once

#include "hyteg/geometry/GeometryMap.hpp"
#include "hyteg/forms/form_hyteg_base/P2FormHyTeG.hpp"

namespace hyteg {
namespace forms {

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_0_0_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_0_0_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_0_0_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_0_0_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu, std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_2D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   , callback_Scalar_Variable_Coefficient_2D_mu(_callback_Scalar_Variable_Coefficient_2D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;
   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_2D_mu;


 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              192     435       2       0      1            271                 3
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                               99     177       1       0      1            104                 3
   ///
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              995    1648       2       0      1            874                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              392     564       1       0      1            312                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_2D_mu( real_t in_0, real_t in_1, real_t * out_0 ) const;

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_0_1_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_0_1_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_0_1_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_0_1_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu, std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_2D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   , callback_Scalar_Variable_Coefficient_2D_mu(_callback_Scalar_Variable_Coefficient_2D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;
   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_2D_mu;


 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              138     269       2       0      1            227                 3
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                               69      95       1       0      1             59                 3
   ///
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_2D_mu( real_t in_0, real_t in_1, real_t * out_0 ) const;

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_0_2_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_0_2_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_0_2_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_0_2_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;


 public:

   /// \brief Not implemented - does nothing.
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Not implemented - does nothing.
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_1_0_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_1_0_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_1_0_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_1_0_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu, std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_2D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   , callback_Scalar_Variable_Coefficient_2D_mu(_callback_Scalar_Variable_Coefficient_2D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;
   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_2D_mu;


 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              138     269       2       0      1            227                 3
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                               69      95       1       0      1             59                 3
   ///
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_2D_mu( real_t in_0, real_t in_1, real_t * out_0 ) const;

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_1_1_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_1_1_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_1_1_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_1_1_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu, std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_2D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   , callback_Scalar_Variable_Coefficient_2D_mu(_callback_Scalar_Variable_Coefficient_2D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;
   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_2D_mu;


 public:

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              192     430       2       0      1            268                 3
   ///
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       triangle, dim: 2, vertices: 3
   /// - element matrix dimensions (rows, cols): (6, 6)
   /// - quadrature rule:                        Dunavant 2 | points: 3, degree: 2, test tolerance: 2.22e-16
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                               99     177       1       0      1            104                 3
   ///
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              995    1648       2       0      1            874                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              392     566       1       0      1            314                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_2D_mu( real_t in_0, real_t in_1, real_t * out_0 ) const;

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_1_2_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_1_2_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_1_2_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_1_2_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;


 public:

   /// \brief Not implemented - does nothing.
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Not implemented - does nothing.
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_2_0_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_2_0_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_2_0_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_2_0_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;


 public:

   /// \brief Not implemented - does nothing.
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Not implemented - does nothing.
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_2_1_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_2_1_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_2_1_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_2_1_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;


 public:

   /// \brief Not implemented - does nothing.
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Not implemented - does nothing.
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              519     788       2       0      1            580                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              213     242       1       0      1            146                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

/// Implementation of the integration of a weak form over an element.
///
/// - name:        p2_epsilonvar_2_2_affine_q2
/// - description: 
/// - trial space: Lagrange, degree: 2
/// - test space:  Lagrange, degree: 2
///
class p2_epsilonvar_2_2_affine_q2 : public P2FormHyTeG
{

 public:

   p2_epsilonvar_2_2_affine_q2() { WALBERLA_ABORT("Not implemented."); }

   p2_epsilonvar_2_2_affine_q2( std::function< real_t ( const Point3D & ) > _callback_Scalar_Variable_Coefficient_3D_mu )
   : callback_Scalar_Variable_Coefficient_3D_mu(_callback_Scalar_Variable_Coefficient_3D_mu)
   {}

 private:

   std::function< real_t ( const Point3D & ) > callback_Scalar_Variable_Coefficient_3D_mu;


 public:

   /// \brief Not implemented - does nothing.
   void integrateAll( const std::array< Point3D, 3 >& coords, Matrix< real_t, 6, 6 >& elMat ) const override;

   /// \brief Not implemented - does nothing.
   void integrateRow0( const std::array< Point3D, 3 >& coords, Matrix< real_t, 1, 6 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              995    1648       2       0      1            874                 4
   ///
   void integrateAll( const std::array< Point3D, 4 >& coords, Matrix< real_t, 10, 10 >& elMat ) const override;

   /// \brief Integrates the weak form over the passed element (vertices in computational space).
   ///
   /// - element geometry:                       tetrahedron, dim: 3, vertices: 4
   /// - element matrix dimensions (rows, cols): (10, 10)
   /// - quadrature rule:                        Vioreanu-Rokhlin 1 | points: 4, degree: 2, test tolerance: 2.379e-17
   /// - floating point operations:
   ///                                             adds    muls    divs    pows    abs    assignments    function_calls
   ///                                           ------  ------  ------  ------  -----  -------------  ----------------
   ///                                              392     563       1       0      1            314                 4
   ///
   void integrateRow0( const std::array< Point3D, 4 >& coords, Matrix< real_t, 1, 10 >& elMat ) const override;

 private:

   void Scalar_Variable_Coefficient_3D_mu( real_t in_0, real_t in_1, real_t in_2, real_t * out_0 ) const;

};

} // namespace forms
} // namespace hyteg
