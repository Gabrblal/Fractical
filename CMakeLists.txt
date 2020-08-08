# Installing the C and C++ GNU compilers:
#
# Windows:
#   http://www.mingw-w64.org/doku.php/download
#   Click on the sourceforge link to download the installer
#   Use 86_64 architexture with posix threading for 64 bit machines
#
# GNU/Linux:
#   sudo apt-get install build-essential

# Setting up CMake:
#
# Windows:
#   To identify the CC and CXX compiler want to run the command
#   cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=gcc CMAKE_CXX_COMPILER=g++ .
#   These variables get stored in the CMakeCache.txt
#
#   The dot at the end is the current directory for source files.
#   Should link to full path to the correct compiler executables in case there exists
#   multiple compilers on the path (e.g. if StrawberryPerl is installed, it has it's
#   own compilers). To check location of the compilers on windows, use "where [g++/gcc".
#
# GNU/Linux:
#   sudo apt-get install cmake

cmake_minimum_required(VERSION 3.13)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(OpenGL REQUIRED)

# Add the GLFW source, will execute the glfw CMakeLists to compile it
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

# Define the source code files
file(GLOB SOURCE
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/lib/glew/src
)

# Define the executable to be compiled
add_executable(fractical ${SOURCE})

# Define all include directories for the executable source files
target_include_directories(fractical PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib/glfw/include
    ${CMAKE_SOURCE_DIR}/lib/glew/include
)

# Define the libraries for linking. glfw and OpenGL are defined in the glfw
# CMakeLists
target_link_libraries(fractical PUBLIC 
    ${CMAKE_SOURCE_DIR}/lib/glew/lib/libGLEW.a
    ${GLFW_LIBRARIES}
    glfw
    OpenGL::GL
)

# Add compiler flags
target_compile_options(fractical
    PUBLIC -g -std=c++17 -Wall -Werror -DGLEW_NO_GLU
)