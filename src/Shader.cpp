#pragma once
#include "Calamity/Shader.h"
#include <iostream>

namespace clm
{
    Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
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
}