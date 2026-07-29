cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(PnuemaOS_mbr VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(PnuemaOS_mbr mbr.cpp)
target_compile_options(PnuemaOS_mbr PRIVATE
    -target i386-none-elf
    -m16
    -O0
    -ffreestanding
    -nostdlib
    -mno-red-zone
    -fno-pic
    -fno-pie
    -fno-exceptions
    -fno-rtti
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
)

target_link_options(PnuemaOS_mbr PRIVATE
    -fuse-ld=lld
    -nostdlib
    -nostartfiles
    -no-pie
    -Wl,--no-dynamic-linker
    -Wl,--build-id=none
    -Wl,--no-eh-frame-hdr
    -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/link.ld
)
target_compile_features(PnuemaOS_mbr PRIVATE cxx_std_26)
target_link_libraries(PnuemaOS_mbr PRIVATE biosf-8086)

add_custom_command(TARGET PnuemaOS_mbr POST_BUILD
    COMMAND objcopy -O binary $<TARGET_FILE:PnuemaOS_mbr> ${CMAKE_BINARY_DIR}/bin/loader.img
)
