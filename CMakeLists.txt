cmake_minimum_required(VERSION 3.21)
project(forcepad3)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )

include_directories( ${PROJECT_SOURCE_DIR}/include ${Stb_INCLUDE_DIR})

# Set the path to vcpkg
set(VCPKG_ROOT "E:/vcpkg" CACHE STRING "Path to vcpkg directory containing the vcpkg executable")


# Find and include the necessary packages from vcpkg
find_package(raylib CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Stb REQUIRED) 
find_package(glfw3 CONFIG REQUIRED)
# Add more find_package statements for other required packages

# Add the src subdirectory containing the main program
add_subdirectory(src)  