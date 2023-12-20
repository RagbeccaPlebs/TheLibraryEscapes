#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Input(RenderWindow& mainWindow, bool& isPlayerCustomizationSelectorEnabled, bool& isPlaying, const Vector2f& playerSpawnLocation)
{
	Event event;
	while (mainWindow.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					isPlaying = false;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					TurnCharacterLeft();
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					TurnCharacterRight();
				}
				if(Keyboard::isKeyPressed(Keyboard::Enter))
				{
					isPlayerCustomizationSelectorEnabled = false;
				}
			}
		}
	}

	if (m_ContinueButton.IsPressed())
	{
		m_Player->Spawn(playerSpawnLocation);
		isPlayerCustomizationSelectorEnabled = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		isPlaying = false;
	}

	if (m_TurnLeftButton.IsPressed())
	{
		TurnCharacterLeft();
	}

	if (m_TurnRightButton.IsPressed())
	{
		TurnCharacterRight();
	}
}