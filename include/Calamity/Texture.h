#ifndef CALAMITY_TEXTURE_H
#define CALAMITY_TEXTURE_H
#include <glad/glad.h>
#include "stb_image.h"
#include <string>

namespace clm
{
    enum class TextureFormat{
        None = 0,
        Red,
        RGB,
        RGBA
    };
    class Texture
    {
        public:
        private:
            unsigned int m_RendererID;
            std::string m_FilePath;
            int m_Width, m_Height, m_BPP;
        public:
            Texture();
            Texture(const std::string& path,TextureFormat format = TextureFormat::None);
            Texture(int width, int height,TextureFormat format, const void* data = nullptr);
            void SetData(void* data);
            void Resize(int width,int height);
            void LoadImage(const std::string& path,TextureFormat format = TextureFormat::None);
            ~Texture();
            
            void Bind(unsigned int slot = 0) const;
            static void Unbind();

            inline int GetWidth() const { return m_Width; }
            inline int GetHeight() const { return m_Height; }
    };
} // namespace clm
#endif // CALAMITY_TEXTURE_H