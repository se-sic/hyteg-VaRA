/*
 * Copyright (c) 2021 Benjamin Mann
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

#include "simplex.hpp"

namespace hyteg {
namespace adaptiveRefinement {

// Factory for constructing sub-simplices of a given tetrahedron
class SimplexFactory
{
 public:
   using FaceMap = std::map< Idx< 3 >, std::shared_ptr< Simplex2 > >;
   using EdgeMap = std::map< Idx< 2 >, std::shared_ptr< Simplex1 > >;

   /* Ctor
      @param parent     parent-tetrahedron
      @param vertices   set of vertices for sub-simplices (i.e. global_vertices \intersect parent),
                        given by their global vertex-id
   */
   SimplexFactory( const std::shared_ptr< Simplex3 > parent, const std::vector< uint_t >& vertices )
   : _parent( parent )
   , _vertices( vertices )
   , _geometryMap( ( parent == nullptr ) ? PrimitiveID() : parent->getGeometryMap() )
   , _boundaryFlag( ( parent == nullptr ) ? 0 : parent->getBoundaryFlag() )
   , _targetRank( ( parent == nullptr ) ? 0 : parent->getTargetRank() )
   {}

   /* add existing face \\subset parent for creating sub-tetrahedra
      @param a    index < SimplexFactory::_vertices.size()
      @param b    index < SimplexFactory::_vertices.size()
      @param c    index < SimplexFactory::_vertices.size()
      @param face conv{x_a, x_b, x_c}, with x_i = Mesh::_vertices[SimplexFactory::_vertices[i]]
   */
   inline void add_face( uint_t a, uint_t b, uint_t c, std::shared_ptr< Simplex2 > face ) { _faces[{ a, b, c }] = face; }
   /* add existing edge \\subset parent for creating sub-faces/-tetrahedra
      @param a    index < SimplexFactory::_vertices.size()
      @param b    index < SimplexFactory::_vertices.size()
      @param edge conv{x_a, x_b}, with x_i = Mesh::_vertices[SimplexFactory::_vertices[i]]
   */
   inline void add_edge( uint_t a, uint_t b, std::shared_ptr< Simplex1 > edge ) { _edges[{ a, b }] = edge; }

   /* create new edge \\subset interior(parent) and add it to list of sub-edges
      @param a    index < SimplexFactory::_vertices.size()
      @param b    index < SimplexFactory::_vertices.size()
      @return pointer to edge = conv{x_a, x_b}, with x_i = Mesh::_vertices[SimplexFactory::_vertices[i]]
   */
   std::shared_ptr< Simplex1 > make_edge( uint_t a, uint_t b, Color color = RED );
   /* create new face \\subset interior(parent) and add it to list of sub-faces
      @param a    index < SimplexFactory::_vertices.size()
      @param b    index < SimplexFactory::_vertices.size()
      @param c    index < SimplexFactory::_vertices.size()
      @return pointer to face = conv{x_a, x_b, x_c}, with x_i = Mesh::_vertices[SimplexFactory::_vertices[i]]
   */
   std::shared_ptr< Simplex2 > make_face( uint_t a, uint_t b, uint_t c );
   /* create new cell \\subset parent
      @param a    index < SimplexFactory::_vertices.size()
      @param b    index < SimplexFactory::_vertices.size()
      @param c    index < SimplexFactory::_vertices.size()
      @param d    index < SimplexFactory::_vertices.size()
      @return pointer to cell = conv{x_a, x_b, x_c, x_d}, with x_i = Mesh::_vertices[SimplexFactory::_vertices[i]]
   */
   std::shared_ptr< Simplex3 > make_cell( uint_t a, uint_t b, uint_t c, uint_t d );

   inline const FaceMap& faces() { return _faces; }
   inline const EdgeMap& edges() { return _edges; }

 private:
   const std::shared_ptr< Simplex3 > _parent;
   std::vector< uint_t >             _vertices;
   EdgeMap                           _edges;
   FaceMap                           _faces;
   PrimitiveID                       _geometryMap;
   uint_t                            _boundaryFlag;
   uint_t                            _targetRank;
};

} // namespace adaptiveRefinement
} // namespace hyteg