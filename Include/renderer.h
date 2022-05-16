#pragma once
#include "vertexArray.h"
#include "elementBuffer.h"
#include "shaders/shader.h"

struct Renderer
{
    void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void draw(const VertexArray& vao,const ElementBuffer& ebo,const Shader& shader) const
    {
        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
    }
};