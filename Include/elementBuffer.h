#pragma once

class ElementBuffer
{
private:
    unsigned int ID;
public:
    ElementBuffer(const unsigned int* data, unsigned int size);
    ~ElementBuffer();

    void bind() const;
    void unbind() const;
};