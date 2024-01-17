#pragma once
#include <SFML/Graphics.hpp>

//States in which the Buttons come in
enum ButtonState
{
	BTN_IDLE,
	BTN_HOVER,
	BTN_PRESSED
};

class Button
{
	//The button variables
	ButtonState m_ButtonState;
	bool b_IsEnabled = false;
	sf::RectangleShape m_Shape;
	sf::Text m_Text;
	sf::Font* m_Font;

	//Colors of the button
	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;

public:
	//Constructors
	Button() = default;
	Button(const sf::Vector2f& position, const sf::Vector2f& dimension, const std::string& fontPath, const std::string& text,
		int fontSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor);

	//Getters
	bool IsPressed();

	//Input
	void Press(const sf::Vector2f mousePosition);

	//Functions
	void Update(sf::Vector2f mousePosition, sf::RenderWindow& mainWindow);
	void Draw(sf::RenderWindow& window);
};
