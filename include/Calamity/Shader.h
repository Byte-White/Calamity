#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace clm
{
    class Shader 
    {
    public:
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        ~Shader();

        void Use() const;
        inline GLuint GetProgramID() const
        {
            return programID;
        }
    private:
        GLuint programID;
    };

}