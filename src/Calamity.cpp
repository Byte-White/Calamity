#include"Calamity/Calamity.h"
#include <iostream>

namespace clm
{
    int CalamityInit()
    {
        // Initialize GLFW
        if (!glfwInit()) {
            return CALAMITY_FAILED;
        }
        // version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Request OpenGL 4.x
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // Request OpenGL x.5
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Request a core profile
        
        return CALAMITY_OK;
    }
    void CalamityDestroy()
    {
        glfwTerminate();
    }
} // namespace clm
