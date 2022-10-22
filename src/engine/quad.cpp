#include "quad.hpp"

#include <glad/glad.h>

Quad::Quad()
    :indices({0,1,2, 0,2,3})
{
    quad_model = {
        {
            {glm::vec2(-0.5f, 0.5f),{0.0f,0.0f,0.0f,1.0f},glm::vec2(0.0f,0.0f)}, // bot left
            {glm::vec2(-0.5f,-0.5f),{0.0f,0.0f,0.0f,1.0f},glm::vec2(0.0f,1.0f)}, // top left
            {glm::vec2( 0.5f,-0.5f),{0.0f,0.0f,0.0f,1.0f},glm::vec2(1.0, 1.0f)}, // top right
            {glm::vec2( 0.5f, 0.5f),{0.0f,0.0f,0.0f,1.0f},glm::vec2(1.0f,0.0f)}  // bot right
        }
    };
    init();
}

Quad::Quad(const std::array<Quad_Vertex,4>& data)
    :quad_model(data),indices({0,1,2, 0,2,3})
{
    init();
}
void Quad::init()
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



