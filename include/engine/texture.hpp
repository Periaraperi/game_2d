#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string& path);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	~Texture();

	void bind(unsigned int slot=0) const;
	void unbind() const;

    int get_width() const {return width;}
    int get_height() const {return height;}

private:
	unsigned int id;
	std::string path;
	unsigned char* buffer;
	int width;
	int height;
	int channels;
};
