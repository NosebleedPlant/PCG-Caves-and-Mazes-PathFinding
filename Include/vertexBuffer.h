#pragma once
#include <glad/glad.h>
/*
Author: Yalmaz
This class abstracts the vertext buffer to clean up the code a bit in main
*/
class VertexBuffer
{
private:
    unsigned int ID;//buffer id
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

    //binds the buffer
    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    //un-binds the buffer
    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};