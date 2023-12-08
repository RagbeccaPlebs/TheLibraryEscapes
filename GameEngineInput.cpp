#include "GameEngine.h"

using namespace sf;

void GameEngine::Input(RenderWindow& mainWindow)
{
	Event event;
	while (mainWindow.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_Paused = !m_Paused;
				}
			}
		}
	}

	if (m_Paused)
	{
		
	}
	else
	{

		m_Player.HandleInput();
	}

}

