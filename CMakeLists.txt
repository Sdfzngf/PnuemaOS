cmake_minimum_required(VERSION 3.28.0)

project(PnuemaOS)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(biosf)
add_subdirectory(bootloader)
