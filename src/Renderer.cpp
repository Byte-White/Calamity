#pragma once
#include "Calamity/Renderer.h"

namespace clm
{
     
    Renderer::Renderer()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    
    Renderer::~Renderer()
    {

    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader,int count)
    {
        // Use the shader program, draw triangles
        shader.Use();
        vao.Bind();
        ib.Bind();
        glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,nullptr);
        ib.Unbind();
        vao.Unbind();

    }
} // namespace clm