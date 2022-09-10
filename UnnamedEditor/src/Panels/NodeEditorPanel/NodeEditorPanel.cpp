#include "uepch.h"
#include "Panels/NodeEditorPanel/NodeEditorPanel.h"

#include <imgui.h>
#include <imgui_node_editor.h>

#include "Project/Project.h"
#include "Panels/PanelsConfig.h"

#include "Panels/NodeEditorPanel/Node/NodePin.h"

namespace ed = ax::NodeEditor;

namespace UE
{
	struct NodeEditorData
	{
		ed::EditorContext* Editor;
		ed::Config Config;
	};

	NodeEditorData EditorData;

	NodeEditorPanel::NodeEditorPanel()
	{
		// Set the configs for the node editor
		EditorData.Config.SettingsFile = "Simple.json";
		EditorData.Editor = ed::CreateEditor(&EditorData.Config);
	}

	NodeEditorPanel::~NodeEditorPanel()
	{}

	NodePin Pin1({ ed::PinKind::Input, NodePin::Type::Number, "Input", 1 });
	NodePin Pin2({ ed::PinKind::Output, NodePin::Type::Number, "Normalized Text", 1 });
	NodePin Pin3({ ed::PinKind::Input, NodePin::Type::Number, "Input", 2 });
	NodePin Pin4({ ed::PinKind::Output, NodePin::Type::Number, "Output", 2 });
	NodePin Pin5({ ed::PinKind::Input, NodePin::Type::Boolean, "Input", 2 });
	NodePin Pin6({ ed::PinKind::Output, NodePin::Type::Boolean, "Output", 2 });

	UEBool RunOnce = true;

	void NodeEditorPanel::OnImGuiRender()
	{
		if (ActivePanelsConfig::NodeEditor && !(PanelsConfig::MaximizeOnPlay && PanelsConfig::ProjectRunning) && Project::Header::IsOpen)
		{
			ImGui::Begin("Node Editor");

			ax::NodeEditor::SetCurrentEditor(EditorData.Editor);
			ax::NodeEditor::Begin("My Editor");
			UEUint32 UniqueID = 1;
			
			ax::NodeEditor::BeginNode(UniqueID++);
			
			ImGui::Text("Node A");
			
			Pin1.Render(1);
			ImGui::SameLine();
			Pin2.Render(1);
			
			ax::NodeEditor::EndNode();
			
			ax::NodeEditor::BeginNode(UniqueID++);
			
			ImGui::Text("Node B");
			
			Pin3.Render(1);
			ImGui::SameLine();
			Pin4.Render(1);

			Pin5.Render(2);
			ImGui::SameLine();
			Pin6.Render(2);
			
			ax::NodeEditor::EndNode();

			ax::NodeEditor::End();
			ax::NodeEditor::SetCurrentEditor(nullptr);

			ImGui::End();

			// Place this in a better place
			NodePin::s_PinIds = 10;
		}
	}
}