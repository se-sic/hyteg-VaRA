
#pragma once

#include "tinyhhg_core/composites/P2P1TaylorHoodFunction.hpp"
#include "tinyhhg_core/gridtransferoperators/P2toP2QuadraticProlongation.hpp"
#include "tinyhhg_core/gridtransferoperators/P1toP1LinearProlongation.hpp"

namespace hhg {

class P2P1StokesToP2P1StokesProlongation
{
public:

    typedef P2toP2QuadraticProlongation VelocityProlongation_T;
    typedef P1toP1LinearProlongation    PressureProlongation_T;

    void operator() ( const P2P1TaylorHoodFunction< real_t > & function, const uint_t & sourceLevel, const DoFType & flag )
    {
      quadraticProlongationOperator_( function.u, sourceLevel, flag );
      quadraticProlongationOperator_( function.v, sourceLevel, flag );
      linearProlongationOperator_   ( function.p, sourceLevel, flag | DirichletBoundary );
    }

private:

    P2toP2QuadraticProlongation quadraticProlongationOperator_;
    P1toP1LinearProlongation    linearProlongationOperator_;

};
}