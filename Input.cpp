#include "Engine.h"

using namespace sf;

void Engine::input() {

	Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_Window.close();
				}
			}
		}
	}
	m_Player.handleInput();
}
