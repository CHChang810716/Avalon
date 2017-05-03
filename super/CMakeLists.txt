cmake_minimum_required (VERSION 3.2)
project (AvalonSuperBuild)
message ( "====== Avalon Super Build System =====" )
get_filename_component( CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../ ABSOLUTE)
set( UnderGround_DIR ${CMAKE_SOURCE_DIR}/lib/UnderGround/share )
find_package( UnderGround CONFIG REQUIRED )
include ( "${UNDER_GROUND_CMAKE_DIR}/utility/debug.cmake" )
include ( "${UNDER_GROUND_CMAKE_DIR}/arch.cmake" )
include ( "${UNDER_GROUND_CMAKE_DIR}/config_external.cmake" )
include ( ExternalProject )
show_var( CMAKE_CXX_COMPILER_ID )
show_var( CMAKE_SYSTEM_NAME )

set( GTEST_EP_SRC   "PRE_BUILD" )
set( SDL2_EP_SRC    "PRE_BUILD" )
set( BOOST_EP_SRC   "PRE_BUILD" )

# build upstream dependency
include ( ${UNDER_GROUND_CMAKE_DIR}/gtest/build.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/SDL2/build.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/boost/build.cmake )

# build Avalon
ExternalProject_add(AVALON_BUILD
    PREFIX ${CMAKE_BINARY_DIR}/AVALON/
    # DEPENDS GTEST_BUILD SDL2_BUILD
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    BINARY_DIR ${CMAKE_BINARY_DIR}/AVALON/build
    TEST_BEFORE_INSTALL 1
    CMAKE_ARGS
#        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
        -DGTEST_ROOT:PATH=${GTEST_ROOT}
        -DSDL2_ROOT:PATH=${SDL2_ROOT}
        -Dsdl2_DIR:PATH=${sdl2_DIR}
        -DBOOST_ROOT:PATH=${BOOST_ROOT}
    INSTALL_COMMAND ""
#    INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
)
add_dependencies( AVALON_BUILD SDL2_BUILD )
add_dependencies( AVALON_BUILD GTEST_BUILD )
add_dependencies( AVALON_BUILD BOOST_BUILD )

