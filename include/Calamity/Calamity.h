#ifndef CALAMITY_H
#define CALAMITY_H

#include "Renderer.h"
#include "Vertex.h"
#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "Framebuffer.h"
#include <glm/glm.hpp>
#include <vector>



namespace clm{
// TODO: Make it useful
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
    void DrawTestTriangle();

    void UpdateData();
};

}// namespace clm
#endif // CALAMITY_H