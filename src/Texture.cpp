#include "Calamity/Texture.h"
#include <string>
#include "stb_image.h"
#include <iostream>

namespace clm
{
    Texture::Texture(const std::string& path)
        : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
    {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
        if (!m_LocalBuffer)
        {
            std::cout<<"Can't load texture '"<<path<<"' - "<<stbi_failure_reason();
        }
        
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Set texture parameters for wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Provide the texture data
        if (m_LocalBuffer)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
            // Generate Mipmap for better texture quality
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            // Handle error or log a message if the image loading fails
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
        
        // std::cout<<"data: ";
        // for(int i = 0;i<m_Width*m_Height;i++)
        // {
        //     std::cout<<(int)m_LocalBuffer[i] << " ";
        // }
        // std::cout<<std::endl;
        
        // Unbind the texture to avoid mistakes
        Unbind();

        // Free the loaded image data
        if (m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace clm
