#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <unordered_map>

#include "defs.hpp"

// Abstratation of the OpenGL shader interface. Handles parsing, compilation
// and creation of OpenGL programs (i.e. shaders) and sets their uniforms.
class Shader
{
    public:

        Shader(const char *vertex, const char *fragment);
        ~Shader();
        
        // BUG: Destroying the shader in the destructor prevents the use of
        // temporaries for initalisation, as the destructor of the temporary
        // would call glDeleteProgram on the ID given to the new shader object.
        // Use this function to destroy instead.
        void Destroy();

        void Bind() const;
        void Unbind() const;

    private:

        // Parses a shader file to a const char*
        const char *ParseShader(const char *filepath);

        // Creates a new shader object on the GPU from source, with error checking.
        // Returns the shaders ID. Most common type is GL_FRAGMENT_SHADER and 
        // GL_VERTEX_SHADER
        GLuint CompileShader(const GLuint type, const char *source);

        // Compiles and links a vertex and fragment shader into a program with error
        // checking. Returns the program's ID
        GLuint CreateProgram(const char *vertex, const char *fragment);

    protected:
    
        // Returns the location of the given uniform, -1 if it does not exist
        GLint GetUniformLocation(const char *name);

        // Cache to store uniform locations to reduce expensive calls to
        // glGetUniformLocation
        std::unordered_map<const char*, GLint> m_uniform_location_cache;

        GLuint m_id;

        void SetUniform1f(const char *name, GLfloat f1);
        void SetUniform4f(const char *name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

};
 
#endif // SHADER_H