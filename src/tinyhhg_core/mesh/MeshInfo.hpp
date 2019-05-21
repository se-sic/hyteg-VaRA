
#pragma once

#include "core/debug/Debug.h"
#include "core/Abort.h"
#include "tinyhhg_core/types/pointnd.hpp"
#include "tinyhhg_core/types/flags.hpp"

#include <array>
#include <map>
#include <set>
#include <vector>

namespace hhg {

using walberla::uint_t;
using walberla::real_t;

/// \brief Contains information about a mesh
/// \author Daniel Drzisga (drzisga@ma.tum.de) \n
///         Nils Kohl (nils.kohl@fau.de)
///         Marcus Mohr (marcus.mohr@lmu.de)
///
/// The \ref MeshInfo class is used to store information about meshes that are
/// either constructed by reading mesh files or generated internally for some
/// standard geometries. It provides static methods to construct meshes by
/// - importing a file in Gmsh format (see method \ref fromGmshFile)
/// - internal mesh generation for rectangles
/// - internal mesh generation for full or partial annuli
/// - internal mesh generation for spherical shells
///
/// \ref MeshInfo instance can then be used to create domains via \ref SetupPrimitiveStorage.
///
/// <b>Details of inline mesh generators for rectangles:</b>
///
/// The inline mesh generator expects to input arguments nx and ny for the discretisation.
/// It supports generation of four different flavours of meshes.
/// - For CRISS, CROSS and CRISSCROSS the rectangle is split into a regular mesh of nx by ny
///   cells, which are then subdivived into two (CRISS and CROSS) or four (CRISSCROSS)
///   triangles.
/// - For DIAMOND we use the same number and position of vertices as for CRISSCROSS, but
///   these are connected in a layered fashion from the outside in.
///
/// | flavour    |       #vertices       | #triangles |
/// |:-----------|:---------------------:|:----------:|
/// | CRISS      | (nx+1)*(ny+1)         | 2*nx*ny    |
/// | CROSS      | (nx+1)*(ny+1)         | 2*nx*ny    |
/// | CRISSCROSS | (nx+1)*(ny+1) + nx*ny | 4*nx*ny    |
/// | DIAMOND    | (nx+1)*(ny+1) + nx*ny | 4*nx*ny    |
///
/*! \htmlonly
  <center>
  <table>
  <tr>
  <td colspan="4" align="center">Sample mesh generated for a rectangle using (nx=3, ny=2)</td>
  </tr>
  <tr>
  <td><img src="../ExtraPics/Mesh_RectangleCriss.png" width="100%"/></td>
  <td><img src="../ExtraPics/Mesh_RectangleCross.png" width="100%"/></td>
  <td><img src="../ExtraPics/Mesh_RectangleCrissCross.png" width="100%"/></td>
  <td><img src="../ExtraPics/Mesh_RectangleDiamond.png" width="100%"/></td>
  </tr>
  <tr>
  <td align="center">CRISS</td>
  <td align="center">CROSS</td>
  <td align="center">CRISSCROSS</td>
  <td align="center">DIAMOND</td>
  </tr>
  </table>
  </center>
  \endhtmlonly
*/
/// <b>Details of inline mesh generators for annuli:</b>
///
/// Meshing of a partial annulus is (conceptually) handled by meshing the correspondig
/// rectangle in cartesian coordinates. In case of a partial annulus this is given by
/// lower left vertex (rhoMin, phiMin) and upper right vertex (rhoMax, phiMax).
/// - For a partial annulus the same four flavours as for rectangles can be specified.
/// - A full annulus is meshed using a CRISSCROSS pattern resulting in
///
/// |              |     #vertices    | #triangles  |
/// |:-------------|:----------------:|:-----------:|
/// | full annulus |  nTan*(2*nRad+1) | 4*nTan*nRad |
///
/*! \htmlonly
  <center>
  <table>
  <tr>
  <td align="center"><img src="../ExtraPics/Mesh_AnnulusPartial.png" width="50%"/></td>
  <td align="center"><img src="../ExtraPics/Mesh_AnnulusFull.png" width="50%"/></td>
  </tr>
  <tr>
  <td align="center">partial annulus (nTan=4, nRad=2)</td>
  <td align="center">full annulus (nTan=15, nRad=2)</td>
  </tr>
  </table>
  </center>
  \endhtmlonly
*/
///
///
/// <b>Details of inline mesh generators for spherical shells:</b>
///
/// This class generates a tetrahedral mesh for a thick spherical shell. It
/// is based on the icosahedral grid approach, i.e. one starts by mapping
/// an icosahedron onto the unit sphere, which results in 20 spherical
/// triangles. Two of these triangles are then conceptually combined resulting
/// in 10 spherical diamonds. These are then further subdivided and the
/// resulting scaled appropriately to obtain radial layers. This leads to
/// a mesh consisting of prismatoidal elements with spherical triangles on
/// top and bottom.
///
/// This class uses the vertices of this mesh and from each prismatoid
/// generates 3 tetrahedrons. Given the following input parameters for the
/// constructor
///
/// | parameter | meaning                                  |
/// |:----------|:-----------------------------------------|
/// | ntan      | number of nodes along a diamond edge     |
/// | nrad      | number of radial layers                  |
/// | rmin      | radius of interior boundary of the shell |
/// | rmax      | radius of exterior boundary of the shell |
///
/// this results in
///
/// - no. of vertices: (10 * (ntan-1) * (ntan-1) + 2) * nrad
/// - no. of tetrahedrons: 60 * (ntan-1) * (ntan-1) * (nrad-1)
///
/*! \htmlonly
     <center>
       <img src="../ExtraPics/ShellMesh-ntan4-nrad3.png"
       width="50%"/><br/>
     Mesh resulting from parameter choice (ntan,nrad,rmin,rmax)=(5,3,1.0,2.0)
     </center>
     \endhtmlonly
*/
///
///
/// We start by generating a mesh for the unit sphere. This mesh is generated
/// by first splitting the four outer arcs of each diamond into (ntan-1)
/// sections of equal arc length and then splitting the west-to-east arcs
/// connecting these new points into sections of equal arc length such that we
/// end up with ntan x ntan nodes on each diamond.
///
/// The thick spherical shell is then meshed by scaling the spherical mesh to
/// obtain nrad radial layers whose radii split the interval [rmin,rmax] into
/// equidistant sub-intervals. Alternatively the radii of the layers can be
/// computed externally and provided to the class via the corresponding
/// constructor.
///
/*! \htmlonly
     <center>
       <img src="../ExtraPics/Diamonds-and-SphericalIndices.png"
       width="50%"/><br/>
     Numbering of diamonds and direction of tangential indices depending on
     hemisphere
     </center>
     \endhtmlonly
*/
///
/*! \htmlonly
     <center>
       <img src="../ExtraPics/Tets-per-local-Cell.png" width="50%"/><br/>
       Splitting a local cell into six tetrahedra
     </center>
     \endhtmlonly
*/
///
/// Every tetrahedron of the mesh can uniquely be addressed by a five-tuple
/// of indices \f$\Big(i_t,i_s^{(1)},i_s^{(2)},i_d,i_r\Big)\f$. These
/// indices have the following meaning an (by our convention) the following
/// ranges:
///
/// |      index       |                           range                 |             indicates              |
/// |:----------------:|:-----------------------------------------------:|:-----------------------------------|
/// | \f$i_t      \f$  | \f$\Big\{ 0, 1, \ldots, 5             \Big\}\f$ | index of tetrahedron in grid cell  |
/// | \f$i_s^{(1)}\f$  | \f$\Big\{ 0, 1, \ldots, n_\text{tan}-1\Big\}\f$ | first spherical node index         |
/// | \f$i_s^{(2)}\f$  | \f$\Big\{ 0, 1, \ldots, n_\text{tan}-1\Big\}\f$ | second spherical node index        |
/// | \f$i_d      \f$  | \f$\Big\{ 0, 1, \ldots, 9             \Big\}\f$ | index of diamond                   |
/// | \f$i_r      \f$  | \f$\Big\{ 0, 1, \ldots, n_\text{rad}-1\Big\}\f$ | index of radial layer (inside-out) |
///
/// We denote by
///
/// \f[ \mathcal{M}_\text{elem} : \Big(i_t,i_s^{(1)},i_s^{(2)},i_d,i_r\Big) \mapsto j_\text{elem} \f]
///
/// the mapping that assigns to each such five-tuple a unique one-dimensional
/// index. We construct the mapping by counting the tetrahedra starting at
/// zero and going through the indices in the given order, with \f$i_t\f$
/// being the fastest running and so on.
/// In a similar fashion each vertex of the grid can be addressed by
/// a four-tuple \f$\Big(i_s^{(1)},i_s^{(2)},i_d,i_r\Big)\f$. Here the indices
/// have an identical meaning as before, but slightly different ranges:
///
/// |      index       |                           range               |             indicates              |
/// |:----------------:|:---------------------------------------------:|:-----------------------------------|
/// | \f$i_s^{(1)}\f$  | \f$\Big\{ 0, 1, \ldots, n_\text{tan}\Big\}\f$ | first spherical node index         |
/// | \f$i_s^{(2)}\f$  | \f$\Big\{ 0, 1, \ldots, n_\text{tan}\Big\}\f$ | second spherical node index        |
/// | \f$i_d      \f$  | \f$\Big\{ 0, 1, \ldots, 9           \Big\}\f$ | index of diamond                   |
/// | \f$i_r      \f$  | \f$\Big\{ 0, 1, \ldots, n_\text{rad}\Big\}\f$ | index of radial layer (inside-out) |
///
/// Additionally the representation of a vertex by such a four-tuple is
/// non-unique. Considering the spherical grid, we see that the north
/// and south pole belong to five diamonds each, while the remaining
/// ten points of the base icosahedron (pentagonal nodes) belong to
/// three diamonds each, and the remaining nodes along a diamond edge
/// always belong to two diamonds. To construct a unique mapping
///
/// \f[ \mathcal{M}_\text{vert} : \Big(i_s^{(1)},i_s^{(2)},i_d,i_r\Big) \mapsto j_\text{vert} \f]
///
/// we introduce the following conventions:
///
/// - The spherical indices of north and south pole are given by (0,0)
/// - A diamond with index \f$i_d\f$ owns all nodes, which satisfy
///   \f{equation*}{\begin{split}
///   i_s^{(1)} &\in \Big\{ 0, 1, \ldots, n_\text{tan}-1\Big\}\\
///   i_s^{(2)} &\in \Big\{ 1, \ldots, n_\text{tan}\Big\}
///   \end{split}\f}
///   on the northern hemisphere this excludes the upper and lower
///   left edge of the diamond.
/// - The above assignment leads to the poles not belonging to any
///   diamond. We assign the north pole to diamond #1 and the south
///   pole to diamond #6.
///
/// The mapping \f$\mathcal{M}_\text{vert}\f$ is then constructed as
/// follows:
///
/// - We first index the north pole on each radial layer, going from
///   \f$i_r=0\f$ up to \f$i_r=n_\text{rad}\f$.
/// - Then we do the same for all south poles.
/// - Then we go through all vertices assigning them indices
///   \f$j_\text{vert}\f$ starting from \f$2\cdot n_\text{rad}\f$.
///   The ordering again follows the given index ordering with,
///   this time, \f$i_s^{(1)}\f$ being the fastest running index.
/*! \htmlonly
     <center>
       <img src="../ExtraPics/tuple2VertIndex.png" width="50%"/><br/>
     Visualisation of vertex ownership convention; vertices marked yellow and
     green are owned by neighbouring diamonds in the indicated direction
     </center>
     \endhtmlonly
*/
///
///
/// \note The inline mesh generators currently set all vertex and edge primitives' boundary flags on the domain boundary to
///       1 and those inside the domain, and of course all face primitives, to 0
class MeshInfo
{
public:

