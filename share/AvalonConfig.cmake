include ( FindPackageHandleStandardArgs )
get_filename_component( AVALON_ROOT         ${CMAKE_CURRENT_LIST_DIR}/../   ABSOLUTE )
get_filename_component( AVALON_INCLUDE_DIRS ${AVALON_ROOT}/include          ABSOLUTE )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( AVALON DEFAULT_MSG AVALON_INCLUDE_DIRS )
