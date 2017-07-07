set( thread_pool_include_dirs 
    ${GTEST_INCLUDE_DIRS} 
    ${Boost_INCLUDE_DIRS}
)
set( thread_pool_link_libs 
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT} 
    ${Boost_LIBRARIES}
)
set( thread_pool_dep GTEST_CONFIG BOOST_CONFIG )

ug_module_test_unit( 
    thread_pool_module_name
    "Avalon/parallel/thread_pool.cpp" 
    "${thread_pool_include_dirs}" 
    "${thread_pool_link_libs}" 
    "${thread_pool_dep}"
)
target_compile_options( ${thread_pool_module_name} PRIVATE -g -O0 )
target_compile_definitions( ${thread_pool_module_name} PRIVATE SINGLE_CPP OPEN_LOG_PORT=warn,msg,dev)
unset( thread_pool_include_dirs )
unset( thread_pool_link_libs)
unset( thread_pool_dep )
unset( thread_pool_module_name )
