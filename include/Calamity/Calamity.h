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



namespace clm
{
    // returns CALAMITY_OK if initialized successfully
    // returns CALAMITY_FAILED on failure
    int CalamityInit();
    void CalamityDestroy();    

}// namespace clm
#endif // CALAMITY_H