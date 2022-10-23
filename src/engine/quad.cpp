#include "quad.hpp"

#include <glad/glad.h>

// default constructor generates dynamic vbo
Quad::Quad()
    :indices({0,1,2, 0,2,3})
{
	vao = std::make_unique<Vertex_Array>();
	vbo = std::make_unique<Vertex_Buffer>(4*sizeof(Quad_Vertex));
	ibo = std::make_unique<Index_Buffer>(&indices[0],indices.size());
	vao->add_attribute(2,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // pos x,y
	vao->add_attribute(4,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // color r,g,b,a
	vao->add_attribute(2,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // tex coord u,v
	vao->set_layout();
	vao->unbind();
}

// store quad in static vbo
Quad::Quad(const std::array<Quad_Vertex,4>& data)
    :quad_model(data),indices({0,1,2, 0,2,3})
{
	vao = std::make_unique<Vertex_Array>();
	vbo = std::make_unique<Vertex_Buffer>(&quad_model[0],quad_model.size()*sizeof(Quad_Vertex));
	ibo = std::make_unique<Index_Buffer>(&indices[0],indices.size());
	vao->add_attribute(2,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // pos x,y
	vao->add_attribute(4,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // color r,g,b,a
	vao->add_attribute(2,GL_FLOAT,GL_FALSE,sizeof(Quad_Vertex)); // tex coord u,v
	vao->set_layout();
	vao->unbind();
}

void Quad::bind() const
{
    vao->bind();
}
void Quad::unbind() const
{
    vao->bind();
}
void Quad::draw() const
{
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
}

void Quad::modify_buffer(const std::array<Quad_Vertex,4> data)
{
	vbo->modify_buffer(&data[0],data.size()*sizeof(Quad_Vertex));
}

