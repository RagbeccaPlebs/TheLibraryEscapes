#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Draw(RenderWindow& mainWindow)
{
	mainWindow.setView(m_StartMenuView);
	m_ExitButton.Draw(mainWindow);
	m_StartButton.Draw(mainWindow);
	m_ResetGameButton.Draw(mainWindow);
}

