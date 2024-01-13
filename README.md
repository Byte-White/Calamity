# Calamity

[![Build Status](https://github.com/Byte-White/Calamity/workflows/build/badge.svg)](https://github.com/Byte-White/Calamity/actions)

an OpenGL abstraction with GLFW, GLAD, GLM and stbimage

![clm](https://github.com/Byte-White/Calamity/assets/51212450/17c5b11b-d476-4439-ae14-c2b26ea1374a)

## How To Use

`git clone --recursive https://github.com/Byte-White/Calamity/` in your project folder and add it as a subdirectory in your `CMakeLists.txt`

## Example Code

### Triangle

main.cpp
```cpp
#include "Calamity/Calamity.h"
#include <iostream>


// Simple vertex shader
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Simple fragment shader
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main() 
{
    if(clm::CalamityInit() == CALAMITY_FAILED)
    {
        std::cerr<<"Calamity Init Failed.\n";
        return 1;
    }
        std::cout<<"Calamity Inited Successfully.\n";
    
    clm::Window window(600,400,"Calamity");

    clm::Shader shader(vertexShaderSource,fragmentShaderSource);

    // Define the vertices of a colored triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
         0.5f, -0.5f, 0.0f, // Bottom right
         0.0f,  0.5f, 0.0f  // Top center
    };
    GLuint indices[] = { 0, 1, 2 }; // Indices for a single triangle

    // Create Vertex Array Object (VAO)
    clm::VertexBufferLayout layout;
    layout.AddFloat(3); // xyz
    clm::VertexArray vertexArray(vertices,3,layout);

    // Create an IndexBuffer
    clm::IndexBuffer indexBuffer(indices, 3);

    clm::Renderer renderer;
    // Main loop
    while (!window.ShouldClose()) {
        renderer.Clear();
        renderer.Draw(vertexArray,indexBuffer,shader,3);
        window.SwapBuffers();
        window.PollEvents();
    }

    clm::CalamityDestroy();
    return 0;
}
```
![image](https://github.com/Byte-White/Calamity/assets/51212450/4391c607-9565-4545-9f29-666e9dab13b0)

### Rotating Cube
main.cpp
```cpp
#include "Calamity/Calamity.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

// Vertex shader with perspective projection
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 u_MVP; // Model-View-Projection matrix

    void main() {
        gl_Position = u_MVP * vec4(aPos, 1.0);
    }
)";

// Simple fragment shader
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main() 
{
    if(clm::CalamityInit() == CALAMITY_FAILED)
    {
        std::cerr<<"Calamity Init Failed.\n";
        return 1;
    }
    std::cout<<"Calamity Inited Successfully.\n";
    
    clm::Window window(800, 600, "Rotating Cube - Calamity");

    clm::Shader shader(vertexShaderSource, fragmentShaderSource);

    // Define the vertices of a colored cube
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3
        -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f  // 7
    };
    GLuint indices[] = {
        0, 1, 2, 2, 3, 0, // Front face
        4, 5, 6, 6, 7, 4, // Back face
        0, 3, 7, 7, 4, 0, // Left face
        1, 2, 6, 6, 5, 1, // Right face
        0, 1, 5, 5, 4, 0, // Bottom face
        2, 3, 7, 7, 6, 2  // Top face
    };

    // Create Vertex Array Object (VAO)
    clm::VertexBufferLayout layout;
    layout.AddFloat(3); // xyz
    clm::VertexArray vertexArray(vertices, 8, layout);

    // Create an IndexBuffer
    clm::IndexBuffer indexBuffer(indices, 36);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::mat4(1.0f);

    clm::Renderer renderer;

    // Main loop
    while (!window.ShouldClose()) {
        // Rotate the cube
        float angle = glm::radians(45.0f) * static_cast<float>(glfwGetTime());
        model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp = proj * view * model;

        // Set the MVP matrix in the shader
        shader.Use();
        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Clear();
        renderer.Draw(vertexArray, indexBuffer, shader, 36);
        window.SwapBuffers();
        window.PollEvents();
    }

    clm::CalamityDestroy();
    return 0;
}

```

![image](https://github.com/Byte-White/Calamity/assets/51212450/bd3a11d2-3544-4cf8-8af2-88580402997d)


https://github.com/Byte-White/Calamity/assets/51212450/dbe6f2ec-0d39-4cc2-b586-6b88c990b498


## Created with this library

# DOOMED - Graphics Library
![image](https://github.com/Byte-White/Calamity/assets/51212450/83be58a1-ffd6-42dd-a3a4-cad45d27e3f8)

![image](https://github.com/Byte-White/Calamity/assets/51212450/d1c3a304-3fb3-42dd-9882-0eae9519ef50)

# Destruction - Graphics Library

![image](https://github.com/Byte-White/Calamity/assets/51212450/138129a8-9902-40ea-abef-0d478058ec9e)

![image](https://github.com/Byte-White/Calamity/assets/51212450/b98922bd-a020-4669-9ce7-3b28a31191ba)

![image](https://github.com/Byte-White/Calamity/assets/51212450/5bc3331d-af5c-456c-989d-1cbc176a7137)
