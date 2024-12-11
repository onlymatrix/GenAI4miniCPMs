# Copyright (C) 2023-2024 Intel Corporation
# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required (VERSION 3.10)
if(POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif()

project(visual_language_chat)

find_package(OpenVINO REQUIRED
    PATHS
        "${CMAKE_BINARY_DIR}"  # Reuse the package from the build.
        ${OpenVINO_DIR}  # GenAI may be installed alogside OpenVINO.
    NO_CMAKE_FIND_ROOT_PATH
)


set (OpenVINO_INCLUDE_DIR "$ENV{INTEL_OPENVINO_DIR}/runtime/include")
set (OpenVINO_LIB_DIR "$ENV{INTEL_OPENVINO_DIR}/runtime/lib/intel64/Release")

set (OPENVINO_GENAI_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/genai_runtime/lib" )
set (OpenVINO_GENAI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/genai_runtime/include")


include_directories(OpenVINO_INCLUDE_DIR)
include_directories(OpenVINO_GENAI_INCLUDE_DIR)


find_library(OPENVINO_GENAI_LIB_PATH
		PATHS ${OPENVINO_GENAI_LIB_PATH}
		)

find_library(OPENVINO_LIBRARY_RELEASE NAMES openvino
		PATHS  ${OpenVINO_LIB_DIR}
		)


add_executable(visual_language_chat visual_language_chat.cpp load_image.cpp)

target_include_directories(visual_language_chat PRIVATE "${CMAKE_CURRENT_SOUCE_DIR}" "${OpenVINO_GENAI_INCLUDE_DIR}", "${OpenVINO_INCLUDE_DIR}")

target_link_libraries(visual_language_chat  PRIVATE
	$<$<CONFIG:Release>:${OPENVINO_LIBRARY_RELEASE}>
	${OPENVINO_GENAI_LIB_PATH}/openvino_tokenizers.lib
	${OPENVINO_GENAI_LIB_PATH}/openvino_genai.lib
	
)


set_target_properties(visual_language_chat PROPERTIES CXX_STANDARD 17)
set_target_properties(visual_language_chat PROPERTIES CXX_STANDARD_REQUIRED ON)

if(MSVC) 
    target_compile_options(
        visual_language_chat PRIVATE
        /Wall  # Display all warnings
        /wd4710 /wd4711  # Disable the inline warnings
        /EHsc  # Enable standard C++ stack unwinding, assume functions with extern "C" never throw
    )
else()
    target_compile_options(visual_language_chat PRIVATE -Wall)  # Display all warnings
endif()
