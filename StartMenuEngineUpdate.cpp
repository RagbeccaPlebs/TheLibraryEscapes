#include "GameEngine.h"
#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));

	m_ExitButton.Update(m_MousePosView, mainWindow);
	m_StartButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_ExitButton.Press(m_MousePosView);
		m_StartButton.Press(m_MousePosView);
	}


	m_StartMenuView.setCenter(mainWindow.getSize().x / 2.f, mainWindow.getSize().y / 2.f);
}
