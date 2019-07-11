#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <unordered_map>

#include "defs.hpp"

// Note that const char* is used since an std::string would have to be converted
// to a c_str on shader compilation
// const char *ParseShader(const char *filepath);
// unsigned int CompileShader(const unsigned int type, const char *source);
// unsigned int CreateProgram(const char *vertexShader, const char *fragmentShader);

extern const char* mandelbrot_fs;
extern const char* mandelbrot_vs;

class Shader
{
    public:

        Shader(const char *vertex, const char *fragment);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:

        // Parses a shader file to a const char*
        const char *ParseShader(const char *filepath);

        // Creates a new shader object on the GPU from source, with error checking.
        // Returns the shaders ID. Most common usage is GL_FRAGMENT_SHADER and 
        //GL_VERTEX_SHADER
        GLuint CompileShader(const GLuint type, const char *source);

        // Compiles and links a vertex and fragment shader into a program with error
        // checking. Returns the programs ID
        GLuint CreateProgram(const char *vertex, const char *fragment);

        // Returns the location of the given uniform, -1 if it does not exist
        GLint GetUniformLocation(const char *name);

        void SetUniform1f(const char *name, GLfloat f1);
        void SetUniform4f(const char *name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

        GLuint m_id;
        std::unordered_map<const char*, GLint> m_uniform_location_cache;

};

class Fractal : public Shader
{
    static const char *s_default_frag;
    static const char *s_default_vert;

    public:
        Fractal(Settings &settings);
        ~Fractal();
    private:

        // Initalises the uniforms used be all fractals, e.g. window coordinates
        void InitUniforms();

        // Updates the view of the fractal
        void Update();

        // Updates any mathematics needed to render to fractal
        virtual void UpdateFractal() = 0;

        // To update uniforms
        Settings* m_settings;
};

class Mandelbrot : public Fractal, public Shader
{
    static const char * s_frag;
    static const char *s_vert;
    
    public:
        Mandelbrot(Settings &settings);

    private:
        void UpdateFractal() override {};
};
 
#endif // SHADER_H