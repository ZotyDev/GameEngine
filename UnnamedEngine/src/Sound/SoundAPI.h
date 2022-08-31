#pragma once

namespace UE
{
	class SoundAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenAL = 1,
		};

	public:
		virtual ~SoundAPI() = default;

		virtual UEResult<> Init() = 0;

		static API GetAPI() { return s_API; }
		static Scope<SoundAPI> Create();
	private:
		static API s_API;
	};
}