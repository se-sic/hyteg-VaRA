#pragma once

#include "tinyhhg_core/Function.hpp"
#include "tinyhhg_core/types/pointnd.hpp"
#include "tinyhhg_core/petsc/PETScWrapper.hpp"

namespace hhg {

class VertexP1FunctionMemory;
class EdgeP1FunctionMemory;
class FaceP1FunctionMemory;

class P1Function : public Function< P1Function > {
public:
    P1Function(const std::string& name, const std::shared_ptr< PrimitiveStorage > & storage, uint_t minLevel, uint_t maxLevel);

    ~P1Function();

  const PrimitiveDataID<VertexP1FunctionMemory, Vertex> &getVertexDataID() const { return vertexDataID_; }

  const PrimitiveDataID<EdgeP1FunctionMemory, Edge> &getEdgeDataID() const { return edgeDataID_; }

  const PrimitiveDataID<FaceP1FunctionMemory, Face> &getFaceDataID() const { return faceDataID_; }

private:

  /// Interpolates a given expression to a P1Function
  void interpolate_impl(std::function<real_t(const Point3D&)>& expr, uint_t level, DoFType flag = All);

  void assign_impl(const std::vector<walberla::real_t> scalars, const std::vector<P1Function*> functions, uint_t level, DoFType flag = All);

  void add_impl(const std::vector<walberla::real_t> scalars, const std::vector<P1Function*> functions, uint_t level, DoFType flag = All);

  real_t dot_impl(P1Function& rhs, uint_t level, DoFType flag = All);

  void prolongate_impl(uint_t level, DoFType flag = All);

  void prolongateQuadratic_impl(uint_t level, DoFType flag = All);

  void restrict_impl(uint_t level, DoFType flag = All);

  void enumerate_impl(uint_t level, uint_t& num);

#ifdef HHG_BUILD_WITH_PETSC
  void createVectorFromFunction_impl(P1Function &numerator, Vec &vec, uint_t level, DoFType flag);

  void createFunctionFromVector_impl(P1Function &numerator, Vec &vec, uint_t level, DoFType flag);

  void applyDirichletBC_impl(Mat &mat, uint_t level);
#endif



  PrimitiveDataID<VertexP1FunctionMemory, Vertex> vertexDataID_;
  PrimitiveDataID<EdgeP1FunctionMemory, Edge> edgeDataID_;
  PrimitiveDataID<FaceP1FunctionMemory, Face> faceDataID_;
};
}
