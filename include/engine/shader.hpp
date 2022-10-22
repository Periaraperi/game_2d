#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Shader {
public:
	Shader(const std::string& vertex_path, const std::string& fragment_path);
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	~Shader();

	void enable() const;

	void set_float(const std::string& u_name, float val);
	void set_vec2(const std::string& u_name, const glm::vec2& v);
    void set_mat4(const std::string& u_name, const glm::mat4& m);

private:
	unsigned int id;
	std::string parse_shader(const std::string& path);
	unsigned int compile_shader(const std::string& src, unsigned int type);
	void create_shader_program(unsigned int vertex_shader, unsigned int fragment_shader);
};
