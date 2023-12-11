#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class GamePauseMenu {

	// Mouse Positions
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;

	Button m_ContinueButton;
	Button m_BackToMenuButton;

	void UpdateMousePositions(const sf::RenderWindow& mainWindow);
public:
	GamePauseMenu();

	void Draw(sf::RenderWindow& mainWindow, const sf::View& hudView);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(bool& isPlayingState, bool& isPausedState);
};