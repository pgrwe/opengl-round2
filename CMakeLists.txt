cmake_minimum_required(VERSION 3.10)
project(opengl_round2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# For generating clangd compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories for build targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source files as project scales
set(SOURCES src/main.cpp src/shaders.cpp src/vbo.cpp src/vao.cpp src/ebo.cpp  src/texture.cpp)

# Disable building tests, examples, and docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# Add GLM
add_subdirectory(external/glm)
# Add GLFW
add_subdirectory(external/glfw-3.4)
# Add Assimp
add_subdirectory(external/assimp-5.4.2)
# Add GLAD
add_library(glad external/glad/src/glad.c)
# Include directories
include_directories(external/glm external/glad/include)

# Add executable to be created
add_executable(opengl_round2 ${SOURCES})

# Testing offscreen rendering for a flutter project
# add_executable(offscreen_render src/offscreen_render.cpp)

# Link the executable with the glfw and glad libraries
target_link_libraries(opengl_round2 glfw glad glm assimp)
