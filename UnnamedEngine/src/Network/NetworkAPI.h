#pragma once

namespace UE
{
	class NetworkAPI
	{
	public:
		enum class API
		{
			None = 0,
			Winsock = 1
		};
	public:
		virtual ~NetworkAPI() = default;

		virtual void Init() = 0;

		static API GetAPI() { return s_API; }
		static Scope<NetworkAPI> Create();
	private:
		static API s_API;
	};
}