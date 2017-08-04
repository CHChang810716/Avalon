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

ep_option( GTEST_EP_SRC   "REMOTE_SOURCE" )
ep_option( SDL2_EP_SRC    "PRE_BUILD" )
ep_option( BOOST_EP_SRC   "PRE_BUILD" )
# if( NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release" )
#     ep_option( BOOST_EP_SRC   "SYSTEM" )
# else()
#     ep_option( BOOST_EP_SRC   "PRE_BUILD" )
# endif()

# build upstream dependency
show_var( DEFAULT_EP_INSTALL_PATH )
include ( ${UNDER_GROUND_CMAKE_DIR}/gtest/build.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/SDL2/build.cmake )
include ( ${UNDER_GROUND_CMAKE_DIR}/boost/build.cmake )
set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${DEFAULT_EP_INSTALL_PATH})
# build Avalon
ExternalProject_add(AVALON_BUILD
    PREFIX ${CMAKE_BINARY_DIR}/AVALON/
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    BINARY_DIR ${CMAKE_BINARY_DIR}/AVALON/build
#    TEST_BEFORE_INSTALL 1
    CMAKE_ARGS
        -DGTEST_ROOT:PATH=${GTEST_ROOT}
        -DSDL2_ROOT:PATH=${SDL2_ROOT}
        -Dsdl2_DIR:PATH=${sdl2_DIR}
        -DRangeV3_DIR:PATH=${CMAKE_SOURCE_DIR}/lib/range-v3/share
        -DBOOST_ROOT:PATH=${BOOST_ROOT}
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
)
add_dependencies( AVALON_BUILD SDL2_BUILD )
add_dependencies( AVALON_BUILD GTEST_BUILD )
add_dependencies( AVALON_BUILD BOOST_BUILD )
enable_testing()
add_test( 
    NAME AVALON_TEST_ALL 
    COMMAND ctest
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/AVALON/build
)
