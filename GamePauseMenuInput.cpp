#include "GamePauseMenu.h"

void GamePauseMenu::Input(bool& isPlayingState, bool& isPausedState)
{
	if (m_ContinueButton.IsPressed())
	{
		isPausedState = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		isPlayingState = false;
	}
}


