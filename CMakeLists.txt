cmake_minimum_required (VERSION 2.8)
project (cpp_mpl)

set( CMAKE_VERBOSE_MAKEFILE ON )
set( GNU        "GNU"   )
set( Clang      "Clang" )
set( MSVC       "MSVC"  )

# Compiler-specific C++14 activation.
if( ${CMAKE_CXX_COMPILER_ID} STREQUAL ${GNU} )
    execute_process( COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION )
    if( NOT (GCC_VERSION VERSION_GREATER 6.0 OR GCC_VERSION VERSION_EQUAL 5.0) )
        message( FATAL_ERROR "${PROJECT_NAME} requires g++ 6.0 OR greater." )
    endif()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL ${Clang} )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z" )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL ${MSVC} )
else()
    message( FATAL_ERROR "Your C++ compiler does not support C++14." )
endif()
message(STATUS "module path: ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}")
find_package( Threads )
include ( ${CMAKE_SOURCE_DIR}/lib/cmake/boost.cmake )
include ( ${CMAKE_SOURCE_DIR}/lib/cmake/gtest.cmake )

# enable_testing()
include_directories( ${CMAKE_SOURCE_DIR}/include )
link_directories( ${CMAKE_SOURCE_DIR}/lib )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/ )

add_executable( loop_test ${CMAKE_SOURCE_DIR}/unit_test/mpl/loop_test.cpp )
if( ${CMAKE_CXX_COMPILER_ID} STREQUAL ${GNU} OR ${CMAKE_CXX_COMPILER_ID} STREQUAL ${Clang})
    target_compile_options( loop_test PRIVATE -g -Ofast )
endif()
target_compile_definitions( loop_test PRIVATE SINGLE_CPP )
target_link_libraries( loop_test 
    ${Boost_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
) 

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

