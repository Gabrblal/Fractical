#include "Error.hpp"

#include <string>
#include <iostream>

void __stdcall glDebugOutput(GLenum source,
                             GLenum type,
                             GLuint id,
                             GLenum severity,
                             GLsizei length,
                             const GLchar *message,
                             const void *userParam)
{
    if (id == 131169
    ||  id == 131185 // Buffer object will use VIDEO memory as the source as buffer object operations
    ||  id == 131218 // Shader will be recompiled dur to GL state mismatches
    ||  id == 131204 // Texture state usage warning, waste of memory: Texture 0 has mipmaps, while its min filter is inconsistent with mipmaps.
    ) {
        return ;
    }

    std::string source_str;
    std::string type_str;
    std::string severity_str;

    switch (source) {
        case GL_DEBUG_SOURCE_API:               source_str = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     source_str = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:   source_str = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:       source_str = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:       source_str = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:             source_str = "Other"; break;
    }

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               type_str = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_str = "Undefined Bahviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_str = "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_str = "Other"; break;
    }

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH: severity_str = "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: severity_str = "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW: severity_str = "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_str = "Notification"; break;
    }

    std::cout << "OpenGL Debug Message ("
              << id << ", "
              << source_str << ", "
              << type_str << ", "
              << severity_str << "):\n"
              << message << '\n' << std::endl;
}

void InitialiseDebugOutput()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}