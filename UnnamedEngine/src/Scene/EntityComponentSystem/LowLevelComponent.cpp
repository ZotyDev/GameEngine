#include "uepch.h"
#include "Scene/EntityComponentSystem/LowLevelComponent.h"

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace UE
{
	glm::mat4 TransformComponent::GetTransform() const
	{
		glm::mat4 MatRotation = glm::toMat4(glm::quat(Rotation));

		return glm::translate(glm::mat4(1.0f), Translation) * MatRotation * glm::scale(glm::mat4(1.0f), Scale);
	}
}