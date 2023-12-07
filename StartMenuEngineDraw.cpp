#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::draw(RenderWindow& mainWindow)
{
	m_ExitButton.draw(mainWindow);
	m_StartButton.draw(mainWindow);
}

