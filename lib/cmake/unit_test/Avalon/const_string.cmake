set( const_string_include_dirs  "${GTEST_INCLUDE_DIRS}" )
set( const_string_link_libs     "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT}" )
set( const_string_dep           "GTEST_CONFIG" )

ug_module_test_unit( 
    const_string_module_name
    "Avalon/const_string.cpp" 
    "${const_string_include_dirs}" 
    "${const_string_link_libs}" 
    "${const_string_dep}"
)
target_compile_options      ( ${const_string_module_name} PRIVATE -g -O0 )
target_compile_definitions  ( ${const_string_module_name} PRIVATE SINGLE_CPP )
target_link_libraries       ( ${const_string_module_name} ${GTEST_BOTH_LIBRARIES} ) 

unset( const_string_include_dirs ) 
unset( const_string_link_libs    ) 
unset( const_string_dep          ) 
unset( const_string_module_name  )
