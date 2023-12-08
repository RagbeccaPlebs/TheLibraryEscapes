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

	sf::RectangleShape m_Shape;
	sf::Text m_Text;

	sf::Font* m_Font;

	sf::Color m_IdleColor;
	sf::Color m_HoverColor;
	sf::Color m_ActiveColor;
public:
	Button() = default;
	Button(sf::Vector2f position, sf::Vector2f dimension, std::string fontPath, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

	//Getters
	bool IsPressed();

	//Functions
	void Update(sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow& window);
};
