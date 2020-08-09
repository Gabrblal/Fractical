echo "This script installs flew and glfw locally in this folder on UNIX."

mkdir lib
cd lib

echo "Installing GLEW under lib/glew/"
git clone https://github.com/nigels-com/glew.git
cd glew
make .
cd ..

echo "Installing GLFW under lib/glfw/"
git clone https://github.com/glfw/glfw.git