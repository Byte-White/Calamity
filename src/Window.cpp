#include "Calamity/Window.h"
#include <iostream>

namespace clm
{
    
    void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            std::cerr << "OpenGL Error: " << message << "" << std::endl;
            std::cout << "Source: " << source << ", Type: " << type << ", ID: " << id << ", Severity: " << severity << std::endl;
    }



    Window::Window(int width, int height, const char* title)
    :width(width),height(height)
    {
        static bool gladisloaded = false;
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(1);
        }
        glfwMakeContextCurrent(window);
        if(!gladisloaded)
        {   
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
            {
                std::cerr<< "Couldn't load glad.\n";
                glfwTerminate();
                exit(1);
            }


            const GLubyte* glVersion = glGetString(GL_VERSION);
            if (glVersion) {
                std::cout << "OpenGL Version: " << glVersion << std::endl;
            } else {
                std::cerr << "Failed to retrieve OpenGL version" << std::endl;
            }

            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(errorCallback, nullptr);
            gladisloaded = true;
        }
    }
    Window::~Window()
    {

    }
    
    int Window::ShouldClose()
    {
        return glfwWindowShouldClose(window);
    }
    void Window::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }
    void Window::PollEvents()
    {
        glfwPollEvents();
    }
}