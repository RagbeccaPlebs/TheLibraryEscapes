#include "GameEngine.h"

using namespace sf;

void GameEngine::Update(float dtAsSeconds, View* mainView, View* hudView, RenderWindow& mainWindow)
{
	if (b_Paused)
	{
		hudView->setCenter(mainWindow.getSize().x / 2.f, mainWindow.getSize().y / 2.f);
		m_GamePausedMenu.Update(dtAsSeconds, mainWindow);
	} else
	{
		m_GameEngineLogic.Update(dtAsSeconds, mainWindow, mainView);
	}
}

