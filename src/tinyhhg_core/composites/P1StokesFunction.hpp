
#pragma once

#include "tinyhhg_core/p1functionspace/P1Function.hpp"
#include "tinyhhg_core/FunctionProperties.hpp"

namespace hyteg {

template <typename ValueType>
class P1StokesFunction
{
public:

  typedef ValueType valueType;

  template< typename VType >
  using FunctionType = P1StokesFunction< VType >;

  typedef P1Function< ValueType > VelocityFunction_T;
  typedef P1Function< ValueType > PressureFunction_T;
  typedef typename FunctionTrait< P1StokesFunction< ValueType > >::Tag Tag;

    P1StokesFunction(const std::string& _name, const std::shared_ptr< PrimitiveStorage > & storage, size_t minLevel, size_t maxLevel)
    : u(_name+"_u", storage, minLevel, maxLevel),
      v(_name+"_v", storage, minLevel, maxLevel),
      w( storage->hasGlobalCells() ? P1Function< ValueType >( _name+"_w", storage, minLevel, maxLevel ) :  P1Function< ValueType >( _name+"_w_dummy", storage )),
      p(_name+"_p", storage, minLevel, maxLevel, BoundaryCondition::createAllInnerBC() )
  {
  }

  std::shared_ptr< PrimitiveStorage > getStorage() const { return u.getStorage(); }

  bool isDummy() const { return false; }

  void interpolate(const std::function<real_t(const hyteg::Point3D&)>& expr, size_t level, DoFType flag = All) const
  {
    u.interpolate(expr, level, flag);
    v.interpolate(expr, level, flag);
    w.interpolate(expr, level, flag);
    p.interpolate(expr, level, flag);
  }

  void interpolate( const real_t& constant, size_t level, DoFType flag = All ) const
  {
     u.interpolate( constant, level, flag );
     v.interpolate( constant, level, flag );
     w.interpolate( constant, level, flag );
     p.interpolate( constant, level, flag );
  }

  void swap( const P1StokesFunction< ValueType > & other,
             const uint_t & level,
             const DoFType & flag = All ) const
  {
    u.swap( other.u, level, flag );
    v.swap( other.v, level, flag );
    w.swap( other.w, level, flag );
    p.swap( other.p, level, flag );
  }

  void assign( const std::vector< walberla::real_t >                                               scalars,
               const std::vector< std::reference_wrapper< const P1StokesFunction< ValueType > > >& functions,
               size_t                                                                              level,
               DoFType                                                                             flag = All ) const
  {
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_u;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_v;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_w;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_p;

     for( const P1StokesFunction< ValueType >& function : functions )
     {
        functions_u.push_back( function.u );
        functions_v.push_back( function.v );
        functions_w.push_back( function.w );
        functions_p.push_back( function.p );
     }

     u.assign( scalars, functions_u, level, flag );
     v.assign( scalars, functions_v, level, flag );
     w.assign( scalars, functions_w, level, flag );
     p.assign( scalars, functions_p, level, flag );
  }

  void add( const std::vector< walberla::real_t >                                               scalars,
            const std::vector< std::reference_wrapper< const P1StokesFunction< ValueType > > >& functions,
            size_t                                                                              level,
            DoFType                                                                             flag = All ) const
  {
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_u;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_v;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_w;
     std::vector< std::reference_wrapper< const P1Function< ValueType > > > functions_p;

     for( const P1StokesFunction< ValueType >& function : functions )
     {
        functions_u.push_back( function.u );
        functions_v.push_back( function.v );
        functions_w.push_back( function.w );
        functions_p.push_back( function.p );
     }

     u.add( scalars, functions_u, level, flag );
     v.add( scalars, functions_v, level, flag );
     w.add( scalars, functions_w, level, flag );
     p.add( scalars, functions_p, level, flag );
  }

  walberla::real_t dotGlobal(const P1StokesFunction<ValueType>& rhs,const uint_t level,const DoFType flag = All) const
  {
    walberla::real_t sum = u.dotLocal(rhs.u, level, flag);
    sum += v.dotLocal(rhs.v, level, flag);
    sum += w.dotLocal(rhs.w, level, flag);
    sum += p.dotLocal(rhs.p, level, flag);
    walberla::mpi::allReduceInplace( sum, walberla::mpi::SUM, walberla::mpi::MPIManager::instance()->comm() );
    return sum;
  }

  void enableTiming( const std::shared_ptr< walberla::WcTimingTree > & timingTree )
  {
    u.enableTiming(timingTree);
    v.enableTiming(timingTree);
    w.enableTiming(timingTree);
    p.enableTiming(timingTree);
  }

  void enumerate( uint_t level )
  {
    uint_t counterVertexDoFs = hyteg::numberOfLocalDoFs< Tag >( *( u.getStorage() ), level );

    std::vector< uint_t > vertexDoFsPerRank = walberla::mpi::allGather( counterVertexDoFs );

    ValueType offset = 0;

    for( uint_t i = 0; i < uint_c( walberla::MPIManager::instance()->rank() ); ++i )
    {
      offset += static_cast< ValueType >( vertexDoFsPerRank[i] );
    }

    u.enumerate( level, offset );
    v.enumerate( level, offset );
    w.enumerate( level, offset );
    p.enumerate( level, offset );
  }

  P1Function< ValueType > u;
  P1Function< ValueType > v;
  P1Function< ValueType > w;
  P1Function< ValueType > p;
};

}

