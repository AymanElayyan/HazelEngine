#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Hazel/Core/Timestep.h"

#include "ImGui/ImGuiLayer.h"

namespace Hazel {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}