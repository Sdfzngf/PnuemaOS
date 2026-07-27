cmake_minimum_required(VERSION 3.28)
project(BIOSF)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(biosf-8086 STATIC)

target_compile_options(biosf-8086 PRIVATE
    -target i386-none-elf
    -m16
    -ffreestanding
    -nostdlib
    -mno-red-zone
    -fno-pic
    -fno-pie
)

target_link_options(biosf-8086 PRIVATE
    -fuse-ld=lld
    -nostdlib
    -nostartfiles
    -no-pie
    -m16
    -Wl,--no-dynamic-linker
)

set(MODULE_EXPORT_DIR ${CMAKE_CURRENT_BINARY_DIR}/cxx-modules)
target_sources(biosf-8086
    PUBLIC
        FILE_SET CXX_MODULES
        FILES biosf.cppm
)
