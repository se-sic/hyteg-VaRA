waLBerla_compile_test(FILES json/BasicJSONReadTest.cpp DEPENDS hyteg core )
waLBerla_execute_test(NAME BasicJSONReadTest)

waLBerla_compile_test(FILES plates/PlateVelocityComputationTest.cpp DEPENDS terraneo hyteg core )
waLBerla_execute_test(NAME PlateVelocityComputationTest)
