#include "GameEngine.h"

using namespace sf;

void GameEngine::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	if (b_Paused)
	{
		m_GamePausedMenu.Update(dtAsSeconds, mainWindow);
	} else
	{
		m_GameEngineLogic.Update(dtAsSeconds, mainWindow);
	}
}

