add_subdirectory( hyteg )
add_subdirectory( convection_particles )

if( HYTEG_TERRANEO_MODULE )
  add_subdirectory( terraneo )
endif()
