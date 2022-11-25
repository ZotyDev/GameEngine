#include "uepch.h"
#include "Panels/ProfilerPanel.h"
#include "EditorConfig.h"
#include "Project/Project.h"

#include "Debug/Instrumentator.h"

#include <imgui.h>
#include <implot.h>

namespace UE
{
	ProfilerPanel::ProfilerPanel()
	{}

	void ProfilerPanel::OnImGuiRender()
	{
		if (ActivePanelsConfig::Profiler && !(PanelsConfig::MaximizeOnPlay && ProjectConfig::ProjectRunning) && Project::Header::IsOpen)
		{
			ImGui::Begin("Profiler");
			ImGui::BeginChild("##profiler");

			UEUint32 DataSize = Instrumentator::GetProfileResults()->size();
			UEFloat PieData[] = { 0.15f, 0.3f, 0.5f };
			std::vector<const UEChar*> DataLabels;
			std::vector<UEFloat> DataValues;
			auto Container = Instrumentator::GetProfileResults();

			UEUint32 Helper = 0;
			for (int i = 0; i < DataSize; i++)
			{
				DataLabels.push_back(Container->at(i).Name.c_str());
				DataValues.push_back(Container->at(i).Time);
			}

			static bool normalize = true;
			ImPlot::PushColormap(ImPlotColormap_Viridis);
			if (ImPlot::BeginPlot("##ProfilerPieChart", ImVec2(350, 350), ImPlotFlags_Equal | ImPlotFlags_NoMouseText | ImPlotFlags_NoFrame | ImPlotFlags_NoMenus))
			{
				ImPlotAxisFlags PieFlags = ImPlotAxisFlags_NoMenus | ImPlotAxisFlags_Lock | ImPlotAxisFlags_NoDecorations;
				ImPlotLocation LegendLocation = ImPlotLocation_South;
				ImPlotLegendFlags LegendFlags = ImPlotLegendFlags_Outside | !ImPlotLegendFlags_Horizontal | ImPlotLegendFlags_NoMenus;
				ImPlot::SetupAxes(NULL, NULL, PieFlags, PieFlags);
				ImPlot::SetupAxesLimits(0, 1, 0, 1);
				ImPlot::SetupLegend(LegendLocation, LegendFlags);
				ImPlot::PlotPieChart(DataLabels.data(), DataValues.data(), DataSize, 0.5, 0.5, 0.35, normalize, "%.4f ms");
				ImPlot::EndPlot();
			}
			ImPlot::PopColormap();

			Instrumentator::Clear();

			ImGui::EndChild();
			ImGui::End();
		}
	}
}