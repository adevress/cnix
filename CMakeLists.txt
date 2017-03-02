project(cnix)
cmake_minimum_required(VERSION 2.8)

enable_testing()

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")

option(UNIT_TESTS "Enable or disable unit tests execution" TRUE)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
      ${PROJECT_SOURCE_DIR}/CMake/portability
      ${PROJECT_SOURCE_DIR}/CMake/packages
      ${PROJECT_SOURCE_DIR}/CMake/config)

include(DefineInstallationPaths)
include(ReleaseDebugAutoFlags)
include(DetectCXX11Support)


# nix API makes mandatory C++11
SET(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Threads)
find_package(Nix)



include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/  )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${INCLUDE_INSTALL_DIR})

add_subdirectory(src)


add_subdirectory(tests/unit)

