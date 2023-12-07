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

	sf::Font m_Font;

	void updateMousePositions(sf::RenderWindow& mainWindow);
public:
	StartMenuEngine();

	void draw(sf::RenderWindow& mainWindow);
	void update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void input(sf::RenderWindow& mainWindow);
};