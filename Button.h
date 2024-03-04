#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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
	Button(const sf::Vector2f& position, const sf::Vector2f& padding, const std::string& fontPath, const std::string& text,
		int fontSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor, bool shouldBeCentered);

	//Getters
	bool IsPressed();

	//Input
	void Press(sf::Vector2f mousePosition);

	//Functions
	void Update(sf::Vector2f mousePosition, sf::RenderWindow& mainWindow);
	void Draw(sf::RenderWindow& window) const;

	void UpdateText(const std::string& text);
};
