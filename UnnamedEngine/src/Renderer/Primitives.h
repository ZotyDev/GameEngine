#pragma once

#include "Core/Base.h"

#include "Renderer/VertexArray.h"

namespace UE
{
	namespace Primitives
	{
		struct Quad
		{
			Quad(glm::vec2 a, glm::vec2 c)
				: A(glm::vec3(a, 0.0f)), C(glm::vec3(c, 0.0f))
			{
				B = glm::vec3(A.x, C.y, 0.0f);
				D = glm::vec3(C.x, A.y, 0.0f);

				CreateVAO();
			}

			glm::vec3 A;
			glm::vec3 B;
			glm::vec3 C;
			glm::vec3 D;

			Ref<VertexArray> VAO;

		private:
			void CreateVAO()
			{
				VAO.reset(VertexArray::Create());

				Ref<VertexBuffer> t_VBuffer;
				Ref<IndexBuffer> t_IBuffer;

				float vertices[4 * 5] =
				{
					A.x, A.y, A.z, 0.0f, 1.0f,
					B.x, B.y, B.z, 0.0f, 0.0f,
					C.x, C.y, C.z, 1.0f, 0.0f,
					D.x, D.y, D.z, 1.0f, 1.0f
				};
				t_VBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

				BufferLayout layout =
				{
					{ShaderDataType::Vec3, "v_Position"},
					{ShaderDataType::Vec3, "v_Texture"},
				};
				t_VBuffer->SetLayout(layout);
				VAO->AddVertexBuffer(t_VBuffer);
				
				uint32_t indices[] = { 0, 1, 3, 1, 2, 3 };
				t_IBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
				VAO->AddIndexBuffer(t_IBuffer);
			}
		};
	}
}