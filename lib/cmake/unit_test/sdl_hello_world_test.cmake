show_var(SDL2_INCLUDE_DIRS)
set( sdl2_hello_world_include_dirs "${SDL2_INCLUDE_DIRS}" )
set( sdl2_hello_world_link_libs "${SDL2_LIBRARIES}" )
set( sdl2_hello_world_dep "SDL2_CONFIG" )
set( OLD_PROJECT_NAME "${PROJECT_NAME}")
set( PROJECT_NAME "SDL2" )
ug_test_unit( "hello_world" 
    "${sdl2_hello_world_include_dirs}" 
    "${sdl2_hello_world_link_libs}" 
    "${sdl2_hello_world_dep}"
)
target_compile_options( ${PROJECT_NAME}_hello_world_test PRIVATE -g -O0 )
target_compile_definitions( ${PROJECT_NAME}_hello_world_test PRIVATE SINGLE_CPP )
target_link_libraries( ${PROJECT_NAME}_hello_world_test  ${sdl2_hello_world_link_libs} ) 

set( PROJECT_NAME ${OLD_PROJECT_NAME})
