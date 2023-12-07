#include "Engine.h"

using namespace sf;

void Engine::input() {

	if (m_Playing)
	{
		m_GameEngine.input(m_Window);
	}
	else
	{
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
	}
}
