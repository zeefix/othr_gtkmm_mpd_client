cmake_minimum_required(VERSION 3.0)

project(anothrclient)

find_package(PkgConfig)
find_package(PythonLibs REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src) 