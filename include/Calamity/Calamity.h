    #pragma once

    #include "Renderer.h"
    #include "Vertex.h"
    #include "Shader.h"
    #include "Window.h"
    #include "Texture.h"
    #include <glm/glm.hpp>
    #include <vector>



    namespace clm{

    class Calamity
    {
    Window& window;
    Shader& shader;
    VertexArray va;
    IndexBuffer ib;
    Renderer renderer;


    std::vector<float> vertexData;
    std::vector<GLuint> indicesData;
    public: 
        Calamity(Window& window,Shader& shader);
        ~Calamity();
        void Render();
        void DrawRect(float x,float y,float w,float h);
        void DrawTriangle();

        void UpdateData();
    };

    }// namespace clm