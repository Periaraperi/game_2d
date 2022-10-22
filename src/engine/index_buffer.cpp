#include "index_buffer.hpp"

#include <glad/glad.h>

Index_Buffer::Index_Buffer(const void* data, unsigned int index_count)
{
    glGenBuffers(1,&id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,index_count*sizeof(unsigned int),data,GL_STATIC_DRAW);
}

Index_Buffer::~Index_Buffer()
{
    glDeleteBuffers(1,&id);
}

void Index_Buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
}

void Index_Buffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

