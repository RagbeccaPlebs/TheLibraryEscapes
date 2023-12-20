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

	//Game pause specific View
	sf::View m_GamePauseView;

	void UpdateMousePositions(const sf::RenderWindow& mainWindow);
public:
	GamePauseMenu() = default;
	GamePauseMenu(const sf::RenderWindow& mainWindow);
	GamePauseMenu& operator=(const GamePauseMenu& gamePauseMenu);
	~GamePauseMenu() = default;

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(bool& isPlayingState, bool& isPausedState);
};