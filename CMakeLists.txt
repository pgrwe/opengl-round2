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


# Add GLFW - disable building tests, examples, and docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw-3.4)

# Add GLAD - create glad library from the glad.c source file
add_library(glad external/glad/src/glad.c)
# Specify where to find the glad.h header
target_include_directories(glad PUBLIC external/glad/include)

# Add the executable - main.cpp contains our application's entry point
add_executable(opengl_round2 src/main.cpp)

# Link the executable with the glfw and glad libraries
target_link_libraries(opengl_round2 glfw glad)

# Specify include directories for the executable
target_include_directories(opengl_round2 PUBLIC external/glad/include)
target_include_directories(opengl_round2 PUBLIC external/glfw/include)
