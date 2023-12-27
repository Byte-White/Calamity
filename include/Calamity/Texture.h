#ifndef CALAMITY_TEXTURE_H
#define CALAMITY_TEXTURE_H
#include <glad/glad.h>
#include "stb_image.h"
#include <string>

namespace clm
{
    class Texture
    {
        private:
            unsigned int m_RendererID;
            std::string m_FilePath;
            unsigned char* m_LocalBuffer;
            int m_Width, m_Height, m_BPP;

        public:
            Texture(const std::string& path);
            ~Texture();

            void Bind(unsigned int slot = 0) const;
            void Unbind() const;

            inline int GetWidth() const { return m_Width; }
            inline int GetHeight() const { return m_Height; }
    };
} // namespace clm
#endif // CALAMITY_TEXTURE_H