#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Draw(RenderWindow& mainWindow)
{
	m_ExitButton.Draw(mainWindow);
	m_StartButton.Draw(mainWindow);
}

