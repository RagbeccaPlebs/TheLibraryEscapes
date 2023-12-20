#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	mainWindow.setMouseCursorVisible(true);

	UpdateMousePositions(mainWindow);
	m_ContinueButton.Update(m_MousePosView);
	m_BackToMenuButton.Update(m_MousePosView);
	m_TurnRightButton.Update(m_MousePosView);
	m_TurnLeftButton.Update(m_MousePosView);
}

void PlayerCustomization::UpdateMousePositions(const RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}