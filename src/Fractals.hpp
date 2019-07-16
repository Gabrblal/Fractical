#ifndef FRACTALS_H
#define FRACTALS_H

#include "defs.hpp"
#include "Shader.hpp"

// Superclass of all shaders that defines common uniforms and functions
class Fractal : virtual public Shader
{
    friend class FractalRenderer;

    public:
        Fractal(Settings &settings);
    
    protected:

        // Initalises the uniforms used be all fractals e.g. window coordinates
        virtual void InitUniforms();

        // Updates the view of the fractal. Ensures window coordinate / screen
        // size uniforms are always updated.
        void Update();

        // Override this function to update uniforms that change the fractal.
        // Likely called every render.
        virtual void UpdateFractal() {};

        // Used to update x,y window uniforms
        Settings* m_settings;
    
    private:

        // Default fractal shaders used for debugging.
        static const char *s_default_vert;
        static const char *s_default_frag;
};

class Mandelbrot : virtual public Shader, virtual public Fractal
{
    static const char *s_frag;
    static const char *s_vert;
    
    public:
        Mandelbrot(Settings &settings);

};

#endif // FRACTALS_H