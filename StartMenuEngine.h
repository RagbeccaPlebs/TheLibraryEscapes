#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class StartMenuEngine {

	// Mouse Positions
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;

	Button m_StartButton;
	Button m_ExitButton;

	void UpdateMousePositions(sf::RenderWindow& mainWindow);
public:
	StartMenuEngine();

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayingState);
};