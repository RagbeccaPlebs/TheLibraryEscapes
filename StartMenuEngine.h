#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class StartMenuEngine {

	//Mouse Position compared to the View
	sf::Vector2f m_MousePosView;

	//Input buttons
	Button m_StartButton;
	Button m_ExitButton;
	Button m_ResetGameButton;

	//Start menu specific Views
	sf::View m_StartMenuView;

	//Reset Tip
	void ShowResetTip(sf::RenderWindow& mainWindow, const sf::Font& font) const;
	bool b_ShouldShowTip = false;

	static void ResetGame(bool& resetEverything);
public:
	//Constructor
	StartMenuEngine() = default;
	explicit StartMenuEngine(const sf::Font& font);

	//The Game Runners
	void Draw(sf::RenderWindow& mainWindow, const sf::Font& font);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayingState, const bool& isEscapePressed, bool& resetEverything);
};