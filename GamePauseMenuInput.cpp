#include "GamePauseMenu.h"

using namespace sf;

void GamePauseMenu::Input(RenderWindow& mainWindow, bool& isPlayingState, bool& isPausedState, const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		isPausedState = false;
	}

	if (m_ContinueButton.IsPressed())
	{
		isPausedState = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		isPlayingState = false;
	}
}

