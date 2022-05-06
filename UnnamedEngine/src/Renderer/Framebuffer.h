#pragma once

#include "Core/Base.h"

namespace UE
{
	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Color = RGBA8,
		Depth = DEPTH24STENCIL8
	};

	enum class FramebufferBindMode
	{
		Default = 0,
		Read = 1,
		Draw = 2,
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) 
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		UEUint32 Width = 0;
		UEUint32 Height = 0;
		FramebufferAttachmentSpecification Attachments;
		UEUint32 Samples = 1;
		UEBool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind(FramebufferBindMode mode = FramebufferBindMode::Default) = 0;
		virtual void Unbind() = 0;

		virtual void BlitInto(Ref<Framebuffer> target) = 0;

		virtual UEUint32 GetWidth() = 0;
		virtual UEUint32 GetHeight() = 0;

		virtual void BindColorAttachment(UEUint32 index = 0, UEUint32 slot = 0) = 0;

		virtual void BindDepthAttachment(UEUint32 slot = 0) = 0;

		virtual void Resize(UEUint32 width, UEUint32 height) = 0;

		virtual void ClearAttachment(UEUint32 attachmentIndex, UEUint32 value) = 0;

		virtual UEUint32 GetColorAttachmentRendererID(UEUint32 index = 0) const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specs);
	};
}