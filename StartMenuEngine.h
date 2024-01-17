#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class StartMenuEngine {

	//Mouse Position compared to the View
	sf::Vector2f m_MousePosView;

	//Input buttons
	Button m_StartButton;
	Button m_ExitButton;

	//Start menu specific Views
	sf::View m_StartMenuView;
public:
	//Constructor
	StartMenuEngine();

	//The Game Runners
	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayingState, const bool& isEscapePressed);
};