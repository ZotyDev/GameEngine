#include "uepch.h"
#include "RenderCommand.h"

namespace UE 
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}