#pragma once

#include "Scene/Scene.h"

namespace UE
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		UEResult<> Serialize(const UEPath& path);

		UEResult<> Deserialize(const UEPath& path);

	private:
		Ref<Scene> m_Scene;
	};
}