  typedef uint_t IDType;

  typedef enum { CRISS, CROSS, CRISSCROSS, DIAMOND } meshFlavour;

  class Vertex
  {
  public:
    Vertex() : id_( 0 ), coordinates_( Point3D() ), boundaryFlag_( 0 ) {};
    Vertex( const IDType & id, const Point3D & coordinates, const uint_t & boundaryFlag ) :
      id_( id ), coordinates_( coordinates ), boundaryFlag_( boundaryFlag )
    {}

    IDType  getID()           const { return id_; }
    Point3D getCoordinates()  const { return coordinates_; }
    uint_t  getBoundaryFlag() const { return boundaryFlag_; }

  private:
    IDType  id_;
    Point3D coordinates_;
    uint_t  boundaryFlag_;
  };

  class Edge
  {
  public:
    Edge() : boundaryFlag_( 0 ) {};
    Edge( const std::array< IDType, 2 > & vertices, const uint_t & boundaryFlag ) :
      vertices_( vertices ), boundaryFlag_( boundaryFlag )
    {}

    std::array< IDType, 2 > getVertices()     const { return vertices_; }
    uint_t                  getBoundaryFlag() const { return boundaryFlag_; }

  private:
    std::array< IDType, 2 > vertices_;
    uint_t                  boundaryFlag_;
  };

