#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>

namespace UE
{
	class NodePin
	{
	public:
		enum Type
		{
			Invalid = 0,
			Boolean = 1,
			Number = 2
		};

	public:
		struct Descriptor {
			//ax::NodeEditor::PinId Id;
			ax::NodeEditor::PinKind Kind;
			NodePin::Type Type;
			UEString Text;
			ax::NodeEditor::NodeId Parent;
		};
		
	public:
		NodePin(NodePin::Descriptor descriptor);
		~NodePin();

		void Render(UEUint32 relative);
	public:
		static UEUint32 s_PinIds;
		NodePin::Descriptor m_Descriptor;
	};
}