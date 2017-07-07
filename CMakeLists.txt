cmake_minimum_required (VERSION 2.8)
project (Avalon)
set( CMAKE_VERBOSE_MAKEFILE ON )
message(STATUS "module path: ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}")
set ( UnderGround_DIR ${CMAKE_SOURCE_DIR}/lib/UnderGround/share )
find_package( UnderGround CONFIG REQUIRED )
set(LIB_PREFIX "avalon" )

# Compiler-specific C++14 activation.
include ( ${UNDER_GROUND_CMAKE_DIR}/compiler.cmake )

include ( ${UNDER_GROUND_CMAKE_DIR}/utility/custom_type_unit.cmake      )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/exe_unit.cmake              )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/debug.cmake                 )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/lib_unit.cmake              )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/option.cmake                )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/test_unit.cmake             )
include ( ${UNDER_GROUND_CMAKE_DIR}/utility/target_compile_config.cmake )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/stage/bin )

if( WIN32 )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/stage/bin )
else()
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/stage/lib )
endif()

find_package( Threads )
include ( ${UNDER_GROUND_CMAKE_DIR}/gtest/config.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/SDL2/config.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/boost/config.cmake )

include_directories( ${CMAKE_SOURCE_DIR}/include )

enable_testing()
file( 
    GLOB_RECURSE unit_test_cmakes 
    ${CMAKE_SOURCE_DIR}/lib/cmake/unit_test/*.cmake 
)
foreach ( utc ${unit_test_cmakes} )
    # show_var( utc )
    include ( ${utc} )
endforeach()
# include ( ${CMAKE_SOURCE_DIR}/lib/cmake/unit_test/loop_test.cmake )

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

