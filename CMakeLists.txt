cmake_minimum_required(VERSION 3.15)
project(minesync CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Cairo via PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

# Find FLTK
find_package(FLTK REQUIRED)

add_executable(minesync
    src/main.cpp
    src/ui/MainWindow.cpp
        src/ui/ConnectionWindow.h
        src/ui/ConnectionWindow.cpp
        src/client/Client.h
        src/client/Client.cpp
)

target_include_directories(minesync PRIVATE 
    src 
    ${FLTK_INCLUDE_DIRS}
    ${CAIRO_INCLUDE_DIRS}
)

target_link_libraries(minesync PRIVATE 
    ${FLTK_LIBRARIES}
    ${CAIRO_LIBRARIES}
)
