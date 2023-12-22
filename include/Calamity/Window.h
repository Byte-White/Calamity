#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CALAMITY_OK     (0)
#define CALAMITY_FAILED (1)

namespace clm
{
    // returns CALAMITY_OK if initialized successfully
    // returns CALAMITY_FAILED on failure
    int CalamityInit();
    void CalamityDestroy();

    class Window 
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        int ShouldClose();
        void SwapBuffers();
        void PollEvents();
    private:
        GLFWwindow* window;
    };
}