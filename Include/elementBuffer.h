#pragma once
#include <glad/glad.h>
/*
Author: Yalmaz
This class abstracts the element buffer to clean up the code a bit in main
*/
class ElementBuffer
{
private:
    unsigned int ID;//id of the buffer
    unsigned int count;//elemnt count
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

    //binds this buffer
    void bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    //un-binds this buffer
    void unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    //gets the element count
    inline unsigned int getCount() const {return count;} 
};