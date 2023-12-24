#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/glm.hpp>
#include <vector>

// TODO: Data Layout

namespace clm {
    // Used as a template 
    /*struct Vertex
    {
    };

    struct CLMVertex: Vertex
    {
        //glm::vec3 position;
        //glm::vec3 color;
        //glm::vec2 textureCoords;
    };*/

    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT         : return sizeof(GLfloat);
                case GL_UNSIGNED_INT  : return sizeof(GLuint);
                case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
            }
            return 0;
        }
    };

    class VertexBufferLayout
    {
        private:
            unsigned int m_Stride, m_Count;
            std::vector<VertexBufferElement> m_Elements;
            
        public:
            VertexBufferLayout() :
                m_Stride(0),m_Count(0) { }

            void AddFloat(unsigned int count)        { Push(GL_FLOAT, count, GL_FALSE);        }
            void AddUnsignedInt(unsigned int count)  { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
            void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

            inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
            inline unsigned int GetStride() const { return m_Stride; }
            inline unsigned int GetCount() const  { return m_Count; }
        private:
            void Push(unsigned int type, unsigned int count, unsigned char normalized)
            {
                struct VertexBufferElement vbe = {type, count, normalized};
                m_Elements.push_back(vbe);
                m_Stride += count * VertexBufferElement::GetSizeOfType(type);
                m_Count += count;
            }
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
        VertexArray(float* vertices, GLsizei vertexCount, const VertexBufferLayout& layout);
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
