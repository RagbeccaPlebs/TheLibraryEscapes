#include "Button.h"

#include "Engine.h"

using namespace sf;
using namespace std;

Button::Button(const Vector2f& position, const Vector2f& dimension, const string& fontPath, const string& text, const int fontSize, const Color& idleColor, const Color& hoverColor, const Color& activeColor)
{
	m_ButtonState = BTN_IDLE;
	m_Shape.setSize(dimension);
	m_Shape.setPosition(position);
	m_Text.setString(text);

	m_Font = new Font();
	m_Font->loadFromFile(fontPath);

	m_Text.setFont(*m_Font);
	m_Text.setFillColor(Color::White);
	m_Text.setCharacterSize(fontSize);
	const float positionX = ((position.x + (dimension.x / 2.0f)) - (m_Text.getGlobalBounds().width / 2.0f));
	const float positionY = ((position.y + (dimension.y / 2.0f)) - (m_Text.getGlobalBounds().height));
	m_Text.setPosition(positionX, positionY);

	//Colors
	m_IdleColor = idleColor;
	m_HoverColor = hoverColor;
	m_ActiveColor = activeColor;

	m_Shape.setFillColor(m_IdleColor);
}

bool Button::IsPressed()
{
	if (m_ButtonState == BTN_PRESSED)
	{
		m_ButtonState = BTN_IDLE;
		return true;
	}
	return false;
}

void Button::Press(const Vector2f mousePosition)
{
	if (m_Shape.getGlobalBounds().contains(mousePosition))
	{
		m_ButtonState = BTN_PRESSED;
		m_Shape.setFillColor(m_ActiveColor);
	}
}


void Button::Update(const Vector2f mousePosition, RenderWindow& mainWindow) {
	//Hover
	if (m_Shape.getGlobalBounds().contains(mousePosition))
	{
		m_ButtonState = BTN_HOVER;
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

void Button::Draw(RenderWindow& window)
{
	window.draw(m_Shape);
	window.draw(m_Text);
}
