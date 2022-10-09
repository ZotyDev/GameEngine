#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

// Todo:
// Remove the need for register and merge it inside set

namespace UE
{
	class Material
	{
	public:
		Material();
		Material(const UEString& shader);
		~Material();

		void Bind();

		void SetShader(Ref<Shader> shader);
		void PushTexture(Ref<Texture> texture);

		Ref<Shader> GetShader() { return m_Shader; }
	private:
		Ref<Shader> m_Shader;
		std::vector<Ref<Texture>> m_Textures;
	};
}