  class Face
  {
  public:
    Face() : boundaryFlag_( 0 ) {};
    Face( const std::vector< IDType > & vertices, const uint_t & boundaryFlag ) :
      vertices_( vertices ), boundaryFlag_( boundaryFlag )
    {}

    std::vector< IDType > getVertices()     const { return vertices_; }
    uint_t                getBoundaryFlag() const { return boundaryFlag_; }

  private:
    std::vector< IDType > vertices_;
    uint_t                boundaryFlag_;
  };

  class Cell
  {
  public:
    Cell() : boundaryFlag_( 0 ) {};
    Cell( const std::vector< IDType > & vertices, const uint_t & boundaryFlag ) :
      vertices_( vertices ), boundaryFlag_( boundaryFlag )
    {}

    std::vector< IDType > getVertices()     const { return vertices_; }
    uint_t                getBoundaryFlag() const { return boundaryFlag_; }

  private:
    std::vector< IDType > vertices_;
    uint_t                boundaryFlag_;
  };


  typedef std::map< IDType,                  Vertex > VertexContainer;
  typedef std::map< std::array< IDType, 2 >, Edge   > EdgeContainer;
  typedef std::map< std::vector< IDType >,   Face   > FaceContainer;
  typedef std::map< std::vector< IDType >,   Cell   > CellContainer;

