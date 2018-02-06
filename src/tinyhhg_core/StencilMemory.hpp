
#pragma once

#include "tinyhhg_core/FunctionMemory.hpp"

namespace hhg {

template< typename ValueType >
using StencilMemory = FunctionMemory< ValueType >;

template< typename DataType, typename PrimitiveType >
using StencilMemoryDataHandling = FunctionMemoryDataHandling< DataType, PrimitiveType >;

}