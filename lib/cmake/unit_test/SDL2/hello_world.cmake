# set( sdl2_hello_world_include_dirs  
#     ${SDL2_INCLUDE_DIRS}
# )
# set( sdl2_hello_world_link_libs     
#     ${SDL2_LIBRARIES}
# )
# set( sdl2_hello_world_dep
#     "SDL2_CONFIG" 
# )
# ug_module_test_unit( 
#     sdl2_hello_world_module_name
#     "SDL2/hello_world.cpp" 
#     "${sdl2_hello_world_include_dirs}" 
#     "${sdl2_hello_world_link_libs}" 
#     "${sdl2_hello_world_dep}"
# )
# target_compile_options      ( ${sdl2_hello_world_module_name} PRIVATE -g -O0 )
# target_compile_definitions  ( ${sdl2_hello_world_module_name} PRIVATE SINGLE_CPP )
# target_link_libraries       ( ${sdl2_hello_world_module_name} ${sdl2_hello_world_link_libs}) 
# 
# unset( sdl2_hello_world_include_dirs ) 
# unset( sdl2_hello_world_link_libs    ) 
# unset( sdl2_hello_world_dep          ) 
# unset( sdl2_hello_world_module_name  )
