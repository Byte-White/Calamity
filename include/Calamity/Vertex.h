#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

// TODO: Data Layout

namespace clm {
    // Used as a template 
    struct Vertex
    {
    };

    struct CLMVertex: Vertex
    {
        glm::vec3 position;
        //glm::vec3 color;
        //glm::vec2 textureCoords;
    };



    class VertexBuffer {
    public:
        VertexBuffer(const void* data, GLsizei size);
        ~VertexBuffer();

        void Bind();
        void Unbind();
        void UpdateData(const void* data, GLsizei size);

        inline GLuint GetVBO() const
        {
            return VBO;
        }
    private:
        GLuint VBO;
    };


    class IndexBuffer {
    public:
        IndexBuffer(const GLuint* data, GLsizei count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        void UpdateData(const void* data, GLsizei count);

        inline GLsizei GetCount() const 
        {
            return count;
        }

        inline GLuint GetIBO() const
        {
            return IBO;
        }
    private:
        GLuint IBO;
        GLsizei count;
    };

    class VertexArray {
    public:
        VertexArray(float* vertices, GLsizei vertexCount);
        ~VertexArray();

        void Bind() const;
        void Unbind() const;
        void UpdateVertexBufferData(const void* data, GLsizei size);

        inline GLuint GetVAO() const
        {
            return VAO;
        }

    private:
        GLuint VAO;
        std::shared_ptr<VertexBuffer> vertexbuffer;
    };

    
} // namespace clm
