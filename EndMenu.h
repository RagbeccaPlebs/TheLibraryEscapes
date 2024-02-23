#pragma once

#include "Button.h"


class EndMenu
{
	//Mouse Position compared to the View
	sf::Vector2f m_MousePosView;

	//Buttons
	Button m_BackButton;
	Button m_TextBoxButton;

	//Game pause specific View
	sf::View m_EndView;
public:
	//Constructors, destructors and copy assignment operators
	EndMenu() = default;
	explicit EndMenu(const sf::RenderWindow& mainWindow);
	EndMenu& operator=(const EndMenu& end);

	//The Game Runners
	void Draw(sf::RenderWindow& mainWindow) const;
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(bool& isPlayingState, bool& wasPlaying, const bool& isEscapePressed);

	//Destructor for sounds
	void ClearSounds();
};


