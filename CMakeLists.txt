cmake_minimum_required(VERSION 3.15)
project(minesync C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG        1.10.5
)
FetchContent_MakeAvailable(cpr)

# Find Cairo via PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

# Find FLTK
find_package(FLTK REQUIRED)

add_executable(minesync
        main.cpp
        client/src/ui/MainWindow.cpp
        client/src/ui/ConnectionWindow.h
        client/src/ui/ConnectionWindow.cpp
        client/src/client/Client.h
        client/src/client/Client.cpp
        client/src/api/ApiController.h
        client/src/api/ApiController.cpp
        common/lib/zip/zip.c
        common/lib/zip/zip.h
        common/zip/ZipUtils.cpp
        common/zip/ZipUtils.h
        client/src/files/CacheHandler.cpp
        client/src/files/CacheHandler.h
        client/config/ClientAppConfig.h
        common/lib/pfd/portable-file-dialogs.h
)

target_compile_definitions(minesync PRIVATE
        _GNU_SOURCE
        _LARGEFILE64_SOURCE
        _FILE_OFFSET_BITS=64
)


target_include_directories(minesync PRIVATE
        client/src
        client/config
        common/lib/zip
        ${FLTK_INCLUDE_DIRS}
        ${CAIRO_INCLUDE_DIRS}
)

target_link_libraries(minesync PRIVATE
        ${FLTK_LIBRARIES}
        ${CAIRO_LIBRARIES}
        cpr::cpr
)