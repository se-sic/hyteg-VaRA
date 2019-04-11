#include "VertexDoFIndexing.hpp"

#include "core/debug/Debug.h"

#include "tinyhhg_core/indexing/MacroEdgeIndexing.hpp"
#include "tinyhhg_core/Levelinfo.hpp"

namespace hhg {
namespace vertexdof {

// ##################
// ### Macro Edge ###
// ##################

namespace macroedge {

uint_t neighborFaceGhostLayerSize( const uint_t& level )
{
   return levelinfo::num_microvertices_per_edge( level ) - 1;
}

uint_t neighborCellGhostLayerSize( const uint_t& level )
{
   return levelinfo::num_microvertices_per_edge( level ) - 2;
}

uint_t index( const uint_t& level, const uint_t& x )
{
   return hhg::indexing::macroEdgeIndex( levelinfo::num_microvertices_per_edge( level ), x );
}

uint_t innerIndex( const uint_t & level, const uint_t & x )
{
  WALBERLA_ASSERT_GREATER( x, 0 );
  const uint_t innerWidth = levelinfo::num_microvertices_per_edge( level ) - 2;
  return indexing::macroEdgeIndex( innerWidth, x - 1 );
}

uint_t indexOnNeighborFace( const uint_t& level, const uint_t& x, const uint_t& neighbor )
{
   return hhg::indexing::macroEdgeSize( levelinfo::num_microvertices_per_edge( level ) ) +
          neighbor * hhg::indexing::macroEdgeSize( neighborFaceGhostLayerSize( level ) ) +
          hhg::indexing::macroEdgeIndex( neighborFaceGhostLayerSize( level ), x );
}

uint_t indexOnNeighborCell( const uint_t& level, const uint_t& x, const uint_t& neighbor, const uint_t& numNeighborFaces )
{
   return hhg::indexing::macroEdgeSize( levelinfo::num_microvertices_per_edge( level ) ) +
          numNeighborFaces * hhg::indexing::macroEdgeSize( neighborFaceGhostLayerSize( level ) ) +
          neighbor * hhg::indexing::macroEdgeSize( neighborCellGhostLayerSize( level ) ) +
          hhg::indexing::macroEdgeIndex( neighborCellGhostLayerSize( level ), x );
}

uint_t indexFromVertexOnNeighborFace( const uint_t& level, const uint_t& x, const uint_t& faceID, const stencilDirection& dir )
{
   typedef stencilDirection sD;
   WALBERLA_ASSERT( dir == sD::VERTEX_W || dir == sD::VERTEX_E );
   switch( dir )
   {
   case sD::VERTEX_W:
      return indexOnNeighborFace( level, x - 1, faceID );
   case sD::VERTEX_E:
      return indexOnNeighborFace( level, x, faceID );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromVertexOnNeighborCell( const uint_t& level, const uint_t& x, const uint_t& cellID, const uint_t& numNeighborFaces )
{
   WALBERLA_ASSERT_GREATER_EQUAL( x, 1, "The 0th edge idx has no cell neighbor." );
   WALBERLA_ASSERT_LESS_EQUAL( x, neighborCellGhostLayerSize( level ) );
   return indexOnNeighborCell( level, x - 1, cellID, numNeighborFaces );
}

uint_t indexFromVertex( const uint_t& level, const uint_t& x, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_C:
      return index( level, x );
   case sD::VERTEX_E:
      return index( level, x + 1 );
   case sD::VERTEX_W:
      return index( level, x - 1 );
   case sD::VERTEX_N:
      return indexFromVertexOnNeighborFace( level, x, 1, sD::VERTEX_E );
   case sD::VERTEX_S:
      return indexFromVertexOnNeighborFace( level, x, 0, sD::VERTEX_W );
   case sD::VERTEX_NW:
      return indexFromVertexOnNeighborFace( level, x, 1, sD::VERTEX_W );
   case sD::VERTEX_SE:
      return indexFromVertexOnNeighborFace( level, x, 0, sD::VERTEX_E );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t stencilIndexOnEdge( const stencilDirection& dir )
{
   typedef stencilDirection sD;
   WALBERLA_ASSERT( dir == sD::VERTEX_C || dir == sD::VERTEX_W || dir == sD::VERTEX_E );
   switch( dir )
   {
   case sD::VERTEX_C:
      return 3;
   case sD::VERTEX_W:
      return 2;
   case sD::VERTEX_E:
      return 4;
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t stencilIndexOnNeighborFace( const stencilDirection& dir, const uint_t& faceID )
{
   typedef stencilDirection sD;
   WALBERLA_ASSERT( dir == sD::VERTEX_W || dir == sD::VERTEX_E );
   if( faceID == 0 )
   {
      switch( dir )
      {
      case sD::VERTEX_W:
         return 0;
      case sD::VERTEX_E:
         return 1;
      default:
         WALBERLA_ABORT( "wrong direction" )
      }
   } else
   {
      switch( dir )
      {
      case sD::VERTEX_W:
         return 3 + 2 * faceID;
      case sD::VERTEX_E:
         return 3 + 2 * faceID + 1;
      default:
         WALBERLA_ABORT( "wrong direction" )
      }
   }
}

uint_t stencilIndexOnNeighborCell( const uint_t& cellID, const uint_t& numNeighborFaces )
{
   return 3 + 2 * numNeighborFaces + cellID;
}

uint_t indexFromHorizontalEdge( const uint_t& level, const uint_t& x, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_W:
      return index( level, x );
   case sD::VERTEX_E:
      return index( level, x + 1 );
   case sD::VERTEX_SE:
      return indexOnNeighborFace( level, x, 0 );
   case sD::VERTEX_NW:
      return indexOnNeighborFace( level, x, 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

Iterator::Iterator( const uint_t& level, const uint_t& offsetToCenter )
: EdgeIterator( levelinfo::num_microvertices_per_edge( level ), offsetToCenter )
{}
} // namespace macroedge

// ##################
// ### Macro Face ###
// ##################

namespace macroface {

uint_t index( const uint_t& level, const uint_t& x, const uint_t& y )
{
   return hhg::indexing::macroFaceIndex( levelinfo::num_microvertices_per_edge( level ), x, y );
}

uint_t innerIndex( const uint_t & level, const uint_t & x, const uint_t & y )
{
  WALBERLA_ASSERT_GREATER( x, 0 );
  WALBERLA_ASSERT_GREATER( y, 0 );
  const uint_t innerWidth = levelinfo::num_microvertices_per_edge( level ) - 3;
  return indexing::macroFaceIndex( innerWidth, x - 1, y - 1 );
}

uint_t index( const uint_t& level, const uint_t& x, const uint_t& y, const uint_t& neighbor )
{
   WALBERLA_ASSERT_LESS_EQUAL( neighbor, 1 );

   return hhg::indexing::macroFaceSize( levelinfo::num_microvertices_per_edge( level ) ) +
          neighbor * hhg::indexing::macroFaceSize( levelinfo::num_microvertices_per_edge( level ) - 1 ) +
          hhg::indexing::macroFaceIndex( levelinfo::num_microvertices_per_edge( level ) - 1, x, y );
}

uint_t indexFromVertex( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_C:
      return index( level, x, y );
   case sD::VERTEX_E:
      return index( level, x + 1, y );
   case sD::VERTEX_W:
      return index( level, x - 1, y );
   case sD::VERTEX_N:
      return index( level, x, y + 1 );
   case sD::VERTEX_S:
      return index( level, x, y - 1 );
   case sD::VERTEX_NW:
      return index( level, x - 1, y + 1 );
   case sD::VERTEX_SE:
      return index( level, x + 1, y - 1 );
   case sD::VERTEX_TC:
      return index( level, x, y, 0 );
   case sD::VERTEX_TW:
      return index( level, x - 1, y, 0 );
   case sD::VERTEX_TS:
      return index( level, x, y - 1, 0 );
   case sD::VERTEX_TSE:
      return index( level, x + 1, y - 1, 0 );
   case sD::VERTEX_TSW:
      return index( level, x - 1, y - 1, 0 );
   case sD::VERTEX_TNW:
      return index( level, x - 1, y + 1, 0 );
   case sD::VERTEX_BC:
      return index( level, x, y, 1 );
   case sD::VERTEX_BN:
      return index( level, x, y + 1, 1 );
   case sD::VERTEX_BS:
      return index( level, x, y - 1, 1 );
   case sD::VERTEX_BE:
      return index( level, x + 1, y, 1 );
   case sD::VERTEX_BW:
      return index( level, x - 1, y, 1 );
   case sD::VERTEX_BSW:
      return index( level, x - 1, y - 1, 1 );
   case sD::VERTEX_BSE:
      return index( level, x + 1, y - 1, 1 );
   case sD::VERTEX_BNW:
      return index( level, x - 1, y + 1, 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromHorizontalEdge( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_W:
      return index( level, x, y );
   case sD::VERTEX_E:
      return index( level, x + 1, y );
   case sD::VERTEX_SE:
      return index( level, x + 1, y - 1 );
   case sD::VERTEX_NW:
      return index( level, x, y + 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromDiagonalEdge( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_SE:
      return index( level, x + 1, y );
   case sD::VERTEX_NE:
      return index( level, x + 1, y + 1 );
   case sD::VERTEX_NW:
      return index( level, x, y + 1 );
   case sD::VERTEX_SW:
      return index( level, x, y );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromVerticalEdge( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_S:
      return index( level, x, y );
   case sD::VERTEX_SE:
      return index( level, x + 1, y );
   case sD::VERTEX_N:
      return index( level, x, y + 1 );
   case sD::VERTEX_NW:
      return index( level, x - 1, y + 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromGrayFace( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_SW:
      return index( level, x, y );
   case sD::VERTEX_SE:
      return index( level, x + 1, y );
   case sD::VERTEX_NW:
      return index( level, x, y + 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

uint_t indexFromBlueFace( const uint_t& level, const uint_t& x, const uint_t& y, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_SE:
      return index( level, x + 1, y );
   case sD::VERTEX_NW:
      return index( level, x, y + 1 );
   case sD::VERTEX_NE:
      return index( level, x + 1, y + 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

bool isVertexOnBoundary( const uint_t& level, const hhg::indexing::Index& idx )
{
   if( idx.row() == 0 )
   {
      return true;
   } else if( idx.col() == 0 )
   {
      return true;
   } else if( ( idx.row() + idx.col() ) == ( hhg::levelinfo::num_microvertices_per_edge( level ) - 1 ) )
   {
      return true;
   } else
   {
      return false;
   }
}

Iterator::Iterator( const uint_t& level, const uint_t& offsetToCenter )
: FaceIterator( levelinfo::num_microvertices_per_edge( level ), offsetToCenter )
{}

BoundaryIterator::BoundaryIterator( const uint_t&                             level,
                                const hhg::indexing::FaceBoundaryDirection& direction,
                                const uint_t&                             offsetToCenter,
                                const uint_t&                             offsetFromVertices )
: FaceBoundaryIterator( levelinfo::num_microvertices_per_edge( level ), direction, offsetToCenter, offsetFromVertices )
{}
} // namespace macroface

// ##################
// ### Macro Cell ###
// ##################

namespace macrocell {

uint_t index( const uint_t& level, const uint_t& x, const uint_t& y, const uint_t& z )
{
   return hhg::indexing::macroCellIndex( levelinfo::num_microvertices_per_edge( level ), x, y, z );
}

uint_t indexFromVertex( const uint_t& level, const uint_t& x, const uint_t& y, const uint_t& z, const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_C:
      return index( level, x, y, z );
   case sD::VERTEX_W:
      return index( level, x - 1, y, z );
   case sD::VERTEX_E:
      return index( level, x + 1, y, z );
   case sD::VERTEX_N:
      return index( level, x, y + 1, z );
   case sD::VERTEX_S:
      return index( level, x, y - 1, z );
   case sD::VERTEX_NW:
      return index( level, x - 1, y + 1, z );
   case sD::VERTEX_SE:
      return index( level, x + 1, y - 1, z );
   case sD::VERTEX_TC:
      return index( level, x, y, z + 1 );
   case sD::VERTEX_TW:
      return index( level, x - 1, y, z + 1 );
   case sD::VERTEX_TS:
      return index( level, x, y - 1, z + 1 );
   case sD::VERTEX_TSE:
      return index( level, x + 1, y - 1, z + 1 );
   case sD::VERTEX_BC:
      return index( level, x, y, z - 1 );
   case sD::VERTEX_BN:
      return index( level, x, y + 1, z - 1 );
   case sD::VERTEX_BE:
      return index( level, x + 1, y, z - 1 );
   case sD::VERTEX_BNW:
      return index( level, x - 1, y + 1, z - 1 );
   default:
      return std::numeric_limits< uint_t >::max();
   }
}

std::set< uint_t > isOnCellFace( const indexing::Index& index, const uint_t& level )
{
   return indexing::isOnCellFace( index, levelinfo::num_microvertices_per_edge( level ) );
}

std::set< uint_t > isOnCellEdge( const indexing::Index& index, const uint_t& level )
{
   return indexing::isOnCellEdge( index, levelinfo::num_microvertices_per_edge( level ) );
}

std::set< uint_t > isOnCellVertex( const indexing::Index& index, const uint_t& level )
{
   return indexing::isOnCellVertex( index, levelinfo::num_microvertices_per_edge( level ) );
}

Iterator::Iterator( const uint_t& level, const uint_t& offsetToCenter )
: CellIterator( levelinfo::num_microvertices_per_edge( level ), offsetToCenter )
{}

BoundaryIterator::BoundaryIterator( const uint_t& level,
                                    const uint_t& vertex0,
                                    const uint_t& vertex1,
                                    const uint_t& vertex2,
                                    const uint_t& offsetToCenter )
: CellBoundaryIterator( levelinfo::num_microvertices_per_edge( level ), vertex0, vertex1, vertex2, offsetToCenter )
{}
} // namespace macrocell

indexing::IndexIncrement logicalIndexOffsetFromVertex( const stencilDirection& dir )
{
   typedef stencilDirection sD;

   switch( dir )
   {
   case sD::VERTEX_C:
      return indexing::IndexIncrement( 0, 0, 0 );
   case sD::VERTEX_W:
      return indexing::IndexIncrement( -1, 0, 0 );
   case sD::VERTEX_E:
      return indexing::IndexIncrement( 1, 0, 0 );
   case sD::VERTEX_N:
      return indexing::IndexIncrement( 0, 1, 0 );
   case sD::VERTEX_S:
      return indexing::IndexIncrement( 0, -1, 0 );
   case sD::VERTEX_NW:
      return indexing::IndexIncrement( -1, 1, 0 );
   case sD::VERTEX_SE:
      return indexing::IndexIncrement( 1, -1, 0 );
   case sD::VERTEX_TC:
      return indexing::IndexIncrement( 0, 0, 1 );
   case sD::VERTEX_TW:
      return indexing::IndexIncrement( -1, 0, 1 );
   case sD::VERTEX_TS:
      return indexing::IndexIncrement( 0, -1, 1 );
   case sD::VERTEX_TSE:
      return indexing::IndexIncrement( 1, -1, 1 );
   case sD::VERTEX_BC:
      return indexing::IndexIncrement( 0, 0, -1 );
   case sD::VERTEX_BN:
      return indexing::IndexIncrement( 0, 1, -1 );
   case sD::VERTEX_BE:
      return indexing::IndexIncrement( 1, 0, -1 );
   case sD::VERTEX_BNW:
      return indexing::IndexIncrement( -1, 1, -1 );
   default:
      WALBERLA_ASSERT( false, "Invalid stencil direction" );
      return indexing::IndexIncrement(
          std::numeric_limits< int >::max(), std::numeric_limits< int >::max(), std::numeric_limits< int >::max() );
   }
}

stencilDirection stencilDirectionFromLogicalOffset( const indexing::IndexIncrement& offset )
{
   typedef stencilDirection         sD;
   typedef indexing::IndexIncrement inc;

   if( offset == inc( 0, 0, 0 ) )
      return sD::VERTEX_C;
   else if( offset == inc( -1, 0, 0 ) )
      return sD::VERTEX_W;
   else if( offset == inc( 1, 0, 0 ) )
      return sD::VERTEX_E;
   else if( offset == inc( 0, 1, 0 ) )
      return sD::VERTEX_N;
   else if( offset == inc( 0, -1, 0 ) )
      return sD::VERTEX_S;
   else if( offset == inc( -1, 1, 0 ) )
      return sD::VERTEX_NW;
   else if( offset == inc( 1, 1, 0 ) )
      return sD::VERTEX_NE;
   else if( offset == inc( -1, -1, 0 ) )
      return sD::VERTEX_SW;
   else if( offset == inc( 1, -1, 0 ) )
      return sD::VERTEX_SE;

   else if( offset == inc( 0, 0, 1 ) )
      return sD::VERTEX_TC;
   else if( offset == inc( -1, 0, 1 ) )
      return sD::VERTEX_TW;
   else if( offset == inc( 1, 0, 1 ) )
      return sD::VERTEX_TE;
   else if( offset == inc( 0, 1, 1 ) )
      return sD::VERTEX_TN;
   else if( offset == inc( 0, -1, 1 ) )
      return sD::VERTEX_TS;
   else if( offset == inc( -1, 1, 1 ) )
      return sD::VERTEX_TNW;
   else if( offset == inc( 1, 1, 1 ) )
      return sD::VERTEX_TNE;
   else if( offset == inc( -1, -1, 1 ) )
      return sD::VERTEX_TSW;
   else if( offset == inc( 1, -1, 1 ) )
      return sD::VERTEX_TSE;

   else if( offset == inc( 0, 0, -1 ) )
      return sD::VERTEX_BC;
   else if( offset == inc( -1, 0, -1 ) )
      return sD::VERTEX_BW;
   else if( offset == inc( 1, 0, -1 ) )
      return sD::VERTEX_BE;
   else if( offset == inc( 0, 1, -1 ) )
      return sD::VERTEX_BN;
   else if( offset == inc( 0, -1, -1 ) )
      return sD::VERTEX_BS;
   else if( offset == inc( -1, 1, -1 ) )
      return sD::VERTEX_BNW;
   else if( offset == inc( 1, 1, -1 ) )
      return sD::VERTEX_BNE;
   else if( offset == inc( -1, -1, -1 ) )
      return sD::VERTEX_BSW;
   else if( offset == inc( 1, -1, -1 ) )
      return sD::VERTEX_BSE;

   WALBERLA_ASSERT( false, "Invaild offset!" );
   return sD::VERTEX_C;
}

uint_t stencilIndexFromVertex( const stencilDirection dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_S:
      return 0;
   case sD::VERTEX_SE:
      return 1;
   case sD::VERTEX_W:
      return 2;
   case sD::VERTEX_C:
      return 3;
   case sD::VERTEX_E:
      return 4;
   case sD::VERTEX_NW:
      return 5;
   case sD::VERTEX_N:
      return 6;
   case sD::VERTEX_NE:
      return 7;
   case sD::VERTEX_SW:
      return 8;
   case sD::VERTEX_TS:
      return 9;
   case sD::VERTEX_TSE:
      return 10;
   case sD::VERTEX_TW:
      return 11;
   case sD::VERTEX_TC:
      return 12;
   case sD::VERTEX_TE:
      return 13;
   case sD::VERTEX_TNW:
      return 14;
   case sD::VERTEX_TN:
      return 15;
   case sD::VERTEX_TNE:
      return 16;
   case sD::VERTEX_TSW:
      return 17;
   case sD::VERTEX_BS:
      return 18;
   case sD::VERTEX_BSE:
      return 19;
   case sD::VERTEX_BW:
      return 20;
   case sD::VERTEX_BC:
      return 21;
   case sD::VERTEX_BE:
      return 22;
   case sD::VERTEX_BNW:
      return 23;
   case sD::VERTEX_BN:
      return 24;
   case sD::VERTEX_BNE:
      return 25;
   case sD::VERTEX_BSW:
      return 26;
   default:
      return std::numeric_limits< size_t >::max();
   }
}

uint_t stencilIndexFromHorizontalEdge( const stencilDirection dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_E:
      return 0;
   case sD::VERTEX_W:
      return 1;
   case sD::VERTEX_SE:
      return 2;
   case sD::VERTEX_NW:
      return 3;
   default:
      return std::numeric_limits< size_t >::max();
   }
}

uint_t stencilIndexFromDiagonalEdge( const stencilDirection dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_SE:
      return 4;
   case sD::VERTEX_NE:
      return 5;
   case sD::VERTEX_NW:
      return 6;
   case sD::VERTEX_SW:
      return 7;
   default:
      return std::numeric_limits< size_t >::max();
   }
}

uint_t stencilIndexFromVerticalEdge( const stencilDirection dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_S:
      return 8;
   case sD::VERTEX_SE:
      return 9;
   case sD::VERTEX_N:
      return 10;
   case sD::VERTEX_NW:
      return 11;
   default:
      return std::numeric_limits< size_t >::max();
   }
}

uint_t stencilIndexFromGrayFace( const stencilDirection& dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_SW:
      return 0;
   case sD::VERTEX_SE:
      return 1;
   case sD::VERTEX_NW:
      return 2;
   default:
      return std::numeric_limits< size_t >::max();
   }
}

uint_t stencilIndexFromBlueFace( const stencilDirection& dir )
{
   typedef stencilDirection sD;
   switch( dir )
   {
   case sD::VERTEX_SE:
      return 0;
   case sD::VERTEX_NW:
      return 1;
   case sD::VERTEX_NE:
      return 2;
   default:
      return std::numeric_limits< size_t >::max();
   }
}
} // namespace vertexdof
} // namespace hhg
