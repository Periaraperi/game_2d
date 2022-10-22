#include "texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& p)
	:id(0), path(p), buffer(nullptr), width(0), height(0), channels(0)
{
	stbi_set_flip_vertically_on_load(1);
	buffer = stbi_load(path.c_str(),&width,&height,&channels,0);

	glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	if (buffer) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(buffer);
		buffer = nullptr;
	} else {
		std::cerr << "Error loading texture\n";
	}
	unbind();
}

Texture::~Texture()
{
	glDeleteTextures(1,&id);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D,id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D,0);
}
