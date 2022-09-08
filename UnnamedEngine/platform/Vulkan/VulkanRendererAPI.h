#pragma once

#include "Renderer/RendererAPI.h"

#include "Vulkan/VulkanDevice.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace UE
{
	class VulkanRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(UEUint32 x, UEUint32 y, UEUint32 width, UEUint32 height) override;
		virtual void GetViewport(UEUint32& width, UEUint32& height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void ClearDepth() override;
		virtual void CullFront() override;
		virtual void CullBack() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, UEUint32 indexCount = 0) override;
	public:
		VulkanDevice Device;
	};
}