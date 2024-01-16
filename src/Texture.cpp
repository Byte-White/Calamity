#include "Calamity/Texture.h"
#include <string>
#include "stb_image.h"
#include <iostream>

namespace clm
{
    Texture::Texture()
    {
        glGenTextures(1, &m_RendererID);
    }

    Texture::Texture(const std::string& path,TextureFormat format)
        : m_RendererID(0), m_FilePath(path), m_Width(0), m_Height(0), m_BPP(0)
    {
        glGenTextures(1, &m_RendererID);
        LoadImage(path);
    }

    
    void Texture::LoadImage(const std::string& path,TextureFormat format)
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        stbi_set_flip_vertically_on_load(1);
        unsigned char* m_LocalBuffer = nullptr;
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
        if (!m_LocalBuffer)
        {
            std::cout<<"Can't load texture '"<<path<<"' - "<<stbi_failure_reason();
        }
        

        // Set texture parameters for wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Provide the texture data
        if (m_LocalBuffer)
        {
            GLenum internalFormat, dataFormat;
            // Check what type of color channels the texture has and load it accordingly
            if(format == TextureFormat::None)
            {
                switch (m_BPP)
                {
                case 4:
                    internalFormat = GL_RGBA;
                    dataFormat = GL_RGBA;
                    break;
                case 3:
                    internalFormat = GL_RGB;
                    dataFormat = GL_RGB;
                    break;
                case 1:
                    internalFormat = GL_RED;
                    dataFormat = GL_RED;
                    break;
                default:
                    throw std::invalid_argument("Automatic Texture type recognition failed");
                }
            }
            else
            {
                switch (format)
                {
                case TextureFormat::RGBA:
                    internalFormat = GL_RGBA;
                    dataFormat = GL_RGBA;
                    break;
                case TextureFormat::RGB:
                    internalFormat = GL_RGB;
                    dataFormat = GL_RGB;
                    break;
                case TextureFormat::Red:
                    internalFormat = GL_RED;
                    dataFormat = GL_RED;
                    break;
                }
            }
            

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                internalFormat,
                m_Width,
                m_Height,
                0,
                dataFormat,
                GL_UNSIGNED_BYTE,
                m_LocalBuffer);

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
Texture::Texture(int width, int height, TextureFormat format, const void *data)
        : m_RendererID(0), m_Width(width), m_Height(height), m_BPP(0)
    {
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        GLenum internalFormat, dataFormat;

        switch (format)
        {
        case TextureFormat::Red:
            internalFormat = GL_RED;
            dataFormat = GL_RED;
            m_BPP = 1;
            break;
        case TextureFormat::RGB:
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
            m_BPP = 3;
            break;
        case TextureFormat::RGBA:
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
            m_BPP = 4;
            break;
        default:
            throw std::invalid_argument("Invalid TextureFormat");
        }


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                internalFormat,
                m_Width,
                m_Height,
                0,
                dataFormat,
                GL_UNSIGNED_BYTE,
                data);

            glGenerateMipmap(GL_TEXTURE_2D);
        }

        Unbind();
    }

    void Texture::SetData(void *data)
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Set texture parameters for wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Provide the texture data if available
        if (data)
        {
            GLenum internalFormat, dataFormat;

            switch (m_BPP)
            {
            case 4:
                internalFormat = GL_RGBA;
                dataFormat = GL_RGBA;
                break;
            case 3:
                internalFormat = GL_RGB;
                dataFormat = GL_RGB;
                break;
            case 1:
                internalFormat = GL_RED;
                dataFormat = GL_RED;
                break;
            default:
                throw std::invalid_argument("Automatic Texture type recognition failed");
            }

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                internalFormat,
                m_Width,
                m_Height,
                0,
                dataFormat,
                GL_UNSIGNED_BYTE,
                data);

            // Generate Mipmap for better texture quality
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Invalid data provided for SetData" << std::endl;
        }

        // Unbind the texture to avoid mistakes
        Unbind();
    }


    void Texture::Resize(int width, int height)
    {
        m_Width = width;
        m_Height = height;

        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Set texture parameters for wrapping and filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Allocate space for the new texture without loading data
        GLenum internalFormat, dataFormat;
        switch (m_BPP)
        {
        case 4:
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
            break;
        case 3:
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
            break;
        case 1:
            internalFormat = GL_RED;
            dataFormat = GL_RED;
            break;
        default:
            throw std::invalid_argument("Automatic Texture type recognition failed");
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            internalFormat,
            m_Width,
            m_Height,
            0,
            dataFormat,
            GL_UNSIGNED_BYTE,
            nullptr); // Pass nullptr as data to allocate space without initializing

        // Unbind the texture to avoid mistakes
        Unbind();
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

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace clm
