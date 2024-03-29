#ifndef CALAMITY_WINDOW_H
#define CALAMITY_WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CALAMITY_OK     (0)
#define CALAMITY_FAILED (1)

namespace clm
{

    class Window 
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        int ShouldClose();
        void SwapBuffers();
        void PollEvents();

        inline int GetWidth()
        {
            glfwGetWindowSize(window,&width,&height);
            return width;
        }
        inline int GetHeight()
        {
            glfwGetWindowSize(window,&width,&height);
            return height;
        }
        inline GLFWwindow* GetGLFWWindow()
        {
            return window;
        }
    private:
        int width,height;
        GLFWwindow* window;
    };
}
#endif // CALAMITY_WINDOW_H