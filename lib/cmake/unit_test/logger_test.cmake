set( logger_include_dirs "${GTEST_INCLUDE_DIRS}" )
set( logger_link_libs "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( logger_dep "GTEST_CONFIG" )

ug_test_unit( "logger" 
    "${logger_include_dirs}" 
    "${logger_link_libs}" 
    "${logger_dep}"
)
target_compile_options( ${PROJECT_NAME}_logger_test PRIVATE -g -O0 )
target_compile_definitions( ${PROJECT_NAME}_logger_test PRIVATE SINGLE_CPP )
target_link_libraries( ${PROJECT_NAME}_logger_test  ${GTEST_BOTH_LIBRARIES} ) 