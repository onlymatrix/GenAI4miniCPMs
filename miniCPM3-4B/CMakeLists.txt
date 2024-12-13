# Copyright (C) 2023-2024 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required (VERSION 3.10)
if(POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif()

project(miniCPM3-4B)
find_package(OpenVINOGenAI REQUIRED
    PATHS
        "${CMAKE_BINARY_DIR}"  # Reuse the package from the build.
        ${OpenVINO_DIR}  # GenAI may be installed alogside OpenVINO.
    NO_CMAKE_FIND_ROOT_PATH
)

add_executable(miniCPM3-4B main.cpp)
target_link_libraries(miniCPM3-4B PRIVATE openvino::genai)
set_target_properties(miniCPM3-4B PROPERTIES
    COMPILE_PDB_NAME miniCPM3-4B
    # Ensure out of box LC_RPATH on macOS with SIP
    INSTALL_RPATH_USE_LINK_PATH ON)
if(MSVC) 
    target_compile_options(
        miniCPM3-4B PRIVATE
        /Wall  # Display all warnings
        /wd4710 /wd4711  # Disable the inline warnings
        /EHsc  # Enable standard C++ stack unwinding, assume functions with extern "C" never throw
    )
else()
    target_compile_options(miniCPM3-4B PRIVATE -Wall)  # Display all warnings
endif()
