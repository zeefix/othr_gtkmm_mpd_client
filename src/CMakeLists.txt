cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE source *.cc *.hh *.cpp *.h *.glade)

configure_file(views/player.glade player.glade COPYONLY)
file(COPY other_modules/speech_processing DESTINATION ./)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${PYTHON_LIBRARY_DIRS}
)

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

add_executable(anothrclient ${source})

target_link_libraries(anothrclient ${GTKMM_LIBRARIES} ${PYTHON_LIBRARIES} -lmpdclient 
-lfftw3
-lm
)