set( concept_include_dirs  "${GTEST_INCLUDE_DIRS}" )
set( concept_link_libs     "${GTEST_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${Boost_LIBRARIES}" )
set( concept_dep           "GTEST_CONFIG" )

ug_module_test_unit( 
    concept_module_name
    "Avalon/concept.cpp" 
    "${concept_include_dirs}" 
    "${concept_link_libs}" 
    "${concept_dep}"
)
target_compile_options      ( ${concept_module_name} PRIVATE -g -O0 )
target_compile_definitions  ( ${concept_module_name} PRIVATE SINGLE_CPP )
target_link_libraries       ( ${concept_module_name} ${GTEST_BOTH_LIBRARIES} ) 

unset( concept_include_dirs ) 
unset( concept_link_libs    ) 
unset( concept_dep          ) 
unset( concept_module_name  )
