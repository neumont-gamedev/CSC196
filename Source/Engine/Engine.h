#pragma once
#include "Core/Time.h"
#include <memory>

namespace viper {
	class AudioSystem;
	class InputSystem;
	class Renderer;

	class Engine {
	public:
		Engine() = default;
		~Engine() = default;

		bool Initialize();
		void Shutdown();
		void Update();

		void Draw();

		const Time& GetTime() { return m_time; }

		AudioSystem& GetAudio() { return *m_audio; }
		InputSystem& GetInput() { return *m_input; }
		Renderer& GetRenderer() { return *m_renderer; }

	private:
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<Renderer> m_renderer;

		Time m_time;
	};

	Engine& GetEngine();
}