  /// Construct empty MeshInfo (for testing)
  static MeshInfo emptyMeshInfo() { return MeshInfo(); }

  /// Construct a MeshInfo object from a file in Gmsh format
  static MeshInfo fromGmshFile( const std::string & meshFileName );

  /// Construct a MeshInfo object for a rectangular domain

  /// \param lowerLeft    coordinates of lower left corner of rectangle
  /// \param upperRigth   coordinates of upper right corner of rectangle
  /// \param flavour      meshing strategy (CRISS, CROSS, CRISSCROSS or DIAMOND)
  /// \param nx           (nx+1) gives the number of vertices along the top and bottom edge of the rectangle
  /// \param ny           (ny+1) gives the number of vertices along the left and right edge of the rectangle
  static MeshInfo meshRectangle( const Point2D lowerLeft, const Point2D upperRight, const meshFlavour flavour,
                                 uint_t nx, uint_t ny );

  /// Construct a MeshInfo object for a partial annulus

  /// \param rhoMin       radius of inner circle of partial annulus
  /// \param rhoMax       radius of outer circle of partial annulus
  /// \param phiMin       smaller angle of radial boundary in polar coordinates
  /// \param phiMax       larger angle of radial boundary in polar coordinates
  /// \param flavour      meshing strategy (CRISS, CROSS, CRISSCROSS or DIAMOND)
  /// \param nTan         number of tangential subdivisions (along inner and outer circle)
  /// \param nRad         number of radial subdivisions (along left and right radial boundary)
  static MeshInfo meshAnnulus( const real_t rhoMin, const real_t rhoMax, const real_t phiLeft,
                               const real_t phiRight, const meshFlavour flavour, uint_t nTan, uint_t nRad );

  /// Construct a MeshInfo object for a full annulus
  static MeshInfo meshAnnulus( const real_t rmin, const real_t rmax, uint_t nTan, uint_t nRad );

  /// Constuct a MeshInfo describing a unit cube discretized by 2 * 4^{level} macro-faces
  static MeshInfo meshUnitSquare( uint_t level );

  /// Constructs a MeshInfo object for a spherical shell (equidistant radial layers)
  ///
  /// \param ntan    number of nodes along spherical diamond edge
  /// \param nrad    number of radial layers
  /// \param rmin    radius of innermost shell (core-mantle-boundary)
  /// \param rmax    radius of outermost shell
  static MeshInfo meshSphericalShell( uint_t ntan, uint_t nrad, double rmin, double rmax );

  /// Constructs a MeshInfo object for a spherical shell (externally computed radial layers)
  ///
  /// \param ntan    number of nodes along spherical diamond edge
  /// \param layers  vector that gives the radii of all layers, sorted from the
  ///                CMB outwards
  static MeshInfo meshSphericalShell( uint_t ntan, const std::vector< double > & layers );

