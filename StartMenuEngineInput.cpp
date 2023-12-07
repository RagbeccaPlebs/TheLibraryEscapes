#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::input(sf::RenderWindow& mainWindow)
{
	Event event;
	while (mainWindow.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
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
}

