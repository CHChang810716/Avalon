set( tuple_include_dirs  "${GTEST_INCLUDE_DIRS}" )
set( tuple_link_libs     "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${Boost_LIBRARIES}" )
set( tuple_dep           "GTEST_CONFIG" )

ug_module_test_unit( 
    tuple_module_name
    "Avalon/tuple.cpp" 
    "${tuple_include_dirs}" 
    "${tuple_link_libs}" 
    "${tuple_dep}"
)
target_compile_options      ( ${tuple_module_name} PRIVATE -g -O0 )
target_compile_definitions  ( ${tuple_module_name} PRIVATE SINGLE_CPP )
target_link_libraries       ( ${tuple_module_name} ${GTEST_BOTH_LIBRARIES} ) 

unset( tuple_include_dirs ) 
unset( tuple_link_libs    ) 
unset( tuple_dep          ) 
unset( tuple_module_name  )
