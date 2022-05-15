#pragma once

class ElementBuffer
{
private:
    unsigned int ID;
public:
    ElementBuffer(const unsigned int* data, unsigned int size)
    {
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
};