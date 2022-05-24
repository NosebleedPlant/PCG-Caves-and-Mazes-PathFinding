#pragma once
#include <vector>
#include "vertexBuffer.h"

/*
Author: Yalmaz
A struct to store vertex buffer elements
*/
struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
};

/*
Author: Yalmaz
This class abstracts the vertext buffer layout to clean up the code a bit in main
*/
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

/*
Author: Yalmaz
This class abstracts the vertext array to clean up the code a bit in main
*/
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

    //adds all elements in vertex buffers to the vertex array with their respective on layouts
    void addVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        vb.bind();//binds vertex buffer
        unsigned long long offset = 0;
        const auto& elements = layout.getElements();//gets all elements in layout
        //adds each element to current vertex array
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (void*)offset);
            glEnableVertexAttribArray(0);
            offset += element.count * sizeof(element.type);
        }
    }

    //binds vertex array
    void bind() const
    {
        glBindVertexArray(ID);
    }
    
    //un-binds vertex array
    void unbind() const
    {
        glBindVertexArray(0);
    }
};