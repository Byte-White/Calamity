#pragma once
#include "Calamity/Shader.h"
#include <iostream>

namespace clm
{
    Shader::Shader()
    {}
    Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
    {    
        CompileShaders(vertexShaderSource,fragmentShaderSource);
    }

    void Shader::CompileShaders(const char* vertexShaderSource,const char* fragmentShaderSource)
    {
        
        GLuint vertexShader,fragmentShader;
        // compile shaders
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        GLint success;
        GLchar infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            // Handle compilation error
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            // Handle compilation error
        }
        // link shaders
        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);
        
        // Check for program linking errors
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            std::cerr<<"Shader Error: " << infoLog << std::endl;// Handle linking error
        }
            
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    Shader::~Shader()
    {
        glDeleteProgram(programID);
    }
    
    void Shader::Use() const
    {
        glUseProgram(programID);
    }
// -------------------------UNIFORMS------------------------------
    int Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        int location = glGetUniformLocation(programID, name.c_str());
        if (location == -1)
            std::cerr << "No active uniform variable with name " << name << " found" << std::endl;

        m_UniformLocationCache[name] = location;

        return location;
    }

    void Shader::SetUniform1i(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
    {
        glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
    }
    void Shader::SetUniform4f(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(GetUniformLocation(name), value.r, value.g, value.b, value.a);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
}