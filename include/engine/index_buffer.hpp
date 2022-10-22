#pragma once

class Index_Buffer {
public:
    Index_Buffer(const void* data, unsigned int index_count);
    Index_Buffer(const Index_Buffer&) = delete;
    Index_Buffer& operator=(const Index_Buffer&) = delete;
    ~Index_Buffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int id;
};
