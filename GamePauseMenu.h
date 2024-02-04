﻿#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class GamePauseMenu
{
	//Mouse Position compared to the View
	sf::Vector2f m_MousePosView;

	//Buttons
	Button m_ContinueButton;
	Button m_BackToMenuButton;

	//Game pause specific View
	sf::View m_GamePauseView;
public:
	//Constructors, destructors and copy assignment operators
	GamePauseMenu() = default;
	GamePauseMenu(const sf::RenderWindow& mainWindow);
	GamePauseMenu& operator=(const GamePauseMenu& gamePauseMenu);
	~GamePauseMenu() = default;

	//The Game Runners
	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayingState, bool& isPausedState, bool& wasPlaying, const bool& isEscapePressed);

	//Destructor for sounds
	void ClearSounds();
};