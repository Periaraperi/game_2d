#include "shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_src = parse_shader(vertex_path);
	std::string fragment_src = parse_shader(fragment_path);

	unsigned int vertex_shader = compile_shader(vertex_src,GL_VERTEX_SHADER);
	unsigned int fragment_shader = compile_shader(fragment_src,GL_FRAGMENT_SHADER);

	create_shader_program(vertex_shader,fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

std::string Shader::parse_shader(const std::string& path)
{
	std::ifstream shader_file;

	shader_file.open(path.c_str());

	std::stringstream ss;
	ss << shader_file.rdbuf();

	shader_file.close();

	return ss.str();
}

unsigned int Shader::compile_shader(const std::string& src, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	const char* shader_src = src.c_str();
	glShaderSource(shader,1,&shader_src,nullptr);
	glCompileShader(shader);

	// check if successfully compiled
	int success;
	char log[512];
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
	if(!success) {
		glGetShaderInfoLog(shader,512,nullptr,log);
		std::cerr << "Couldn't compile shader\n" << log << '\n';
	}

	return shader;
}

void Shader::create_shader_program(unsigned int vertex_shader, unsigned int fragment_shader)
{
	id = glCreateProgram();
	glAttachShader(id,vertex_shader);
	glAttachShader(id,fragment_shader);
	glLinkProgram(id);

	// check if successfully linked
	int success;
	char log[512];
	glGetProgramiv(id,GL_LINK_STATUS,&success);
	if(!success) {
		glGetProgramInfoLog(id,512,nullptr,log);
		std::cerr << "Couldn't link shader program\n" << log << '\n';
	}
}

void Shader::enable() const
{
	glUseProgram(id);
}

void Shader::set_float(const std::string& u_name,float val)
{
	glUniform1f(glGetUniformLocation(id,u_name.c_str()),val);
}

void Shader::set_vec2(const std::string& u_name,const glm::vec2& v)
{
	glUniform2f(glGetUniformLocation(id,u_name.c_str()),v.x,v.y);
}

void Shader::set_mat4(const std::string& u_name,const glm::mat4& m)
{
	glUniformMatrix4fv(glGetUniformLocation(id,u_name.c_str()),1,GL_FALSE,glm::value_ptr(m));
}
