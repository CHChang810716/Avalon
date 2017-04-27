
set( loop_include_dirs "${GTEST_INCLUDE_DIRS}" )
set( loop_link_libs "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( loop_dep "GTEST_CONFIG" )

ug_test_unit( "loop" 
    "${loop_include_dirs}" 
    "${loop_link_libs}" 
    "${loop_dep}"
)
target_compile_options( ${PROJECT_NAME}_loop_test PRIVATE -g -O0 )
target_compile_definitions( ${PROJECT_NAME}_loop_test PRIVATE SINGLE_CPP )
target_link_libraries( ${PROJECT_NAME}_loop_test  ${GTEST_BOTH_LIBRARIES} ) 

