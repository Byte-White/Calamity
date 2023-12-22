#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "Shader.h"
 
namespace clm
{
    class Renderer 
    {
    public:
        Renderer();
        ~Renderer();

        void Clear();
        void Draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader,int count);
    private:
    };

    
    

} // namespace clm