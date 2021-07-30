#pragma once

#include "Sound/SoundAPI.h"

#include <glm/glm.hpp>

namespace UE
{
	class SoundListener
	{
	public:
		virtual ~SoundListener() = default;

		virtual UEResult MakeCurrent() = 0;

		virtual UEResult SetGain(float gain) = 0;
		virtual UEResult SetPosition(const glm::vec3& position) = 0;
		virtual UEResult SetVelocity(const glm::vec3& velocity) = 0;
		virtual UEResult SetOrientation(const glm::quat& orientation) = 0;

		virtual const float& GetGain() = 0;
		virtual const glm::vec3& GetPosition() = 0;
		virtual const glm::vec3& GetVelocity() = 0;
		virtual const glm::quat& GetOrientation() = 0;

		static Ref<SoundListener> Create();
	};
}