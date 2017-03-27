#boost
set( Boost_USE_STATIC_LIBS    OFF )
set( Boost_USE_MULTITHREADED  ON  )
set( Boost_USE_STATIC_RUNTIME OFF )
find_package( Boost REQUIRED COMPONENTS 
    date_time 
    program_options 
    filesystem system 
    serialization 
    regex 
    thread 
    iostreams 
)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIR} )
