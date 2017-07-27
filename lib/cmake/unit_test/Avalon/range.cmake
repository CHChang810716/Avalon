set( range_include_dirs "${GTEST_INCLUDE_DIRS};${Boost_INCLUDE_DIRS}" )
set( range_link_libs "${GTEST_BOTH_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${Boost_LIBRARIES}" )
set( range_dep "GTEST_CONFIG;BOOST_CONFIG" )

ug_module_test_unit( 
    range_module_name
    "Avalon/range.cpp" 
    "${range_include_dirs}" 
    "${range_link_libs}" 
    "${range_dep}"
)
target_compile_options( ${range_module_name} PRIVATE -g -O0 )
target_compile_definitions( ${range_module_name} PRIVATE SINGLE_CPP OPEN_LOG_PORT=warn,msg,dev)
target_link_libraries( ${range_module_name} ${GTEST_BOTH_LIBRARIES} ) 
unset( range_include_dirs )
unset( range_link_libs)
unset( range_dep )
unset( range_module_name )
