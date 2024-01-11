#include "GameEngine.h"

using namespace sf;

void GameEngine::Input(RenderWindow& mainWindow, bool& isPlaying, const bool& isEscapePressed)
{
	if (b_Paused)
	{
		m_GamePausedMenu.Input(mainWindow, isPlaying, b_Paused, isEscapePressed);
	}
	else
	{
		m_GameEngineLogic.Input(mainWindow, isPlaying, b_Paused, isEscapePressed);
	}

}

