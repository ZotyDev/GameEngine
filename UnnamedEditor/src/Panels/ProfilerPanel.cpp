#include "uepch.h"
#include "Panels/ProfilerPanel.h"
#include "Panels/PanelsConfig.h"

#include "Debug/Instrumentator.h"

#include <imgui.h>

namespace UE
{
	ProfilerPanel::ProfilerPanel()
	{}

	void ProfilerPanel::OnImGuiRender()
	{
		if (PanelsShowConfig::ShowProfiler && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning))
		{
			ImGui::Begin("Profiler");
			ImGui::BeginChild("##profiler");

			for (auto& result : *Instrumentator::GetProfileResults())
			{
				ImGui::Text(("%.4fms " + result.Name).c_str(), result.Time);
			}
			Instrumentator::Clear();

			ImGui::EndChild();
			ImGui::End();
		}
	}
}