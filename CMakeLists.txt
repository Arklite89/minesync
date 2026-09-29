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

FetchContent_Declare(
        crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(crow)

# GUI Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)
find_package(FLTK REQUIRED)

# ==============================================================================
#  Shared Common Library
# ==============================================================================
add_library(minesync_common STATIC
        common/lib/zip/zip.c
        common/lib/zip/zip.h
        common/zip/ZipUtils.cpp
        common/zip/ZipUtils.h
        common/files/CacheHandler.cpp
        common/files/CacheHandler.h
        common/lib/pfd/portable-file-dialogs.h
        common/files/FileHelpers.cpp
        common/files/FileHelpers.h
)

target_compile_definitions(minesync_common PRIVATE
        _GNU_SOURCE
        _LARGEFILE64_SOURCE
        _FILE_OFFSET_BITS=64
)

target_include_directories(minesync_common PUBLIC
        common/
        common/lib/zip
)

# ==============================================================================
#  Client Target
# ==============================================================================
add_executable(minesync_client
        client/main.cpp
        client/src/ui/MainWindow.cpp
        client/src/ui/MainWindow.h
        client/src/ui/ConnectionWindow.cpp
        client/src/ui/ConnectionWindow.h
        client/src/client/Client.cpp
        client/src/client/Client.h
        client/src/api/ApiController.cpp
        client/src/api/ApiController.h
        client/src/data/World.cpp
        client/src/data/World.h
        common/files/ClientAppConfig.h
        server/src/api/ApiController.cpp
        server/src/api/ApiController.h
)

target_include_directories(minesync_client PRIVATE
        client/src
        client/config
        ${FLTK_INCLUDE_DIRS}
        ${CAIRO_INCLUDE_DIRS}
)

target_link_libraries(minesync_client PRIVATE
        minesync_common
        ${FLTK_LIBRARIES}
        ${CAIRO_LIBRARIES}
        cpr::cpr
)

# ==============================================================================
#  Server Target
# ==============================================================================
add_executable(minesync_server
        server/main.cpp
)

target_include_directories(minesync_server PRIVATE
        server/src
)

target_link_libraries(minesync_server PRIVATE
        minesync_common
        Crow::Crow
)