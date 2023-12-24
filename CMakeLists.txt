project(Calamity)

add_subdirectory(vendor)

add_library(
    ${PROJECT_NAME}
    STATIC   
    src/Renderer.cpp
    src/Shader.cpp
    src/Vertex.cpp
    src/Window.cpp
    src/Calamity.cpp
    src/Texture.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    glfw
    glm
    stb_image
)

add_library(calamity ALIAS ${PROJECT_NAME})