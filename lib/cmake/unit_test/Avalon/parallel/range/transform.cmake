set( transform_include_dirs "${GTEST_INCLUDE_DIRS};${Boost_INCLUDE_DIRS}" )
set( transform_link_libs "${GTEST_BOTH_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${Boost_LIBRARIES}" )
set( transform_dep "GTEST_CONFIG;BOOST_CONFIG" )

ug_module_test_unit( 
    transform_module_name
    "Avalon/parallel/range/transform.cpp" 
    "${transform_include_dirs}" 
    "${transform_link_libs}" 
    "${transform_dep}"
)
target_compile_options( ${transform_module_name} PRIVATE -g -O0 )
target_compile_definitions( ${transform_module_name} PRIVATE SINGLE_CPP OPEN_LOG_PORT=warn,msg,dev)
target_link_libraries( ${transform_module_name} ${GTEST_BOTH_LIBRARIES} ) 
unset( transform_include_dirs )
unset( transform_link_libs)
unset( transform_dep )
unset( transform_module_name )

