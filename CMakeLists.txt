//gltf viewer cmake
cmake_minimum_required(3.10.0)

project(gltf_viewer VERSION 0.1.0)

include_directories(
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(toy_render)