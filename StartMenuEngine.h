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

	//Start menu specific Views
	sf::View m_StartMenuView;

	void UpdateMousePositions(sf::RenderWindow& mainWindow);
public:
	StartMenuEngine();

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayingState, const bool& isEscapePressed);
	void ClearEverything();
};