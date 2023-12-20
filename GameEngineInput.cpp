#include "GameEngine.h"

using namespace sf;

void GameEngine::Input(RenderWindow& mainWindow, bool& isPlaying)
{
	Event event;
	while (mainWindow.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					b_Paused = !b_Paused;
				}
			}
		}
	}

	if (b_Paused)
	{
		m_GamePausedMenu.Input(isPlaying, b_Paused);
	}
	else
	{
		m_GameEngineLogic.Input(mainWindow, isPlaying);
	}

}

