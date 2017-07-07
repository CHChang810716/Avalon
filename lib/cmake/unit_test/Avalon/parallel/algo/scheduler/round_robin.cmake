set( round_robin_include_dirs "${GTEST_INCLUDE_DIRS}" )
set( round_robin_link_libs "${GTEST_BOTH_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( round_robin_dep "GTEST_CONFIG" )

ug_module_test_unit( 
    round_robin_module_name
    "Avalon/parallel/algo/schedule/round_robin.cpp" 
    "${round_robin_include_dirs}" 
    "${round_robin_link_libs}" 
    "${round_robin_dep}"
)
target_compile_options( ${round_robin_module_name} PRIVATE -g -O0 )
target_compile_definitions( ${round_robin_module_name} PRIVATE SINGLE_CPP OPEN_LOG_PORT=warn,msg,dev)
target_link_libraries( ${round_robin_module_name} ${GTEST_BOTH_LIBRARIES} ) 
unset( round_robin_include_dirs )
unset( round_robin_link_libs)
unset( round_robin_dep )
unset( round_robin_module_name )