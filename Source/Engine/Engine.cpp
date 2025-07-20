#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

namespace viper {
	Engine& GetEngine() {
		static Engine instance;
		return instance;
	}

	bool Engine::Initialize() {
		// create renderer
		m_renderer = std::make_unique<viper::Renderer>();
		if (!m_renderer->Initialize()) return false;
		if (!m_renderer->CreateWindow("Viper Engine", 1280, 1024)) return false;

		// create input system
		m_input = std::make_unique<viper::InputSystem>();
		if (!m_input->Initialize()) return false;

		// create audio system
		m_audio = std::make_unique<viper::AudioSystem>();
		if (!m_audio->Initialize()) return false;

		return true;
	}

	void Engine::Shutdown() {
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();

		m_audio->Update();
		m_input->Update();
	}

	void Engine::Draw()	{
		m_renderer->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_renderer->Clear();

		m_renderer->Present();
	}
}