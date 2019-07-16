#ifndef FRACTALS_H
#define FRACTALS_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "defs.hpp"
#include "Shader.hpp"

// Superclass of all shaders that defines common uniforms and functions
class Fractal : virtual public Shader
{
    friend class FractalRenderer;


    public:
        Fractal();
    
    protected:

        // Override to initalise custom uniforms for the fractal
        virtual void InitFractal() {};

        // Override this function to update uniforms that change the fractal.
        // Likely called every render.
        virtual void UpdateFractal() {};

        void SetWindowResolution(GLfloat width, GLfloat height);
        void SetWindowCoordinates(GLfloat x0, GLfloat y0);
        void SetCartesianValues(GLfloat x, GLfloat y);
    
    private:

        // Default fractal shaders used for debugging.
        static const char *s_default_vert;
        static const char *s_default_frag;
        
        struct {
            GLfloat width = 1920.0;
            GLfloat height = 1080.0;
            GLfloat x0 = -1.0;
            GLfloat y0 = -1.0;
            GLfloat x = 2.0;
            GLfloat y = 2.0;
        } s_default_settings;
};

class Mandelbrot : virtual public Shader, virtual public Fractal
{
    static const char *s_frag;
    static const char *s_vert;
    
    public:
        Mandelbrot();

};

#endif // FRACTALS_H