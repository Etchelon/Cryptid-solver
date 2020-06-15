cmake_minimum_required(VERSION 3.17.0)

project(Cryptid VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Cryptid")
set(CMAKE_TOOLCHAIN_FILE "C:/Code/C++/vcpkg/scripts/buildsystems/vcpkg.cmake")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Cryptid-app
    src/Cryptid.cpp
    src/map/hex.cpp
    src/map/sector.cpp
    src/clues/clue.cpp
)

target_link_libraries(Cryptid-app ${CONAN_LIBS})
