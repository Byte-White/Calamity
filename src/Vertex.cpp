#pragma once
#include "Calamity/Vertex.h"

namespace clm 
{
// Vertex Array
    VertexArray::VertexArray(float* vertices, GLsizei vertexCount)
    : vertexbuffer(std::make_shared<VertexBuffer>(vertices, vertexCount * sizeof(float) * 3))
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        // Create and bind the Vertex Buffer Object (VBO)
        
        // Set the vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind the VAO
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray() 
    {
        glDeleteVertexArrays(1, &VAO);
    }

    void VertexArray::UpdateVertexBufferData(const void *data, GLsizei size)
    {    
        glBindVertexArray(VAO);
        vertexbuffer->UpdateData(data, size);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(VAO);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
// Vertex Buffer
    VertexBuffer::VertexBuffer(const void* data, GLsizei size) 
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() 
    {
        glDeleteBuffers(1, &VBO);
    }
    void VertexBuffer::UpdateData(const void* data, GLsizei size) 
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }
    void VertexBuffer::Bind() 
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }

    void VertexBuffer::Unbind() 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
// Index Buffer
    IndexBuffer::IndexBuffer(const GLuint* data, GLsizei count) : count(count) 
    {
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); 
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() 
    {
        glDeleteBuffers(1, &IBO);
    }

    void IndexBuffer::Bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    }

    void IndexBuffer::Unbind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::UpdateData(const void* data, GLsizei count)
    {
        this->count = count;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); 
        //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(GLuint), data);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
    }
} // namespace clm
