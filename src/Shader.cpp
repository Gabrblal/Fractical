#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/////////////////////////////////// Shader /////////////////////////////////////

Shader::Shader(const char *vertex, const char *fragment)
    : m_id(0)
{
    m_id = CreateProgram(vertex, fragment);
}

Shader::~Shader()
{
    // See header file
    // glDeleteProgram(m_id);
}

void Shader::Destroy()
{
    glDeleteProgram(m_id);
}

void Shader::Bind() const
{
    glUseProgram(m_id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

const char *Shader::ParseShader(const char *filepath)
{
    std::ifstream filestream(filepath);
    std::string line;
    std::string source;

    while (std::getline(filestream, line)) {
        std::cout << line;
        source.append(line).append("\n");
    }

    return source.c_str();
}

GLuint Shader::CreateProgram(const char *vertex, const char *fragment)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    int valid;
    int linked;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if ( (valid == GL_FALSE) || (linked == GL_FALSE)) {

        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Program failed: " << message << std::endl;

        delete[] message;
        return 0;

    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint Shader::CompileShader(const GLuint type, const char *source)
{
    // Create a new shader with reference id. glShaderSource replaces the
    // shaders source code with an array of strings, of which there are 1
    // and it is null terminated.
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // glGetShaderiv returns an attribute from a shader object.
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Shader Compilation Error\n" << message << std::endl;

        delete[] message;

        return 0;
    }

    return id;
}

GLint Shader::GetUniformLocation(const char *name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) {
        return m_uniform_location_cache[name];
    }
    GLint location = glGetUniformLocation(m_id, name);
    if (location == -1) {
        std::cout << "Shader Warning: Uniform '" << name << "' does not exist." << std::endl;
    }
    
    m_uniform_location_cache[name] = location;
    return location;
}

void Shader::SetUniform1f(const char *name, GLfloat f1)
{
    glUniform1f(GetUniformLocation(name), f1);
}

void Shader::SetUniform4f(const char *name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}
