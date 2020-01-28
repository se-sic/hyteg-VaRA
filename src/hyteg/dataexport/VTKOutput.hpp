/*
 * Copyright (c) 2017-2019 Dominik Thoennes, Marcus Mohr, Nils Kohl.
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

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "hyteg/dgfunctionspace/DGFunction.hpp"
#include "hyteg/edgedofspace/EdgeDoFFunction.hpp"
#include "hyteg/p2functionspace/P2Function.hpp"
#include "hyteg/p1functionspace/P1Function.hpp"
#include "hyteg/composites/P1StokesFunction.hpp"
#include "hyteg/composites/P2P1TaylorHoodFunction.hpp"

#include "core/DataTypes.h"

namespace hyteg {

using walberla::real_c;
using walberla::real_t;
using walberla::uint64_t;
using walberla::uint_c;
using walberla::uint_t;

class PrimitiveStorage;

class VTKOutput
{
 public:
   ///
   /// \param dir             Directory where the files are stored
   /// \param filename        Basename of the vtk files
   /// \param storage         PrimitiveStorage containing the functions
   /// \param writeFrequency  Specifies the frequency of the VTK output see write()
   VTKOutput( std::string                                dir,
              std::string                                filename,
              const std::shared_ptr< PrimitiveStorage >& storage,
              const uint_t&                              writeFrequency = 1 );

   void add( P1Function< real_t > function );
   void add( EdgeDoFFunction< real_t > function );
   void add( DGFunction< real_t > function );

   void add( P2Function< real_t > function );

   void add( P1StokesFunction< real_t > function );
   void add( P2P1TaylorHoodFunction< real_t > function );

   /// Writes the VTK output only if writeFrequency > 0 and timestep % writeFrequency == 0.
   /// Therefore always writes output if timestep is 0.
   /// Appends the time step to the filename.
   /// Note: files will be overwritten if called twice with the same time step!
   void write( const uint_t& level, const uint_t& timestep = 0 ) const;

 private:
   enum class DoFType
   {
      VERTEX,
      EDGE_X,
      EDGE_Y,
      EDGE_Z,
      EDGE_XY,
      EDGE_XZ,
      EDGE_YZ,
      EDGE_XYZ,
      DG,
      P2
   };

  enum class VTK_DATA_FORMAT { ASCII, BINARY, APPENDED };

   static const std::map< VTKOutput::DoFType, std::string > DoFTypeToString_;

   void   writeDoFByType( std::ostream& output, const uint_t& level, const VTKOutput::DoFType& dofType ) const;
   uint_t getNumRegisteredFunctions( const VTKOutput::DoFType& dofType ) const;

   void writeP1( std::ostream& output, const uint_t& level ) const;
   void writeEdgeDoFs( std::ostream& output, const uint_t& level, const VTKOutput::DoFType& dofType ) const;
   void writeDGDoFs( std::ostream& output, const uint_t& level ) const;
   void writeP2( std::ostream& output, const uint_t& level ) const;

   std::string fileNameExtension( const VTKOutput::DoFType& dofType, const uint_t& level, const uint_t& timestep ) const;

   void writeHeader( std::ostringstream& output, const uint_t& numberOfPoints, const uint_t& numberOfCells ) const;
   void writeFooterAndFile( std::ostringstream& output, const std::string& completeFilePath ) const;

   void writePointsForMicroVertices( std::ostream&                              output,
                                     const std::shared_ptr< PrimitiveStorage >& storage,
                                     const uint_t&                              level ) const;
   void writePointsForMicroEdges( std::ostream&                              output,
                                  const std::shared_ptr< PrimitiveStorage >& storage,
                                  const uint_t&                              level,
                                  const VTKOutput::DoFType&                  dofType ) const;

   void writeVertexDoFData( std::ostream&                                 output,
                            const vertexdof::VertexDoFFunction< real_t >& function,
                            const std::shared_ptr< PrimitiveStorage >&    storage,
                            const uint_t&                                 level ) const;
   void writeEdgeDoFData( std::ostream&                              output,
                          const EdgeDoFFunction< real_t >&           function,
                          const std::shared_ptr< PrimitiveStorage >& storage,
                          const uint_t&                              level,
                          const DoFType&                             dofType ) const;

   void writeCells2D( std::ostream& output, const std::shared_ptr< PrimitiveStorage >& storage, const uint_t& faceWidth ) const;
   void writeCells3D( std::ostream& output, const std::shared_ptr< PrimitiveStorage >& storage, const uint_t& level ) const;

   void syncAllFunctions( const uint_t& level ) const;

   void openDataElement( std::ostream& output, const std::string& type, const std::string& name,
                         const uint_t nComponents, const VTK_DATA_FORMAT fmt ) const;

   /// Writes only macro-faces.
   void set2D() { write2D_ = true; }
   /// Writes only macro-cells.
   void set3D() { write2D_ = false; }

   std::string dir_;
   std::string filename_;

   const std::string defaultFMT_ = "format=\"ascii\"";

   uint_t writeFrequency_;

   bool write2D_;

   std::vector< P1Function< real_t > >      p1Functions_;
   std::vector< EdgeDoFFunction< real_t > > edgeDoFFunctions_;
   std::vector< DGFunction< real_t > >      dgFunctions_;

   std::vector< P2Function< real_t > > p2Functions_;
};

} // namespace hyteg