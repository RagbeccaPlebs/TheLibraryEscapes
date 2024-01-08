#pragma once
#include <SFML/Graphics.hpp>

enum ButtonState
{
	BTN_IDLE,
	BTN_HOVER,
	BTN_PRESSED
};

class Button
{
	ButtonState m_ButtonState;

	bool b_IsEnabled = false;

	sf::RectangleShape m_Shape;
	sf::Text m_Text;

	sf::Font* m_Font;

	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;
public:
	Button() = default;
	Button(const sf::Vector2f& position, const sf::Vector2f& dimension, const std::string& fontPath, const std::string& text,
		int fontSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor);

	//Getters
	bool IsPressed();

	//Functions
	void Update(sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow& window);
};
