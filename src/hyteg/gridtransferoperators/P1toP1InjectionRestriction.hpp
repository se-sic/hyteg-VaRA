/*
 * Copyright (c) 2017-2023 Dominik Thoennes, Nils Kohl, Marcus Mohr.
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

#include "hyteg/gridtransferoperators/RestrictionOperator.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"

namespace hyteg {

class P1toP1InjectionRestriction : public RestrictionOperator< P1Function< real_t > >
{
 public:
   void restrict( const P1Function< real_t >& function, const uint_t& sourceLevel, const DoFType& flag ) const override
   {
      restrict3D( function, sourceLevel, flag );
   }

 private:
   void restrict3D( const P1Function< real_t >& function, const uint_t& sourceLevel, const DoFType& flag ) const;

   void restrictMacroVertex( const real_t* src, real_t* dst, const uint_t& sourceLevel ) const;

   void restrictMacroEdge( const real_t* src, real_t* dst, const uint_t& sourceLevel ) const;

   void restrictMacroFace( const real_t* src, real_t* dst, const uint_t& sourceLevel ) const;

   void restrictMacroCell( const real_t* src, real_t* dst, const uint_t& sourceLevel ) const;
};

} // namespace hyteg
