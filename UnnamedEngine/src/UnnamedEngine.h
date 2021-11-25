#pragma once

/* PCH */
/*============================================================*/
#include <uepch.h>

/* Essential */
/*============================================================*/
#include "Core/Base.h"
#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Log.h"

#include "Core/Assert.h"

#include "Core/Timestep.h"

/* Math */
/*============================================================*/
#include "Math/Random/Salt.h"

/* Time */
/*============================================================*/
#include "Time/localTime.h"
#include "Time/Stopwatch.h"

/* Event */
/*============================================================*/
#include "Events/Event.h"
#include "Events/GamepadEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

/* ECS */
/*============================================================*/
#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "ECS/System.h"

/* Script */
/*============================================================*/
#include "Script/Lune/LuneAPI.h"
#include "Script/Lune/LuneFunction.h"
#include "Script/Lune/LuneClass.h"
#include "Script/Lune/LuneModule.h"

/* Renderer */
/*============================================================*/
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Screen.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Renderer3D.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"

#include "Renderer/Material.h"

#include "Renderer/Camera.h"
#include "Renderer/Camera3D.h"
#include "Renderer/CameraController.h"

#include "Renderer/Primitives.h"

/* Input */
/*============================================================*/
#include "Input/keyBoard.h"

/* Core Lua */
/*============================================================*/