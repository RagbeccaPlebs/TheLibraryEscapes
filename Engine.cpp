#include "Engine.h"

using namespace sf;

Engine::Engine()
{
	//Get screen resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "The Library Escapes", Style::Fullscreen);

	m_GameView.setSize(resolution);

	m_GameView.zoom(0.4f);

	m_MainView.setSize(resolution);

	m_HudView.setViewport(FloatRect(0, 0, resolution.x, resolution.y));
}

void Engine::run() {
	//Timing
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		const float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
