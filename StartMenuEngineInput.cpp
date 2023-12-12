#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Input(sf::RenderWindow& mainWindow, bool& isPlayingState)
{
	Event event;
	while (mainWindow.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					mainWindow.close();
				}
			}
		}
	}
	if (m_StartButton.IsPressed())
	{
		isPlayingState = true;
	}

	if (m_ExitButton.IsPressed())
	{
		mainWindow.close();
	}
}

