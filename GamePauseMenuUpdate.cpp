﻿#include "GamePauseMenu.h"

using namespace sf;

void GamePauseMenu::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	UpdateMousePositions(mainWindow);
	m_ContinueButton.Update(m_MousePosView, mainWindow);
	m_BackToMenuButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_ContinueButton.Press(m_MousePosView);
		m_BackToMenuButton.Press(m_MousePosView);
	}
}

void GamePauseMenu::UpdateMousePositions(const RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}
