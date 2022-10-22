#include "vertex_buffer.hpp"

#include <glad/glad.h>

Vertex_Buffer::Vertex_Buffer(const void* data, unsigned int nbytes)
{
    glGenBuffers(1,&id);
    bind();
    glBufferData(GL_ARRAY_BUFFER,nbytes,data,GL_STATIC_DRAW);
}

Vertex_Buffer::~Vertex_Buffer()
{
    glDeleteBuffers(1,&id);
}

void Vertex_Buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,id);
}

void Vertex_Buffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
