# include "Vertex.hpp"

///////////////////////////////// VertexBuffer /////////////////////////////////

VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data, GLenum usage)
{
    // Generate a single new VBO
    glGenBuffers(1, &m_id);

    // Bind the buffer to the array buffer binding point
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    // Copy the data to the graphics storage
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///////////////////////////////// IndexBuffer //////////////////////////////////

IndexBuffer::IndexBuffer(const GLuint *data, unsigned int count, GLenum usage)
    : m_count(count)
{   
    // Create a new buffer
    glGenBuffers(1, &m_id);

    // Bind the buffer the the index buffer binding point
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

    // Copy the data of this index buffer to the graphics storage
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint), data, usage);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

////////////////////////////// VertexBufferLayout //////////////////////////////

VertexBufferLayout::VertexBufferLayout() : m_stride(0) {}

void VertexBufferLayout::PushBack(GLenum type, GLint count, GLboolean normalised)
{
    m_attributes.push_back({type, count, normalised});
    m_stride += count * SizeOfType(type);
}

unsigned int VertexBufferLayout::SizeOfType(GLenum type)
{
    switch (type)
    {
        case GL_BYTE:           return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
        case GL_SHORT:          return sizeof(GLfloat);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);
        case GL_INT:            return sizeof(GLint);
        case GL_UNSIGNED_INT:   return sizeof(GLuint);
        case GL_FLOAT:          return sizeof(GLfloat);
        case GL_DOUBLE:         return sizeof(GLdouble);
    }

    return 0;
}

///////////////////////////////// VertexArray //////////////////////////////////

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_id);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &vertexbuffer, const VertexBufferLayout &layout)
{
    // Bind this vertex array and the vertex buffer to add attributes to.
    Bind();
    vertexbuffer.Bind();

    // Get the attributes, offset is the number of bytes into each vertex an attribute it
    const std::vector<VertexBufferAttribute>& attributes = layout.GetAttributes();
    GLuint offset = 0;

    // For each attribute, add a new attribute pointer at index i and define an
    // array of vertex attribute data for that attribute.
    for (GLuint i = 0; i < attributes.size(); i++)
    {
        const auto& attribute = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              attribute.count,
                              attribute.type,
                              attribute.normalised,
                              layout.GetStride(),
                              reinterpret_cast<const GLvoid*>(offset));

        // Update the offset into the attribute by adding the number of bytes the
        // attribute takes up
        offset += attribute.count * VertexBufferLayout::SizeOfType(attribute.type);
    }
}
