#ifndef ERROR_H
#define ERROR_H

#define GLEW_STATIC
#include <GL/glew.h>

// Function to bind to glDebugMessageCallback to receive debugging messages from
// the GL. This function will be called whenever a debug message is generated
void __stdcall glDebugOutput(GLenum source,
                             GLenum type,
                             GLuint id,
                             GLenum severity,
                             GLsizei length,
                             const GLchar *message,
                             const void *userParam);

// Initalises the debugging output.  Must be called after glewInit()
void InitialiseDebugOutput();

#endif // ERROR_H