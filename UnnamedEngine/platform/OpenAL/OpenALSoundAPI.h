#pragma once

#include "Sound/SoundAPI.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace UE
{
	bool CheckAlcError(ALCdevice* device);

	bool CheckAlError();

	class OpenALSoundAPI : public SoundAPI
	{
	public:
		OpenALSoundAPI();
		virtual ~OpenALSoundAPI() override;

		virtual UEResult<> Init() override;
	private:
		ALCdevice* m_SoundDevice;
		ALCcontext* m_SoundContext;
	};
}