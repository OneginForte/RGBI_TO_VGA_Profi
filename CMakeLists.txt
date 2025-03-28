# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD waveshare_rp2040_zero CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(RGBI_TO_VGA C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(RGBI_TO_VGA main.cpp vga.c dvi.c g_config.c rgb_capture.c v_buf.c ZX_RGBI_TO_VGA_HDMI.cpp RP2040USB.cpp)

pico_set_program_name(RGBI_TO_VGA "RGBI_TO_VGA")
pico_set_program_version(RGBI_TO_VGA "0.1.6")

# Generate PIO header
pico_generate_pio_header(RGBI_TO_VGA ${CMAKE_CURRENT_LIST_DIR}/pio_programs.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(RGBI_TO_VGA 0)
pico_enable_stdio_usb(RGBI_TO_VGA 0)
#pico_enable_stdio_usb(TARGET ENABLED)
# Add the standard include files to the build
target_include_directories(RGBI_TO_VGA PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(RGBI_TO_VGA 
        hardware_pio
        hardware_dma
        hardware_flash
        pico_multicore
        pico_unique_id
        pico_stdlib
        #pico_stdio
        tinyusb_device
        #tinyusb_host
        #pico_stdio_usb
        )

pico_add_extra_outputs(RGBI_TO_VGA)
