#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("SandBox2D"), m_CameraController(1288.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/Texture/Checkerboard.png");

	// Smoke
	m_SmokeParticle.Position = { 0.0f, 0.0f };
	m_SmokeParticle.Velocity = { -2.0f, 0.0f }, m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
	m_SmokeParticle.SizeBegin = 0.35f, m_SmokeParticle.SizeEnd = 0.0f, m_SmokeParticle.SizeVariation = 0.15f;
	m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.LifeTime = 4.0f;


}

void Sandbox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazel::Renderer2D::ResetStats();

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 0.1f });
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f,{0.0f, 0.0f, 0.0f, 0.0f});
	Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
	//Hazel::Renderer2D::EndScene();

	//Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.1f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.1f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
			Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}

	Hazel::Renderer2D::EndScene();


	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}


void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::Text("Renderer2D Stats:");
	auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertices  : %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices   : %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));  // Allow color change
	ImGui::End();
}


void Sandbox2D::OnEvent(Hazel::Event& e)
{
	HZ_PROFILE_FUNCTION();
	m_CameraController.OnEvent(e);
}