  /// Constructs a MeshInfo object for a chain of triangles.
  ///
  /// Starting from the left side, numFaces faces are connected to each other in an alternating fashion
  /// to build a channel-like domain.
  /// There are no inner vertices in this mesh - each face is connected to its two neighbors only.
  /// If numFaces is not even, the channel is not rectangular but a trapezoid.
  ///
  /// \param numFaces number of faces in the mesh
  /// \param width width of the domain
  /// \param height height of the domain
  static MeshInfo meshFaceChain( uint_t numFaces, real_t width, real_t height );

  /// Constructs a MeshInfo object for a chain of triangles with regular size.
  static MeshInfo meshFaceChain( uint_t numFaces );

  /// Construct a MeshInfo object for a rectangular cuboid
  ///
  /// \param lowerLeftFront   coordinates of lower left front corner of cuboid
  /// \param upperRightBack   coordinates of upper right back corner of cuboid
  /// \param nx               (nx+1) gives the number of vertices along cuboid edges in x-direction
  /// \param ny               (ny+1) gives the number of vertices along cuboid edges in y-direction
  /// \param nz               (nz+1) gives the number of vertices along cuboid edges in z-direction
  static MeshInfo meshCuboid( const Point3D lowerLeftFront, const Point3D upperRightBack,
                              uint_t nx, uint_t ny, uint_t nz );

  /// Construct a MeshInfo object for a symmetric, rectangular cuboid.
  /// This version of the cuboid is made up of numCubesX * numCubesY * numCubesZ 24-element-cubes,
  /// and has the following properties:
  /// - point symmetric at the center,
  /// - no edge at the corner points towards its interior.
  ///
  /// \param lowerLeftFront   coordinates of lower left front corner of cuboid
  /// \param upperRightBack   coordinates of upper right back corner of cuboid
  /// \param numCubesX        gives the number of 24-element cubes in x-direction
  /// \param numCubesY        gives the number of 24-element cubes in y-direction
  /// \param numCubesZ        gives the number of 24-element cubes in z-direction
  static MeshInfo meshSymmetricCuboid( const Point3D lowerLeftFront, const Point3D upperRightBack,
                                       uint_t numCubesX, uint_t numCubesY, uint_t numCubesZ );

  /// Returns vertices of the mesh
  const VertexContainer & getVertices() const { return vertices_; };

  /// Returns edges of the mesh
  const EdgeContainer & getEdges() const { return edges_; };

  /// Returns faces of the mesh
  const FaceContainer & getFaces() const { return faces_; }

  /// Returns cells of the mesh
  const CellContainer & getCells() const { return cells_; }

private:

  MeshInfo() {};

  /// Adds edge in ascending index order and performs checks
  void addEdge( const Edge & edge );

  /// Adds face in ascending index order and performs checks
  void addFace( const Face & face );

  /// Adds cell and all edges and faces
  void addCellAndAllEdgesAndFaces( const Cell & cell );

  /// Construct a MeshInfo for a rectangular domain using diamond approach
  static MeshInfo meshRectangleDiamond( const Point2D lowerLeft, const Point2D upperRight, uint_t nx, uint_t ny );

  /// Derive information on edges from vertices and faces (for rectangles)

  /// This method is used in the 2D inline mesh generators for rectangles. The latter
  /// provide only information on vertices and faces. The information on the edges is
  /// derived from the faces, as each face has three edges.
  /// \param lowerLeft   lower left vertex of rectangle
  /// \param upperRight  upper right vertex of rectangle
  /// \param tol         parameter used to determine, whether an edge is part of the boundary, or not
  void deriveEdgesForRectangles( const Point2D lowerLeft, const Point2D upperRight, real_t tol );

  /// Derive information on edges from vertices and faces (for full annulus)

  /// This method is used in the 2D inline mesh generator for the full annulus. The latter
  /// provides only information on vertices and faces. The information on the edges is then
  /// derived from the faces, as each face has three edges.
  /// \param minTol  parameter used to determine, whether an edge is part of the inner boundary, or not
  /// \param maxTol  parameter used to determine, whether an edge is part of the outer boundary, or not
  void deriveEdgesForFullAnnulus( real_t minTol, real_t maxTol );

  VertexContainer vertices_;
  EdgeContainer   edges_;
  FaceContainer   faces_;
  CellContainer   cells_;

};

}
