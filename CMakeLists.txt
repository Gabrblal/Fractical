##### Installing the C and C++ GNU compilers, using MinGW64:
# http://www.mingw-w64.org/doku.php/download
# Click on the sourceforge link to download the installer
# Use 86_64 architexture with posix threading for 64 bit machines
#

#### Setting up CMake:
# To identify the CC and CXX compiler want to run the command
# cmake -G "MinGW Makefiles" -D CMAKE_C_COMPILER=gcc CMAKE_CXX_COMPILER=g++ .
# These variables get stored in the CMakeCache.txt
#
# The dot at the end is the current directory for source files.
# Should link to full path to the correct compiler executables in case there exists
# multiple compilers on the path (e.g. if StrawberryPerl is installed, it has it's
# own compilers). To check location of the compilers on windows, use "where [g++/gcc".
# To check location of compilers on linux use "which [g++/gcc]"

cmake_minimum_required(VERSION 3.13)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

################################## GLFW ########################################

find_package(OpenGL REQUIRED)

# Add the GLFW source, will execute the glfw CMakeLists to compile it
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

# Define the include directory for GLFW
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/glfw/include)

################################## GLEW ########################################

# Glew requires the statically linked binaries e.g. glew32s.lib

# Define the GLEW include folder
set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/glew/include)

# Define the location of the glew libraries that must be linked
set(GLEW_LINK_DIR ${CMAKE_SOURCE_DIR}/lib/glew/lib/Release/x64)

############################## Compilation #####################################

# Define the source code files
file(GLOB SOURCE ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/lib/glew/src)

# Define the header files
set(SOURCE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

# Define the executable to be compiled
add_executable(fractical ${SOURCE} ${GLEW_SOURCE})

# Define all include directories for the executable source files
target_include_directories(
    fractical 
    PUBLIC 
    ${SOURCE_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIR} 
    ${GLFW_INCLUDE_DIR} 
)

# Define the directories for linking
target_link_directories(fractical PUBLIC ${GLEW_LINK_DIR})

# Define the libraries for linking. glfw and OpenGL are defined in the glfw CMakeLists
target_link_libraries(fractical PUBLIC glew32s glfw ${GLFW_LIBRARIES} OpenGL::GL)

# Add compiler flags
target_compile_options(fractical
    PUBLIC -g -std=c++17 -Wall -Werror
)