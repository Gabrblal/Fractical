#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "FractalRenderer.hpp"
#include "Error.hpp"

#define DEBUG true
#define INIT_WIDTH 1980
#define INIT_HEIGHT 1080

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

    if (!glfwInit()) {
        std::cout << "Failed to initalise GLFW" << std::endl;
        return -1;
    }
    
    // Despite the word "hint", glfwWindowHint sets configuration options.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (DEBUG) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    GLFWwindow *window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "Fractical", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Bind function when window changes size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return -1;
    }

    if (DEBUG) {
        InitialiseDebugOutput();
    }

    Settings settings = {
        -2, 2,
         -2, 2
    };

    FractalRenderer renderer(settings);

    while(!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // Render
        renderer.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    glfwTerminate();
    return 0;

}

// When the framebuffer size changes, adjust the view port width as well
void framebuffer_size_callback(GLFWwindow *window, GLint width, GLint height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}