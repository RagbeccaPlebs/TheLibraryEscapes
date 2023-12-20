#include "GameEngine.h"

using namespace sf;

void GameEngine::Draw(RenderWindow& mainWindow)
{
	m_GameEngineLogic.Draw(mainWindow);
	if (b_Paused)
	{
		m_GamePausedMenu.Draw(mainWindow);
	}
}
