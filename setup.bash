echo "This script installs flew and glfw locally in this folder."

mkdir lib
cd lib

echo "Installing GLEW under lib/glew/"
git clone https://github.com/nigels-com/glew.git

echo "Installing GLFW under lib/glfw/"
git clone https://github.com/glfw/glfw.git