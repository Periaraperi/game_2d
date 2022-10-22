#pragma once

#include <vector>

#include "vertex_attribute.hpp"

class Vertex_Array {
public:
	Vertex_Array();
	Vertex_Array(const Vertex_Array&) = delete;
	Vertex_Array& operator=(const Vertex_Array&) = delete;
    ~Vertex_Array();

    void add_attribute(unsigned int count, 
                       unsigned int type, 
                       unsigned char normalized, 
                       unsigned int stride);
    void set_layout();
    void bind() const;
    void unbind() const;
private:
    unsigned int id;
    std::vector<Vertex_Attribute> attributes;
};
