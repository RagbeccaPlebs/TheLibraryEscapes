#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Input(sf::RenderWindow& mainWindow, bool& isPlayingState, const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		mainWindow.close();
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

