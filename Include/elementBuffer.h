#pragma once
#include <glad/glad.h>

class ElementBuffer
{
private:
    unsigned int ID;
    unsigned int count;
public:
    ElementBuffer(const unsigned int* data, const unsigned int size)
    {
        count = size/sizeof(unsigned int);
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ~ElementBuffer()
    {
        glDeleteBuffers(1, &ID);
    }

    void bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline unsigned int getCount() const {return count;} 
};