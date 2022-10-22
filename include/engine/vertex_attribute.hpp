#pragma once

#include <glad/glad.h>

struct Vertex_Attribute {
    unsigned int count;
    unsigned int type;
    unsigned char normalized; 
    unsigned int stride;

    unsigned int get_type_size() const 
    {
        switch(type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
            default: return 0;
        }
    }
};
