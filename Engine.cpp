#include "Engine.h"

using namespace sf;

Engine::Engine()
{
	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "The Library Escapes", Style::Fullscreen);

	delete m_GameEngine;
	m_GameEngine = new GameEngine(m_Window);
}

void Engine::Run() {
	//Timing
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		const float dtAsSeconds = dt.asSeconds();

		Input();
		Update(dtAsSeconds);
		Draw();
	}
}

