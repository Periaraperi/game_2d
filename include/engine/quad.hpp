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
    glm::vec2 tex_coord;
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
	void modify_buffer(const std::array<Quad_Vertex,4> data);
private:
    std::unique_ptr<Vertex_Array> vao;
    std::unique_ptr<Vertex_Buffer> vbo;
    std::unique_ptr<Index_Buffer> ibo;
    std::array<Quad_Vertex,4> quad_model;
    std::array<unsigned int,6> indices;
};

inline std::array<Quad_Vertex,4> gen_quad(Color c)
{
	std::array<Quad_Vertex,4> q = {
		{
			{glm::vec2(-0.5f, 0.5f),c,glm::vec2(0.0f,0.0f)}, // bot left
			{glm::vec2(-0.5f,-0.5f),c,glm::vec2(0.0f,1.0f)}, // top left
			{glm::vec2( 0.5f,-0.5f),c,glm::vec2(1.0, 1.0f)}, // top right
			{glm::vec2( 0.5f, 0.5f),c,glm::vec2(1.0f,0.0f)}  // bot right
		}
	};
	return q;
}

inline std::array<Quad_Vertex,4> gen_quad(const std::array<glm::vec2,4> tex_coords)
{
	std::array<Quad_Vertex,4> q = {
		{
			{glm::vec2(-0.5f, 0.5f),{0.0f,0.0f,0.0f,1.0f},tex_coords[0]}, // bot left
			{glm::vec2(-0.5f,-0.5f),{0.0f,0.0f,0.0f,1.0f},tex_coords[1]}, // top left
			{glm::vec2( 0.5f,-0.5f),{0.0f,0.0f,0.0f,1.0f},tex_coords[2]}, // top right
			{glm::vec2( 0.5f, 0.5f),{0.0f,0.0f,0.0f,1.0f},tex_coords[3]}  // bot right
		}
	};
	return q;
}