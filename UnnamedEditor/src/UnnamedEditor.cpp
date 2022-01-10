#include <UnnamedEngine.h>
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

namespace UE
{
	class UnnamedEditor : public Application
	{
	public:
		UnnamedEditor()
		{
			PushLayer(new EditorLayer(m_Data));
		}

		~UnnamedEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new UnnamedEditor();
	}
}