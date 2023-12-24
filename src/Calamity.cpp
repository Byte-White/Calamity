#include"Calamity/Calamity.h"
#include <iostream>

namespace clm
{
    Calamity::Calamity(Window& window,Shader& shader)
    : window(window), shader(shader),va(vertexData.data(),vertexData.size()),ib(indicesData.data(),indicesData.size()),renderer()
    {

    }

    Calamity::~Calamity()
    {

    }
    void Calamity::Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.Clear();
        renderer.Draw(va,ib,shader,indicesData.size());
        window.SwapBuffers();
        window.PollEvents();
        
        vertexData.clear();
        indicesData.clear();
    }

    void Calamity::DrawRect(float x,float y,float w,float h)
    {
        vertexData.push_back(x);
        vertexData.push_back(y);
        vertexData.push_back(0);

        vertexData.push_back(x+w);
        vertexData.push_back(y);
        vertexData.push_back(0);
        
        vertexData.push_back(x);
        vertexData.push_back(y-h);
        vertexData.push_back(0);

        vertexData.push_back(x+w);
        vertexData.push_back(y-h);
        vertexData.push_back(0);

        //--------------------------
        indicesData.push_back(0);
        indicesData.push_back(1);
        indicesData.push_back(2);

        indicesData.push_back(1);
        indicesData.push_back(2);
        indicesData.push_back(3);
        UpdateData();
    }
    void Calamity::DrawTestTriangle()
    {    
        vertexData.push_back(0.0f);  // x1
        vertexData.push_back(-0.5f); // y1
        vertexData.push_back(0.0f);

        vertexData.push_back(0.5f);  // x2
        vertexData.push_back(-0.5f); // y2
        vertexData.push_back(0.0f);

        vertexData.push_back(0.0f);  // x3
        vertexData.push_back(0.5f);  // y3
        vertexData.push_back(0.0f);

        indicesData.push_back(0);
        indicesData.push_back(1);
        indicesData.push_back(2);

        UpdateData();
    }

    void Calamity::UpdateData()
    {
        va.UpdateVertexBufferData(vertexData.data(),vertexData.size());
        ib.UpdateData(indicesData.data(),indicesData.size());
    }
} // namespace clm
