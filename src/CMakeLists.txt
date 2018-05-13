cmake_minimum_required(VERSION 3.11)

file(GLOB_RECURSE source *.cc *.hh *.glade)

configure_file(player.glade player.glade COPYONLY)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
)

include_directories(
    ${GTKMM_INCLUDE_DIRS}
)

add_executable(out ${source})

target_link_libraries(out ${GTKMM_LIBRARIES} -lmpdclient )

#cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/opt/plplot -DPLD_wingdi=ON -DPLD_wingcc=ON -DWIN32=1 -DMINGW=1 -DMINGWLIBPATH=/d/msys64/usr/lib/w32api
#../plplot/ &> cmake.log