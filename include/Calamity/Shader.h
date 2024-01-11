#ifndef CALAMITY_SHADER_H
#define CALAMITY_SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace clm
{
    class Shader 
    {
    public:
        Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        Shader();
        ~Shader();

        void CompileShaders(const char* vertexShaderSource,const char* fragmentShaderSource);
        void Use() const;
        inline GLuint GetProgramID() const
        {
            return programID;
        }
        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
        void SetUniform4f(const std::string& name, const glm::vec4& value);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    private:
        GLuint programID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
        int GetUniformLocation(const std::string& name);
        struct ShaderProgramSource ParseShader(const std::string& filepath);
    };
}
#endif // CALAMITY_SHADER_H