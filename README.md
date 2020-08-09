# Fractical
A hobby project to implement viewing, zooming and exploration of various 
fractals with OpenGL.

## Dependancies

#### GLFW
[GLFW](https://www.glfw.org/) (Graphics Library Framework) is used for window
creation and event handling. The GLFW license can be found
[here](https://www.glfw.org/license.html).

#### GLEW
[GLEW](http://glew.sourceforge.net/) (OpenGL Extension Wrangler Library) is used
for interfacing with OpenGL functionality on target systems. The GLEW license
can found [here](https://github.com/nigels-com/glew#copyright-and-licensing).

## Compiling

For unix, run the setup.bash script to download and compile the required git
repositories in the local folder for an in tree build (shouldn't install system
wide).

For windows, compiling is currently broken due to GLEW. Eventually will need to
download the windows precompiled binaries and change CMakeLists to detect
windows and assume those binaries are present.

After installing, press F7 for available tasks for reconfiguring (required to
register new files), building the executable and running Fractical without a
debugger. Press F5 to start the debugger on the current executable.