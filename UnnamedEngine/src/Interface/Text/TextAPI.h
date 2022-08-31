#pragma once

namespace UE
{
	class TextAPI
	{
	public:
		enum class API
		{
			None = 0,
			FreeType = 1
		};

	public:
		virtual ~TextAPI() = default;

		virtual UEResult<> Init() = 0;

		virtual void* GetRawLibrary() = 0;

		static API GetAPI() { return s_API; }
		static Scope<TextAPI> Create();
	private:
		static API s_API;
	};
}