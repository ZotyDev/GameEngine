#pragma once

#include "Renderer/Framebuffer.h"

namespace UE
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specs);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind(FramebufferBindMode mode) override;
		virtual void Unbind() override;

		virtual void BlitInto(Ref<Framebuffer> target) override;

		virtual UEUint32 GetWidth() override;
		virtual UEUint32 GetHeight() override;

		virtual void BindColorAttachment(UEUint32 index = 0, UEUint32 slot = 0) override;

		virtual void BindDepthAttachment(UEUint32 slot = 0) override;

		virtual void Resize(UEUint32 width, UEUint32 height) override;

		virtual void ClearAttachment(UEUint32 attachmentIndex, UEUint32 value) override;

		virtual UEUint32 GetColorAttachmentRendererID(UEUint32 index = 0) const override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		UEUint32 m_ID;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<UEUint32> m_ColorAttachments;
		UEUint32 m_DepthAttachment = 0;
	};
}