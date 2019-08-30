
#include "tinyhhg_core/p1functionspace/VertexDoFIndexing.hpp"
#include "tinyhhg_core/indexing/Common.hpp"
#include "tinyhhg_core/HHGDefinitions.hpp"

#include "core/mpi/all.h"
#include "core/debug/CheckFunctions.h"
#include "core/logging/Logging.h"


namespace hyteg {

using indexing::Index;

void testNeighborhood2( const Index & index, const std::map< stencilDirection, uint_t > & dirToLinearIndex )
{
  const uint_t level = 2;
  for ( const auto & it : dirToLinearIndex )
  {
    const auto dir         = it.first;
    const auto linearIndex = it.second;
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, index.x(), index.y(), index.z(), dir ), linearIndex );
  }
}

void testNeighborhood3( const Index & index, const std::map< stencilDirection, uint_t > & dirToLinearIndex )
{
  const uint_t level = 3;
  for ( const auto & it : dirToLinearIndex )
  {
    const auto dir         = it.first;
    const auto linearIndex = it.second;
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, index.x(), index.y(), index.z(), dir ), linearIndex );
  }
}

static void testVertexDofMacroCellIndexing()
{
  typedef stencilDirection sd;

  if ( globalDefines::useP1Coloring )
  {
    std::map< sd, uint_t > level2Center;

    level2Center[sd::VERTEX_C] = 34;

    testNeighborhood2( Index( 1, 1, 1 ), level2Center );

    uint_t level = 2;

    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 0, 0, 0, sd::VERTEX_C ), 0 );
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 2, 0, 0, sd::VERTEX_C ), 1 );
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 4, 0, 0, sd::VERTEX_C ), 2 );
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 0, 2, 0, sd::VERTEX_C ), 3 );
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 2, 2, 0, sd::VERTEX_C ), 4 );
    WALBERLA_CHECK_EQUAL( vertexdof::macrocell::indexFromVertex( level, 0, 4, 0, sd::VERTEX_C ), 5 );
  }
  else
  {
    std::map< sd, uint_t > level2Center;

    level2Center[sd::VERTEX_C] = 20;
    level2Center[sd::VERTEX_E] = 21;
    level2Center[sd::VERTEX_W] = 19;
    level2Center[sd::VERTEX_N] = 23;
    level2Center[sd::VERTEX_S] = 16;

    level2Center[sd::VERTEX_NW] = 22;
    level2Center[sd::VERTEX_SE] = 17;

    level2Center[sd::VERTEX_TC] = 29;
    level2Center[sd::VERTEX_TW] = 28;
    level2Center[sd::VERTEX_TS] = 26;
    level2Center[sd::VERTEX_TSE] = 27;

    level2Center[sd::VERTEX_BC] = 6;
    level2Center[sd::VERTEX_BE] = 7;
    level2Center[sd::VERTEX_BN] = 10;
    level2Center[sd::VERTEX_BNW] = 9;

    testNeighborhood2( Index( 1, 1, 1 ), level2Center );

    std::map< sd, uint_t > level3FirstInner;

    level3FirstInner[sd::VERTEX_C] = 54;
    level3FirstInner[sd::VERTEX_E] = 55;
    level3FirstInner[sd::VERTEX_W] = 53;
    level3FirstInner[sd::VERTEX_N] = 61;
    level3FirstInner[sd::VERTEX_S] = 46;

    level3FirstInner[sd::VERTEX_NW] = 60;
    level3FirstInner[sd::VERTEX_SE] = 47;

    level3FirstInner[sd::VERTEX_TC] = 89;
    level3FirstInner[sd::VERTEX_TW] = 88;
    level3FirstInner[sd::VERTEX_TS] = 82;
    level3FirstInner[sd::VERTEX_TSE] = 83;

    level3FirstInner[sd::VERTEX_BC] = 10;
    level3FirstInner[sd::VERTEX_BE] = 11;
    level3FirstInner[sd::VERTEX_BN] = 18;
    level3FirstInner[sd::VERTEX_BNW] = 17;

    testNeighborhood3( Index( 1, 1, 1 ), level3FirstInner );

    std::map< sd, uint_t > level3TopInner;

    level3TopInner[sd::VERTEX_C] = 150;
    level3TopInner[sd::VERTEX_E] = 151;
    level3TopInner[sd::VERTEX_W] = 149;
    level3TopInner[sd::VERTEX_N] = 153;
    level3TopInner[sd::VERTEX_S] = 146;

    level3TopInner[sd::VERTEX_NW] = 152;
    level3TopInner[sd::VERTEX_SE] = 147;

    level3TopInner[sd::VERTEX_TC] = 159;
    level3TopInner[sd::VERTEX_TW] = 158;
    level3TopInner[sd::VERTEX_TS] = 156;
    level3TopInner[sd::VERTEX_TSE] = 157;

    level3TopInner[sd::VERTEX_BC] = 136;
    level3TopInner[sd::VERTEX_BE] = 137;
    level3TopInner[sd::VERTEX_BN] = 140;
    level3TopInner[sd::VERTEX_BNW] = 139;

    testNeighborhood3( Index( 1, 1, 5 ), level3TopInner );

  }

  // checking the index at vertex/edge/face functions
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 0, 0, 0 ), 2 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 0, 0, 0 ), 3 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 0, 0, 0 ), 4 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 8, 0, 0 ), 3 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 7, 0, 0 ), 3 ).size(), 2 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 0, 7, 0 ), 3 ).size(), 2 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellFace( indexing::Index( 1, 1, 1 ), 3 ).size(), 0 );

  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 0, 0, 0 ), 2 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 0, 0, 0 ), 3 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 0, 0, 0 ), 4 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 8, 0, 0 ), 3 ).size(), 3 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 7, 0, 0 ), 3 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 0, 7, 0 ), 3 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellEdge( indexing::Index( 1, 1, 1 ), 3 ).size(), 0 );

  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 0, 0, 0 ), 2 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 0, 0, 0 ), 3 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 0, 0, 0 ), 4 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 8, 0, 0 ), 3 ).size(), 1 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 7, 0, 0 ), 3 ).size(), 0 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 0, 7, 0 ), 3 ).size(), 0 );
  WALBERLA_CHECK_EQUAL( vertexdof::macrocell::isOnCellVertex( indexing::Index( 1, 1, 1 ), 3 ).size(), 0 );
}

}

int main(int argc, char* argv[])
{
  walberla::mpi::Environment walberlaEnv(argc, argv);
  walberla::MPIManager::instance()->useWorldComm();
  hyteg::testVertexDofMacroCellIndexing();
}

