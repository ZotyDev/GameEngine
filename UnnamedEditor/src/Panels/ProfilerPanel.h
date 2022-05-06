#pragma once

namespace UE
{
	struct ProfilerResult
	{
		UEString Name;
		UEFloat Time;
	};

	class ProfilerPanel
	{
	public:
		ProfilerPanel();

		void OnImGuiRender();
	};
}