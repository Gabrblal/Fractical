#ifndef VERTEX_H
#define VERTEX_H

#define GLEW_STATIC
#include "GL/glew.h"

#include <vector>

class VertexBuffer {
    // Abstractation of the Vertex Buffer Object (VBO) in OpenGL.
    // VBOs handle data related to the verticies of a shape (position, colour etc)
    
    public:

        VertexBuffer(GLsizeiptr size, const void* data, GLenum usage); 
        ~VertexBuffer();

        void Bind() const;   // Binds this VertexBuffer for the next draw call
        void Unbind() const; // Unbinds this VertexBuffer, binding the states VBO to 0

    private:
    
        GLuint m_id; // The OpenGL Id for this VBO

};

class IndexBuffer {
    // Abstraction of the OpenGL index buffer that is an array of indicies
    // into a vertex buffer, so that verticies aren't repeated in the vertex
    // buffer but are instead referenced by their index when drawing.

    public:

        // data - pointer to index array
        // count - the number of indicies in the array
        // usage - Specifies the expected usage pattern of the data. Must
        //         be one of:
        //         GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY,
        //         GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
        //         GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY        
        IndexBuffer(const GLuint *data, unsigned int count, GLenum usage); 
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline GLuint GetCount() { return m_count; }

    private:
    
        GLuint m_id;    // The OpenGL ID for this index buffer
        GLuint m_count; // The number of indicies in the index buffer

};

struct VertexBufferAttribute {
    GLenum type;
    GLint count;
    GLboolean normalised;
};

class VertexBufferLayout {

    // Contains information of the layout of a vertex buffer. Each vertex has
    // attributes (such as position, colour, etc) that may differ between buffers.
    // This class is used to construct a layout of a buffer.

    public:

        VertexBufferLayout();

        // Adds a new attribute to the vertex layout
        void PushBack(GLenum type, GLint count, GLboolean normalised = GL_FALSE);

        // Returns the layout of a single vertex
        inline const std::vector<VertexBufferAttribute>& GetAttributes() const {
            return m_attributes;
        }

        // Returns the stride in bytes of each vertex in the layout
        inline GLsizei GetStride() const { return m_stride; }

        // Returns the size in bytes of a GL symbolic constant e.g. GL_BYTE
        static unsigned int SizeOfType(GLenum type);
        
    private:
 
        // The stride in number of bytes of each vertex
        GLsizei m_stride;

        // A vector of VertexBufferAttributes that represents the layout of a
        // single vertex 
        std::vector<VertexBufferAttribute> m_attributes;

};

class VertexArray
{
    // Combines a vertex 
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const VertexBuffer &vertexbuffer, const VertexBufferLayout& layout);

    private:
        GLuint m_id;
};

#endif // VERTEX_H