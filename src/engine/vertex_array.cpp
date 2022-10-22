#include "vertex_array.hpp"

Vertex_Array::Vertex_Array()
{
    glGenVertexArrays(1,&id);
    bind();
}

Vertex_Array::~Vertex_Array()
{
    glDeleteVertexArrays(1,&id);
}

void Vertex_Array::add_attribute(unsigned int count, 
                                 unsigned int type, 
                                 unsigned char normalized, 
                                 unsigned int stride)
{
    attributes.push_back({count,type,normalized,stride});
}

void Vertex_Array::set_layout()
{
    int offset = 0;
    for(int attr=0; attr<(int)attributes.size(); ++attr) {
        glEnableVertexAttribArray(attr);
        Vertex_Attribute va = attributes[attr];
        glVertexAttribPointer(attr,
                              va.count,
                              va.type,
                              va.normalized,
                              va.stride,
                              (const void*) offset);
        offset += (va.count*va.get_type_size());
    }
}

void Vertex_Array::bind() const
{
    glBindVertexArray(id);
}

void Vertex_Array::unbind() const
{
    glBindVertexArray(0);
}

