#pragma once
#include "Calamity/Vertex.h"

namespace clm 
{
// Vertex Array

    VertexArray::VertexArray(void* vertices, GLsizei vertexCount, const VertexBufferLayout& layout)
    : vertexbuffer(std::make_shared<VertexBuffer>(vertices, vertexCount * layout.GetStride()))
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        // Create and bind the Vertex Buffer Object (VBO)
        
        // Set the vertex attribute pointers
        //glVertexAttribPointer(0, layout.GetCount(), GL_FLOAT, GL_FALSE, layout.GetStride(), (void*)0);
        
        const std::vector<VertexBufferElement>& elements = layout.GetElements();
        unsigned int offset = 0;
        for(int i = 0;i<elements.size();i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,elements[i].count,elements[i].type,elements[i].normalized,layout.GetStride(),(void*)(uintptr_t)(offset));
            offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
        }

        // Unbind the VAO
        glBindVertexArray(0);
    }

    VertexArray::VertexArray()
    : vertexbuffer(std::make_shared<VertexBuffer>())
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
    }
    void VertexArray::LinkAttrib(void* vertices, GLsizei vertexCount, const VertexBufferLayout& layout)
    {
        glBindVertexArray(VAO);
        vertexbuffer->UpdateData(vertices,vertexCount* layout.GetStride());
        const std::vector<VertexBufferElement>& elements = layout.GetElements();
        unsigned int offset = 0;
        for(int i = 0;i<elements.size();i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,elements[i].count,elements[i].type,elements[i].normalized,layout.GetStride(),(void*)(uintptr_t)(offset));
            offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
        }
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

    void VertexArray::Unbind()
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
    VertexBuffer::VertexBuffer() 
    {
        glGenBuffers(1, &VBO);
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

    IndexBuffer::IndexBuffer() 
    {
        glGenBuffers(1, &IBO);
    }

    IndexBuffer::~IndexBuffer() 
    {
        glDeleteBuffers(1, &IBO);
    }

    void IndexBuffer::Bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    }

    void IndexBuffer::Unbind() {
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
