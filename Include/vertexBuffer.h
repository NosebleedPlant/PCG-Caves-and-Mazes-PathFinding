#pragma once
#include <glad/glad.h>

class VertexBuffer
{
private:
    unsigned int ID;
public:
    VertexBuffer(const void* data, unsigned int size)
    {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ~VertexBuffer()
    {
    glDeleteBuffers(1, &ID);
    }

    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};