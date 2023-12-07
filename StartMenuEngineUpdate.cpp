#include "StartMenuEngine.h"

using namespace sf;

void StartMenuEngine::update(float dtAsSeconds, RenderWindow& mainWindow)
{
	updateMousePositions(mainWindow);
	m_ExitButton.update(m_MousePosView);
	m_StartButton.update(m_MousePosView);
}

void StartMenuEngine::updateMousePositions(RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}
