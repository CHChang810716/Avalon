set( const_string_include_dirs "${GTEST_INCLUDE_DIRS}" )
set( const_string_link_libs "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( const_string_dep "GTEST_CONFIG" )

ug_test_unit( "const_string" 
    "${const_string_include_dirs}" 
    "${const_string_link_libs}" 
    "${const_string_dep}"
)
target_compile_options( ${PROJECT_NAME}_const_string_test PRIVATE -g -O0 )
target_compile_definitions( ${PROJECT_NAME}_const_string_test PRIVATE SINGLE_CPP )
target_link_libraries( ${PROJECT_NAME}_const_string_test  ${GTEST_BOTH_LIBRARIES} ) 