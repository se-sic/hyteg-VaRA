target_sources( hyteg
    PRIVATE
    P2Form.hpp
    P2LinearCombinationForm.hpp
    P1Form.hpp
    P1WrapperForm.hpp
    P1RowSumForm.hpp
    P1Form.cpp
    P2RowSumForm.hpp
    P2Form.cpp
    Form.hpp
    P1ZeroForm.hpp
    P1LinearCombinationForm.hpp
    CoefficientQuadratureAveraging.hpp
    P1LinearCombinationForm.hpp
    N1E1Form.hpp
    N1E1LinearCombinationForm.hpp
    P0Form.hpp
    P0Form.cpp
)
add_subdirectory( form_hyteg_base )
add_subdirectory( form_hyteg_manual )
add_subdirectory( form_fenics_base )
add_subdirectory( form_hyteg_generated )
add_subdirectory( form_fenics_generated )
