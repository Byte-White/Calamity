#ifndef CALAMITY_FRAMEBUFFER_H
#define CALAMITY_FRAMEBUFFER_H

#include "Renderer.h"

namespace clm
{

    struct FramebufferSpecification
    {
        unsigned int Width, Height;
        unsigned int Samples = 1;
        bool SwapChainTarget = false;
    };
    
    class Framebuffer
    {
    private:
        unsigned int m_Framebuffer, m_ColorAttachment, m_DepthAttachment;
        FramebufferSpecification m_Specification;
    public:
        Framebuffer(const FramebufferSpecification& spec);
        ~Framebuffer();

        void Resize();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetColorAttachment() const	{ return m_ColorAttachment; }
        void BindColorAttachment(unsigned int slot = 0);
        static void UnbindColorAttachment();
    };
} // namespace clm
#endif // CALAMITY_FRAMEBUFFER_H