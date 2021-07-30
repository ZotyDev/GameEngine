#pragma once

#include "Sound/SoundAPI.h"
#include "Sound/Sound.h"

#include "Events/event.h"

namespace UE
{
	class SoundCommand
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static void Init()
		{
			s_SoundAPI->Init();
		}

		static void Play(const std::string& filename)
		{
			Ref<Sound> Music = Sound::Create();
			Music->LoadFromFile(filename);
		}

	private:
		static Scope<SoundAPI> s_SoundAPI;
	};
}