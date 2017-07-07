set( logger_include_dirs  "${GTEST_INCLUDE_DIRS}" )
set( logger_link_libs     "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( logger_dep           "GTEST_CONFIG" )

ug_module_test_unit( 
    logger_module_name
    "Avalon/util/logger.cpp" 
    "${logger_include_dirs}" 
    "${logger_link_libs}" 
    "${logger_dep}"
)
target_compile_options      ( ${logger_module_name} PRIVATE -g -O0 )
target_compile_definitions  ( ${logger_module_name} PRIVATE SINGLE_CPP )
target_link_libraries       ( ${logger_module_name} ${GTEST_BOTH_LIBRARIES} ) 

unset( logger_include_dirs ) 
unset( logger_link_libs    ) 
unset( logger_dep          ) 
unset( logger_module_name  )