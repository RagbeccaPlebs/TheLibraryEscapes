#include "GameEngine.h"

using namespace sf;

void GameEngine::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (b_Paused)
	{
		m_GamePausedMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else
	{
		m_GameEngineLogic.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
}

