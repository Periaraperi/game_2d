#pragma once

class Vertex_Buffer {
public:
    Vertex_Buffer(const void* data, unsigned int nbytes);
    Vertex_Buffer(const Vertex_Buffer&) = delete;
    Vertex_Buffer& operator=(const Vertex_Buffer&) = delete;
    ~Vertex_Buffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int id;
};
