#include "Button.h"

using namespace sf;
using namespace std;

Button::Button(Vector2f position, Vector2f dimension, Font* font, string text, Color idleColor, Color hoverColor, Color activeColor)
{
	m_Font = *font;
	m_ButtonState = ButtonState::BTN_IDLE;
	m_Shape.setSize(dimension);
	m_Shape.setPosition(position);
	m_Text.setFont(m_Font);
	m_Text.setString(text);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setCharacterSize(10);
	m_Text.setPosition(100.f, 100.f);

	//Colors
	m_IdleColor = idleColor;
	m_HoverColor = hoverColor;
	m_ActiveColor = activeColor;

	m_Shape.setFillColor(m_IdleColor);
}

//Getters
bool Button::isPressed()
{
	return m_ButtonState == BTN_PRESSED;
}


void Button::update(const Vector2f mousePosition)
{
	//Hover
	if (m_Shape.getGlobalBounds().contains(mousePosition))
	{
		m_ButtonState = BTN_HOVER;

		//Pressed
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			m_ButtonState = BTN_PRESSED;
		}
	}
	//Idle
	else
	{
		m_ButtonState = BTN_IDLE;
	}

	switch (m_ButtonState)
	{
	case BTN_IDLE:
		m_Shape.setFillColor(m_IdleColor);
		break;
	case BTN_HOVER:
		m_Shape.setFillColor(m_HoverColor);
		break;
	case BTN_PRESSED:
		m_Shape.setFillColor(m_ActiveColor);
		break;
	}
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_Shape);
	//window.draw(m_Text);
}
