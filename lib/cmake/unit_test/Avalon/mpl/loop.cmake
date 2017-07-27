
set( loop_include_dirs  "${GTEST_INCLUDE_DIRS}" )
set( loop_link_libs     "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${Boost_LIBRARIES}" )
set( loop_dep           "GTEST_CONFIG" )

ug_module_test_unit( 
    loop_module_name
    "Avalon/mpl/loop.cpp" 
    "${loop_include_dirs}" 
    "${loop_link_libs}" 
    "${loop_dep}"
)
target_compile_options      ( ${loop_module_name} PRIVATE -g -O0 )
target_compile_definitions  ( ${loop_module_name} PRIVATE SINGLE_CPP )
target_link_libraries       ( ${loop_module_name} ${GTEST_BOTH_LIBRARIES} ) 

unset( loop_include_dirs ) 
unset( loop_link_libs    ) 
unset( loop_dep          ) 
unset( loop_module_name  )
