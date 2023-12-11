#include "Engine.h"

using namespace sf;

Engine::Engine()
{
	//Get screen resolution
	Vector2f resolution;
	resolution.x = static_cast<float>(VideoMode::getDesktopMode().width);
	resolution.y = static_cast<float>(VideoMode::getDesktopMode().height);

	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "The Library Escapes", Style::Fullscreen);

	m_GameView.setSize(resolution);

	m_GameView.zoom(0.4f);

	m_MainView.setSize(resolution);

	m_HudView.setSize(resolution);
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
