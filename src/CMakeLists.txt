cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE source *.cc *.hh *.glade)

configure_file(views/player.glade player.glade COPYONLY)
file(COPY other_modules/natural_language_interface DESTINATION ./)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${PYTHON_LIBRARY_DIRS}
)

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

add_executable(out ${source})

target_link_libraries(out ${GTKMM_LIBRARIES} ${PYTHON_LIBRARIES} -lmpdclient )