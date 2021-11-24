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

#include <algorithm>
#include <array>
#include <assert.h>
#include <cmath>
#include <map>
#include <vector>

#include "hyteg/types/pointnd.hpp"

namespace hyteg {
namespace adaptiveRefinement {

using walberla::int64_t;
using walberla::real_t;

enum Color
{
   RED,
   GREEN
};

// multi-index to identify a K-simplex by its vertices
template < int K >
class Idx : public std::array< int64_t, K >
{
 public:
   template < class... Args >
   inline Idx( Args&&... args )
   : std::array< int64_t, K >( { args... } )
   {
      std::sort( this->begin(), this->end() );
   }
};

// CRTP-base class for K-simplices
template < int K, class K_Simplex >
class Simplex
{
 public:
   /* Ctor
      @param vertices   global indices of the new Simplexes vertices
      @param parent     K-simplex s.th. this is a direct refinement of parent
   */
   Simplex( const std::array< int64_t, K + 1 >& vertices, std::shared_ptr< K_Simplex > parent )
   : _vertices( vertices )
   , _parent( parent )
   {}

   // return true if this has been refined
   bool has_children() const { return not _children.empty(); }
   /* check whether idx is a vertex of this element
      @param idx global vertex-id
      @return (idx \\in Simplex::_vertices)
   */
   bool has_vertex( int64_t idx ) const;

   const std::array< int64_t, K + 1 >&                get_vertices() const { return _vertices; }
   const std::vector< std::shared_ptr< K_Simplex > >& get_siblings() const { return _parent->_children; }
   std::shared_ptr< K_Simplex >                       get_parent() const { return _parent; }
   const std::vector< std::shared_ptr< K_Simplex > >& get_children() const { return _children; }
   // @returns children, ordered s.th. vertices[j] \\subset children[j] for all j < children.size()
   const std::vector< std::shared_ptr< K_Simplex > > get_children_sorted( const std::array< int64_t, K + 1 >& vertices ) const;

   /* compute the barycenter of a simplex
      @nodes  coordinates of the global vertices
   */
   Point3D barycenter( const std::vector< Point3D >& nodes ) const;
   /* compute the volme of a simplex
      @nodes  coordinates of the global vertices
   */
   double volume( const std::vector< Point3D >& nodes ) const;

   /* remove all children
      @return true if any children have been killed
   */
   bool kill_children();
   /* add new child
   */
   void add_child( const std::shared_ptr< K_Simplex >& child );

 protected:
   std::array< int64_t, K + 1 >                _vertices;
   std::shared_ptr< K_Simplex >                _parent;
   std::vector< std::shared_ptr< K_Simplex > > _children;
};

// 1-simplex (edge)
class Simplex1 : public Simplex< 1, Simplex1 >
{
 public:
   /* Ctor
      @param p1      global id of first vertex
      @param p2      global id of second vertex
      @param parent  parent-edge
      @param c       = GREEN if this edge was added during green refinement step
   */
   Simplex1( int64_t p1, int64_t p2, std::shared_ptr< Simplex1 > parent = nullptr, Color c = RED )
   : Simplex< 1, Simplex1 >( { p1, p2 }, parent )
   , _color( c )
   , _midpoint( -1 )
   {}

   bool is_green() const { return _color == GREEN; }

   /* when an edge is refined, the index of the midpoint should be added!
      @param idx  global id of the newly added vertex
   */
   void set_midpoint_idx( int64_t idx ) { _midpoint = idx; }
   // @return global id of the vertex on the edge midpoint or -1 if edge hasn't been refined
   int64_t get_midpoint_idx() const { return _midpoint; }

   /* count number of vertices in the interior of this edge
      @return number of vertices on the interior of *this
   */
   int inner_vertices() const;

 private:
   Color   _color;
   int64_t _midpoint;
};

// 2-simplex (face)
class Simplex2 : public Simplex< 2, Simplex2 >
{
 public:
   /* create new face with the following form
         0
         |\
         | \
         |  \
         |   \
         |    \
      [0]|     \ [2]
         |      \
         |       \
         |        \
         |         \
         |          \
         1-----------2
               [1]
   */
   Simplex2( const std::array< int64_t, 3 >&                     vertices,
             const std::array< std::shared_ptr< Simplex1 >, 3 >& edges,
             std::shared_ptr< Simplex2 >                         parent = nullptr );

