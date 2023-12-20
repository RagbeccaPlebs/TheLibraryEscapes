#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	mainWindow.setMouseCursorVisible(true);

	UpdateMousePositions(mainWindow);
	m_ExitButton.Update(m_MousePosView);
	m_StartButton.Update(m_MousePosView);

	m_StartMenuView.setCenter(mainWindow.getSize().x / 2.f, mainWindow.getSize().y / 2.f);
}

void StartMenuEngine::UpdateMousePositions(RenderWindow& mainWindow)
{
	m_MousePosScreen = Mouse::getPosition();
	m_MousePosWindow = Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));
}
