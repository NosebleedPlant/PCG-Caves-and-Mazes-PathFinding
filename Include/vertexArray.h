#pragma once
#include <vector>
#include "vertexBuffer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
};

class VertexBufferLayout
{
private:
    unsigned int stride;
    std::vector<VertexBufferElement> elements;
public:
    VertexBufferLayout()
        : stride(0) 
    {}

    inline const std::vector<VertexBufferElement> getElements() const {return elements;}
    inline unsigned int getStride() const {return stride;}

    void push(unsigned int count)
    {
        elements.push_back({GL_FLOAT,count,GL_FALSE});
        stride += sizeof(GL_FLOAT)*count;
    }
};

class VertexArray
{
private:
    unsigned int ID;
public:
    VertexArray()
    {
        glGenVertexArrays(1, &ID);
        glBindVertexArray(ID);
    }
    ~VertexArray()
    {
        glDeleteVertexArrays(1, &ID);
    }

    void addVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        vb.bind();
        unsigned long long offset = 0;
        const auto& elements = layout.getElements();
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)offset);
            glEnableVertexAttribArray(0);
            offset += element.count * sizeof(element.type);
        }
    }

    void bind() const
    {
        glBindVertexArray(ID);
    }
    void unbind() const
    {
        glBindVertexArray(0);
    }
};