   /* count inner vertices on all edges
      @return sum(edge->inner_vertices())
   */
   int vertices_on_edges() const;

   bool has_green_edge() const;

   /* compute minimum and maximum angle of this face
      @nodes  coordinates of the global vertices
      @return {min_φ, max_φ}
   */
   std::pair< real_t, real_t > min_max_angle( const std::vector< Point3D >& nodes ) const;

   const std::array< std::shared_ptr< Simplex1 >, 3 >& get_edges() const { return _edges; }
   // @returns edges of this face, ordered s.th. vertices[j] \\subset edges[j] for all j < 3
   std::array< std::shared_ptr< Simplex1 >, 3 > get_edges_sorted( const std::array< int64_t, 3 >& vertices ) const;
   /* get pointer to a certain edge of this face
      @param a    global vertex id
      @param b    global vertex id
      @return pointer to conv{a,b} if a,b \\in Face::_vertices, null otherwise
   */
   std::shared_ptr< Simplex1 > get_Edge( int64_t a, int64_t b ) const;

 private:
   /* //!ordering of vertices must match ordering of edges, i.e.,
      set{_edge[i]->_vertices[0],_edge[i]->_vertices[1]} == set{_vertices[i], _vertices[(i+1)%3]}
   */
   std::array< std::shared_ptr< Simplex1 >, 3 > _edges;
};

// 3-simplex (cell)
class Simplex3 : public Simplex< 3, Simplex3 >
{
 public:
   /* create new cell with the following form

              vertices:                      edges:                      faces:
                   3
                  /|\                          /|\                          /|\
                 / | \                        / | \                        / | \
                /  |  \                      /  |  \                      /  |  \
               /   |   \                    /   |   \                    /   |   \
              /    |    \                  /    |    \                  /    |    \
             /     |     \                /     |     \                /     | (3) (back)
            /      |      \            [3]    [4]    [5]              /      |      \
           /       |       \            /       |       \            /       |       \
          /        |        \          /        |        \          /        |        \
      0  /- - - - -| - - - - \  2     /- - - - -| - [2] - \        /- - - - -| - - - - \
         '*,       |        ,*        '*,       |        ,*        '*,  (1)  |   (2)  ,*
            '*,    |    ,*'              '*,    |    ,*'              '*,    |    ,*'
               '*, |,*'               [0]   '*, |,*'   [1]               '*, |,*'
                   1                                                            (0) (bottom)
   */
   Simplex3( const std::array< int64_t, 4 >&                     vertices,
             const std::array< std::shared_ptr< Simplex1 >, 6 >& edges,
             const std::array< std::shared_ptr< Simplex2 >, 4 >& faces,
             std::shared_ptr< Simplex3 >                         parent = nullptr );

   bool has_green_edge() const;

   /* count inner vertices on all edges
      @return sum(edge->inner_vertices())
   */
   int vertices_on_edges() const;

   /* compute minimum and maximum angle of this face
      @nodes  coordinates of the global vertices
      @return {min_φ, max_φ}
   */
   std::pair< real_t, real_t > min_max_angle( const std::vector< Point3D >& nodes ) const;

   const std::array< std::shared_ptr< Simplex1 >, 6 >& get_edges() const { return _edges; }
   const std::array< std::shared_ptr< Simplex2 >, 4 >& get_faces() const { return _faces; }

   /* get pointer to a certain edge of this cell
      @param a    global vertex id
      @param b    global vertex id
      @return pointer to conv{a,b} if a,b \\in Cell::_vertices, null otherwise
   */
   std::shared_ptr< Simplex1 > get_Edge( int64_t a, int64_t b ) const;
   /* get pointer to a certain face of this cell
      @param a    global vertex id
      @param b    global vertex id
      @param c    global vertex id
      @return pointer to conv{a,b,c} if a,b,c \\in Cell::_vertices, null otherwise
   */
   std::shared_ptr< Simplex2 > get_Face( int64_t a, int64_t b, int64_t c ) const;

   /* return all faces with vertices on the interior of their edges
      @return {F_red, F_green} s.th. F_* are those faces eligible for *-refinement (may be refined already)
   */
   std::map< Color, std::vector< std::shared_ptr< Simplex2 > > > refined_faces() const;

 private:
   std::array< std::shared_ptr< Simplex1 >, 6 > _edges;
   std::array< std::shared_ptr< Simplex2 >, 4 > _faces;
};

} // namespace adaptiveRefinement
} // namespace hyteg
