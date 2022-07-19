/*
 * Copyright (c) 2022 Daniel Bauer.
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

#include "hyteg/boundary/BoundaryConditions.hpp"
#include "hyteg/edgedofspace/EdgeDoFFunction.hpp"
#include "hyteg/functions/VectorFunction.hpp"
#include "hyteg/memory/FunctionMemory.hpp"
#include "hyteg/sparseassembly/VectorProxy.hpp"

#include "Eigen/Dense"

namespace hyteg {
namespace n1e1 {

template < typename ValueType >
class N1E1VectorFunction final : public VectorFunction< N1E1VectorFunction< ValueType > >
{
 public:
   using valueType  = ValueType;
   using VectorType = Eigen::Matrix< ValueType, 3, 1 >;

   template < typename VType >
   using FunctionType = N1E1VectorFunction< VType >;

   N1E1VectorFunction( const std::string&                         name,
                       const std::shared_ptr< PrimitiveStorage >& storage,
                       const uint_t&                              minLevel,
                       const uint_t&                              maxLevel );

   N1E1VectorFunction( const std::string&                         name,
                       const std::shared_ptr< PrimitiveStorage >& storage,
                       const uint_t&                              minLevel,
                       const uint_t&                              maxLevel,
                       const BoundaryCondition&                   boundaryCondition );

   virtual uint_t getDimension() const { return 3; }

   inline void swap( const N1E1VectorFunction< ValueType >& other, const uint_t& level, const DoFType& flag = All )
   {
      dofs_->swap( *other.getDoFs(), level, flag );
   }

   /// \brief Copies all values function data from other to this.
   ///
   /// This method can be used safely if the other function is located on a different PrimitiveStorage.
   inline void copyFrom( const N1E1VectorFunction< ValueType >& other, const uint_t& level ) const
   {
      dofs_->copyFrom( *other.getDoFs(), level );
   }

   /// \brief Copies all values function data from other to this.
   ///
   /// This method can be used safely if the other function is located on a different PrimitiveStorage.
   /// This method also works, if the storages are distributed differently.
   ///
   /// \param other another function
   /// \param level the refinement level
   /// \param localPrimitiveIDsToRank Map that contains as keys all primitive IDs of all primitives that are local regarding the
   ///                                storage of this function, and as values the MPI ranks of the processes that own these
   ///                                primitives regarding the storage of the other function
   /// \param otherPrimitiveIDsToRank Map that contains as keys all primitive IDs of all primitives that are local regarding the
   ///                                storage of the other function, and as values the MPI ranks of the processes that own these
   ///                                primitives regarding the storage this function lives on.
   ///
   inline void copyFrom( const N1E1VectorFunction< ValueType >&         other,
                         const uint_t&                                  level,
                         const std::map< PrimitiveID::IDType, uint_t >& localPrimitiveIDsToRank,
                         const std::map< PrimitiveID::IDType, uint_t >& otherPrimitiveIDsToRank )
   {
      dofs_->copyFrom( *other.getDoFs(), level, localPrimitiveIDsToRank, otherPrimitiveIDsToRank );
   }

   /// \brief Evaluate finite element function at specific coordinates.
   ///
   /// In a parallel setting, the specified coordinate might not lie in the local subdomain.
   ///
   /// Evaluation is performed in two steps:
   ///
   ///   1. For all volume primitives of the local subdomain:
   ///      If a point-tet (point-triangle in 2D) inclusion test succeeds, the function returns true
   ///      and the finite-element function is evaluated.
   ///
   ///   2. Skipped, if radius is negative.
   ///      For all volume primitives of the local subdomain:
   ///      A sphere-tet (circle-triangle) intersection
   ///      test is performed, if successful returns true, and the finite-element function is extrapolated
   ///      to the specified coordinate and evaluated, depending on the radius, this might introduce (large) errors.
   ///
   /// If both tests fail, this function returns false, and no evaluation is performed (i.e. the returned, evaluated
   /// value is not set to anything meaningful).
   ///
   /// Note that two parallel processes that return true, may return _different_ values.
   ///
   /// No communication is performed in this function.
   /// -> Does not need to be called collectively.
   /// -> Different values are returned on each process.
   ///
   /// \param coordinates where the function shall be evaluated
   /// \param level refinement level
   /// \param value function value at the coordinate if search was successful
   /// \param searchToleranceRadius radius of the sphere (circle) for the second search phase, skipped if negative
   /// \return true if the function was evaluated successfully, false otherwise
   ///
   bool evaluate( const Point3D& coordinates, uint_t level, VectorType& value, real_t searchToleranceRadius = 1e-05 ) const;

   void assign( const std::vector< ValueType >&                                                       scalars,
                const std::vector< std::reference_wrapper< const N1E1VectorFunction< ValueType > > >& functions,
                uint_t                                                                                level,
                DoFType                                                                               flag = All ) const;

   void add( VectorType vector, uint_t level, DoFType flag = All ) const;

   void add( const std::vector< ValueType >&                                                       scalars,
             const std::vector< std::reference_wrapper< const N1E1VectorFunction< ValueType > > >& functions,
             uint_t                                                                                level,
             DoFType                                                                               flag = All ) const;

   /// @name Member functions for interpolation using BoundaryUID flags
   //@{
   void interpolate( VectorType constant, uint_t level, BoundaryUID boundaryUID ) const;

   void interpolate( const std::function< VectorType( const Point3D& ) >& expr, uint_t level, BoundaryUID boundaryUID ) const;

   void interpolate( const std::function< VectorType( const Point3D&, const std::vector< VectorType >& ) >& expr,
                     const std::vector< std::reference_wrapper< const N1E1VectorFunction< ValueType > > >&  srcFunctions,
                     uint_t                                                                                 level,
                     BoundaryUID                                                                            boundaryUID ) const;
   //@}

   /// @name Member functions for interpolation using DoFType flags
   //@{
   void interpolate( VectorType constant, uint_t level, DoFType flag = All ) const;

   void interpolate( const std::function< VectorType( const Point3D& ) >& expr, uint_t level, DoFType flag = All ) const;

   void interpolate( const std::function< VectorType( const Point3D&, const std::vector< VectorType >& ) >& expr,
                     const std::vector< std::reference_wrapper< const N1E1VectorFunction< ValueType > > >&  srcFunctions,
                     uint_t                                                                                 level,
                     DoFType                                                                                flag = All ) const;

   void interpolate( const std::vector< std::function< VectorType( const Point3D& ) > >& expr,
                     uint_t                                                              level,
                     DoFType                                                             flag = All ) const
   {
      WALBERLA_ASSERT_EQUAL( expr.size(), 1 );
      this->interpolate( expr[0], level, flag );
   };
   //@}

   /// Compute the product of several functions in an elementwise fashion
   ///
   /// The method takes as input a collection of functions. These are multiplied together in an elementwise fashion.
   /// The latter is to be understood not in a FE context, but in the sense of element-wise operators in matrix/array
   /// oriented languages, i.e. the product is a function of the same type as the inputs and its DoFs are formed as
   /// product of the corresponding DoFs of the input functions. The result is stored in the function object on which
   /// the method is invoked, overwritting its contents. It is safe, if the destination function is part of the product.
   ///
   /// \param functions  the functions forming the product
   /// \param level      level on which the multiplication should be computed
   /// \param flag       marks those primitives which are partaking in the computation of the product
   //void multElementwise( const std::vector< std::reference_wrapper< const N1E1VectorFunction< ValueType > > >& functions,
   //                      uint_t                                                                                   level,
   //                      DoFType flag = All ) const;

   /// Replace values of the function by their inverses in an elementwise fashion
   //void invertElementwise( uint_t level, DoFType flag = All, bool workOnHalos = false ) const;

   //ValueType dotLocal( const N1E1VectorFunction< ValueType >& secondOp, const uint_t level, const DoFType flag = All ) const;

   /// @name Unimplemented methods (only dummys for inheritance)
   /// @{
   //ValueType dotGlobal( const N1E1VectorFunction< ValueType >&, uint_t, DoFType ) const {
   //    WALBERLA_ABORT( "N1E1VectorFunction::dotGlobal not implemented!" ) } /// @}

   /// Set all function DoFs to zero including the ones in the halos
   inline void setToZero( const uint_t level ) const { dofs_->setToZero( level ); }

   inline void enumerate( uint_t level ) const { dofs_->enumerate( level ); }

   inline void enumerate( uint_t level, ValueType& offset ) const { dofs_->enumerate( level, offset ); }

   inline std::shared_ptr< EdgeDoFFunction< ValueType > > getDoFs() const { return dofs_; }

   inline BoundaryCondition getBoundaryCondition() const { return boundaryCondition_; }
   inline void              setBoundaryCondition( BoundaryCondition bc )
   {
      boundaryCondition_ = bc;
      // TODO set on dofs_
   }

   template < typename OtherFunctionValueType >
   inline void copyBoundaryConditionFromFunction( const N1E1VectorFunction< OtherFunctionValueType >& other )
   {
      dofs_->copyBoundaryConditionFromFunction( *other->getDoFs() );
   }

   template < typename SenderType, typename ReceiverType >
   inline void startCommunication( const uint_t& level ) const
   {
      communicators_.at( level )->template startCommunication< SenderType, ReceiverType >();
   }

   template < typename SenderType, typename ReceiverType >
   inline void endCommunication( const uint_t& level ) const
   {
      communicators_.at( level )->template endCommunication< SenderType, ReceiverType >();
   }

   template < typename SenderType, typename ReceiverType >
   inline void communicate( const uint_t& level ) const
   {
      startCommunication< SenderType, ReceiverType >( level );
      endCommunication< SenderType, ReceiverType >( level );
   }

   /// Sets the communication mode that is used between primitives that belong to the same process. Normally this is only needed
   /// for debugging. See communication::BufferedCommunicator::LocalCommunicationMode for the available options
   /// \param localCommunicationMode
   void setLocalCommunicationMode( const communication::BufferedCommunicator::LocalCommunicationMode& localCommunicationMode );

   /// conversion to/from linear algebra representation
   /// @{
   inline void toVector( const N1E1VectorFunction< idx_t >&    numerator,
                         const std::shared_ptr< VectorProxy >& vec,
                         uint_t                                level,
                         DoFType                               flag ) const
   {
      dofs_->toVector( *numerator.getDoFs(), vec, level, flag );
   }

   inline void fromVector( const N1E1VectorFunction< idx_t >&    numerator,
                           const std::shared_ptr< VectorProxy >& vec,
                           uint_t                                level,
                           DoFType                               flag ) const
   {
      dofs_->fromVector( *numerator.getDoFs(), vec, level, flag );
   }
   /// @}

 private:
   using VectorFunction< N1E1VectorFunction< ValueType > >::communicators_;
   using VectorFunction< N1E1VectorFunction< ValueType > >::additiveCommunicators_;

   std::shared_ptr< PrimitiveStorage >             storage_;
   std::shared_ptr< EdgeDoFFunction< ValueType > > dofs_;
   BoundaryCondition                               boundaryCondition_;
};

template <>
bool N1E1VectorFunction< real_t >::evaluate( const Point3D& coordinates,
                                             uint_t         level,
                                             VectorType&    value,
                                             real_t         searchToleranceRadius ) const;

template <>
void N1E1VectorFunction< real_t >::add( VectorType vector, uint_t level, DoFType flag ) const;

template <>
void N1E1VectorFunction< real_t >::interpolate( VectorType constant, uint_t level, BoundaryUID boundaryUID ) const;

template <>
void N1E1VectorFunction< real_t >::interpolate(
    const std::function< VectorType( const Point3D&, const std::vector< VectorType >& ) >& expr,
    const std::vector< std::reference_wrapper< const N1E1VectorFunction< real_t > > >&     srcFunctions,
    uint_t                                                                                 level,
    BoundaryUID                                                                            boundaryUID ) const;

template <>
void N1E1VectorFunction< real_t >::interpolate( VectorType constant, uint_t level, DoFType flag ) const;

template <>
void N1E1VectorFunction< real_t >::interpolate(
    const std::function< VectorType( const Point3D&, const std::vector< VectorType >& ) >& expr,
    const std::vector< std::reference_wrapper< const N1E1VectorFunction< real_t > > >&     srcFunctions,
    uint_t                                                                                 level,
    DoFType                                                                                flag ) const;

} // namespace n1e1
} // namespace hyteg
