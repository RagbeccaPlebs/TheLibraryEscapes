#include "Engine.h"

using namespace sf;

Engine::Engine()
{
	//Get screen resolution
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "The Library Escapes", Style::Fullscreen);

	//Temp fix
	m_Playing = false;
	m_Inventory = false;

	//Always get the correct map
	m_IsNewMapNeeded = true;

	m_MainView.setSize(resolution);

	m_MainView.zoom(0.4f);

	m_HudView.setViewport(FloatRect(0, 0, resolution.x, resolution.y));
}

void Engine::run() {
	//Timing
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}
