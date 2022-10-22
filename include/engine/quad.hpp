#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

#include "color.hpp"

struct Quad_Vertex {
    glm::vec2 pos;
    Color c;
    glm::vec2 tex_coord; // texture coords
};

class Quad {
public:
    float w,h;

    Quad();
    Quad(const std::array<Quad_Vertex,4>& data);
    Quad(const Quad&) = delete;
    Quad& operator=(const Quad&) = delete;
    void bind() const;
    void unbind() const;
    void draw() const;
private:
    std::unique_ptr<Vertex_Array> vao;
    std::unique_ptr<Vertex_Buffer> vbo;
    std::unique_ptr<Index_Buffer> ibo;
    std::array<Quad_Vertex,4> quad_model;
    std::array<unsigned int,6> indices;

    void init();
};

