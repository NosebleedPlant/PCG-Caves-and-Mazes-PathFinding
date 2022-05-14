#include <elementBuffer.h>
#include <glad/glad.h>

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &ID);
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

