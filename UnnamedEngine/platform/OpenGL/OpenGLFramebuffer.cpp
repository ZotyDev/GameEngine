#include "uepch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace UE
{
	namespace Utils
	{
		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(UEBool multisampled, UEUint32* outID, UEUint32 count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(UEBool multisampled, UEUint32 id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(UEUint32 id, UEUint32 samples, GLenum internalFormat, GLenum format, UEUint32 width, UEUint32 height, UEUint32 index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(UEUint32 id, UEUint32 samples, GLenum format, GLenum attachmentType, UEUint32 width, UEUint32 height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case UE::FramebufferTextureFormat::DEPTH24STENCIL8: return true;
			}

			return false;
		}

		static GLenum ueFramebufferTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case UE::FramebufferTextureFormat::RGBA8: return GL_RGBA8;
			}

			UE_CORE_ERROR("Unknown Framebuffer format!");
			return 0;
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specs) : m_Specification(specs)
	{
		for (auto spec : m_Specification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
			{
				m_ColorAttachmentSpecifications.emplace_back(spec);
			}
			else
			{
				m_DepthAttachmentSpecification = spec;
			}
		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_ID)
		{
			glDeleteFramebuffers(1, &m_ID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		UEBool multisampled = m_Specification.Samples > 1;

		// Attachments
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multisampled, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (UEUint32 i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisampled, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
						break;
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisampled, &m_DepthAttachment, 1);
			Utils::BindTexture(multisampled, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			GLenum buffers[4] =
			{
				GL_COLOR_ATTACHMENT0,
				GL_COLOR_ATTACHMENT1,
				GL_COLOR_ATTACHMENT2,
				GL_COLOR_ATTACHMENT3
			};
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			glDrawBuffer(GL_NONE);
		}

		if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
		{
			UE_CORE_ERROR("Framebuffer is incomplete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind(FramebufferBindMode mode)
	{
		switch (mode)
		{
		case UE::FramebufferBindMode::Read:
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
			break;
		case UE::FramebufferBindMode::Draw:
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
			break;
		case UE::FramebufferBindMode::Default:
		default:
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
			break;
		}
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::BlitInto(Ref<Framebuffer> target)
	{
		Bind(FramebufferBindMode::Read);
		target->Bind(FramebufferBindMode::Draw);
		glBlitFramebuffer(
			0, 0, m_Specification.Width, m_Specification.Height,
			0, 0, m_Specification.Width, m_Specification.Height,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	UEUint32 OpenGLFramebuffer::GetWidth()
	{
		return m_Specification.Width;
	}

	UEUint32 OpenGLFramebuffer::GetHeight()
	{
		return m_Specification.Height;
	}

	void OpenGLFramebuffer::BindColorAttachment(UEUint32 index, UEUint32 slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(Utils::TextureTarget(m_Specification.Samples > 1), GetColorAttachmentRendererID(index));
	}

	void OpenGLFramebuffer::BindDepthAttachment(UEUint32 slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(Utils::TextureTarget(m_Specification.Samples > 1), m_DepthAttachment);
	}

	void OpenGLFramebuffer::Resize(UEUint32 width, UEUint32 height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;

		Invalidate();
	}

	void OpenGLFramebuffer::ClearAttachment(UEUint32 attachmentIndex, UEUint32 value)
	{
		if (attachmentIndex > m_ColorAttachments.size())
		{
			UE_CORE_ERROR("Index out of range!");
			return;
		}

		auto& spec = m_ColorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0, Utils::ueFramebufferTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
	}

	UEUint32 OpenGLFramebuffer::GetColorAttachmentRendererID(UEUint32 index) const
	{
		if (index > m_ColorAttachments.size())
		{
			UE_CORE_ERROR("Index out of range!");
			return 0;
		}

		return m_ColorAttachments[index];
	}
}