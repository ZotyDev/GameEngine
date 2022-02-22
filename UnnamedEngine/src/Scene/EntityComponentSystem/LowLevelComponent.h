#pragma once

#include "Scene/EntityComponentSystem/Entity.h"

#include <glm/glm.hpp>

namespace UE
{
	struct TagComponent
	{
		UEString Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const UEString& tag)
			: Tag(tag)
		{}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation)
		{}

		glm::mat4 GetTransform() const;
	};
}