#include "Application.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace UE
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	Window* window;

	std::shared_ptr<VertexBuffer> vBuffer;
	std::shared_ptr<IndexBuffer> iBuffer;
	std::shared_ptr<VertexArray> vArray;

	Ref<ShaderLibrary> m_ShaderLibrary = CreateRef<ShaderLibrary>();

	void Application::Run()
	{
		LocalTime::Update();

		window = new WindowsWindow();
		window->Initialize("UnnamedEngine", 1280, 720);

		vArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		vBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout =
		{
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		vBuffer->SetLayout(layout);
		vArray->AddVertexBuffer(vBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		iBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vArray->AddIndexBuffer(iBuffer);

		m_ShaderLibrary->Load("data/shaders/default");

		while (!glfwWindowShouldClose((GLFWwindow*)window->GetNativeWindow()))
		{
			Update();
			Render();
		}

		glfwDestroyWindow((GLFWwindow*)window->GetNativeWindow());
		glfwTerminate();
	};

	void Application::Update()
	{
		Logger::ShowLog("tatest.log");
	};

	void Application::Render()
	{
		glClearColor(0.1f, 0.1, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		m_ShaderLibrary->Get("default")->Bind();
		vArray->Bind();
		glDrawElements(GL_TRIANGLES, iBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers((GLFWwindow*)window->GetNativeWindow());
		glfwPollEvents();
	};
}