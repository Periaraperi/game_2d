#include "vertex_buffer.hpp"

#include <glad/glad.h>
#include <iostream>

// static buffer
Vertex_Buffer::Vertex_Buffer(const void* data, unsigned int nbytes)
	:usage(GL_STATIC_DRAW)
{
    glGenBuffers(1,&id);
    bind();
    glBufferData(GL_ARRAY_BUFFER,nbytes,data,usage);
}

// dynamic buffer
Vertex_Buffer::Vertex_Buffer(unsigned int nbytes)
	:usage(GL_DYNAMIC_DRAW)
{
	glGenBuffers(1,&id);
	bind();
	glBufferData(GL_ARRAY_BUFFER,nbytes,nullptr,usage);
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

void Vertex_Buffer::modify_buffer(const void* data, unsigned int nbytes, unsigned int offset /* 0 if not provided */)
{
	if (usage==GL_DYNAMIC_DRAW) {
		bind();
		glBufferSubData(GL_ARRAY_BUFFER,offset,nbytes,data);
	} else {
		std::cerr << "trying to modify static vbo!\n";
	}
}