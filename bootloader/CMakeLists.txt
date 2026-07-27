cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(PnuemaOS_bootloader VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(PnuemaOS_bootloader boot.cpp)
target_compile_options(PnuemaOS_bootloader PRIVATE
    -target i386-none-elf
    -m16
    -ffreestanding
    -nostdlib
    -mno-red-zone
    -fno-pic
    -fno-pie
)

target_link_options(PnuemaOS_bootloader PRIVATE
    -fuse-ld=lld
    -nostdlib
    -nostartfiles
    -no-pie
    -Wl,--no-dynamic-linker
    -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/link.ld
)
target_compile_features(PnuemaOS_bootloader PRIVATE cxx_std_26)
target_link_libraries(PnuemaOS_bootloader PRIVATE biosf-8086)

add_custom_command(TARGET PnuemaOS_bootloader POST_BUILD
    COMMAND objcopy -O binary $<TARGET_FILE:PnuemaOS_bootloader> ${CMAKE_BINARY_DIR}/bin/loader.img
)
