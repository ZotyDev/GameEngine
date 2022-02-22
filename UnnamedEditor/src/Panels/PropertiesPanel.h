#pragma once

namespace UE
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel();

		void OnImGuiRender();
	private:
		UEString CurrentPath = "test";
		UEString CurrentFilenameExtension;

		UEUint32 Test = 0;
	};
}