#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	UpdateMousePositions(mainWindow);
	m_ExitButton.Update(m_MousePosView);
	m_StartButton.Update(m_MousePosView);
}

void StartMenuEngine::UpdateMousePositions(RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}
