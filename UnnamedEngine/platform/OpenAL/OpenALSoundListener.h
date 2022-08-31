#pragma once

#include "Sound/SoundListener.h"

#include "OpenAL/OpenALSoundAPI.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <AL/al.h>
#include <AL/alc.h>

namespace UE
{
	class OpenALSoundListener : public SoundListener
	{
	public:
		OpenALSoundListener();
		virtual ~OpenALSoundListener() override;

		virtual UEResult<> MakeCurrent() override;

		virtual UEResult<> SetGain(float gain) override;
		virtual UEResult<> SetPosition(const glm::vec3& position) override;
		virtual UEResult<> SetVelocity(const glm::vec3& velocity) override;
		virtual UEResult<> SetOrientation(const glm::quat& orientation) override;

		virtual const float& GetGain() override { return m_Gain; }
		virtual const glm::vec3& GetPosition() { return m_Position; }
		virtual const glm::vec3& GetVelocity() override { return m_Velocity; }
		virtual const glm::quat& GetOrientation() override { return m_Orientation; }

	private:
		float m_Gain;
		glm::vec3 m_Position;
		glm::vec3 m_Velocity;
		glm::quat m_Orientation;
	private:
		static OpenALSoundListener* s_CurrentContext;
	};
}