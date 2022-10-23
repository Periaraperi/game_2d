#pragma once

class Vertex_Buffer {
public:
    Vertex_Buffer(const void* data, unsigned int nbytes);
	Vertex_Buffer(unsigned int nbytes);
    Vertex_Buffer(const Vertex_Buffer&) = delete;
    Vertex_Buffer& operator=(const Vertex_Buffer&) = delete;
    ~Vertex_Buffer();

    void bind() const;
    void unbind() const;

	void modify_buffer(const void* data, unsigned int nbytes, unsigned int offset = 0);

private:
    unsigned int id;
	unsigned int usage;
};
