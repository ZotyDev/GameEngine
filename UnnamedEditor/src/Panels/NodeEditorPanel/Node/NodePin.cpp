#include "uepch.h"
#include "Panels/NodeEditorPanel/Node/NodePin.h"

namespace UE
{
	std::vector<ImColor> PinColorTable = {
		{0.0f, 0.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f, 1.0f},
		{0.23f, 1.0f, 0.23f, 1.0f},
	};

	UEUint32 NodePin::s_PinIds = 10;

	NodePin::NodePin(NodePin::Descriptor descriptor)
		: m_Descriptor(descriptor)
	{}

	NodePin::~NodePin()
	{}

	void NodePin::Render(UEUint32 relative)
	{
		ax::NodeEditor::BeginPin(s_PinIds, m_Descriptor.Kind);

		// Some helpers
		ImVec2 NodePosition = ax::NodeEditor::GetNodePosition(m_Descriptor.Parent);
		ImVec2 NodeSize = ax::NodeEditor::GetNodeSize(m_Descriptor.Parent);
		UEFloat StartPosition = 18.0f;
		UEFloat PinVerticalSize = 22.0f;
		ImColor PinColor = PinColorTable[m_Descriptor.Type];

		if (m_Descriptor.Kind == ax::NodeEditor::PinKind::Input)
		{
			ax::NodeEditor::PinPivotAlignment(ImVec2(0.05f, 0.55f));
			ax::NodeEditor::PinPivotSize(ImVec2(0.0f, 0.0f));

			ImVec2 PinIconCenter(NodePosition.x + 15.0f, NodePosition.y + StartPosition + (PinVerticalSize * UEFloat(relative)));

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			if (ax::NodeEditor::PinHadAnyLinks(s_PinIds))
			{
				draw_list->AddCircleFilled(PinIconCenter, 5.0f, PinColor, 0);
			}
			else
			{
				draw_list->AddCircle(PinIconCenter, 5.0f, PinColor, 0, 2.0f);
			}
		
			ImGui::Dummy(ImVec2(10.0f, 0.0f));
			ImGui::SameLine();
			ImGui::Text(m_Descriptor.Text.c_str());
		}
		else
		{
			ImVec2 TextSize = ImGui::CalcTextSize(m_Descriptor.Text.c_str());
			ax::NodeEditor::PinPivotAlignment(ImVec2(0.95f, 0.55f));
			ax::NodeEditor::PinPivotSize(ImVec2(0.0f, 0.0f));

			ImVec2 PinIconCenter(NodePosition.x + NodeSize.x - 15.0f, NodePosition.y + StartPosition + (PinVerticalSize * UEFloat(relative)));

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			if (ax::NodeEditor::PinHadAnyLinks(s_PinIds))
			{
				draw_list->AddCircleFilled(PinIconCenter, 5.0f, PinColor, 0);
			}
			else
			{
				draw_list->AddCircle(PinIconCenter, 5.0f, PinColor, 0, 2.0f);
			}
			
			ImGui::Text(m_Descriptor.Text.c_str());
			ImGui::SameLine();
			ImGui::Dummy(ImVec2(10.0f, 0.0f));			
		}

		

		ax::NodeEditor::EndPin();

		s_PinIds++;
	}
}