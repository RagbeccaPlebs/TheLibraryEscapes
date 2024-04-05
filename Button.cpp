#include "Button.h"

#include "Engine.h"

using namespace sf;
using namespace std;

Button::Button(const sf::Vector2f& position, const sf::Vector2f& padding, const sf::Font& font, const std::string& text, int fontSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor, bool shouldBeCentered)
	: Button(position, padding, font, text, fontSize, idleColor, hoverColor, activeColor, Color::White, shouldBeCentered)
{}

Button::Button(const Vector2f& position, const Vector2f& padding, const Font& font, const string& text,
	const int fontSize, const Color& idleColor, const Color& hoverColor, const Color& activeColor, const Color& fontColor, bool shouldBeCentered)
{
	m_ButtonState = BTN_IDLE;
	m_Text.setString(text);

	m_Text.setFont(font);
	m_Text.setFillColor(fontColor);
	m_Text.setCharacterSize(fontSize);
	m_Shape.setSize(Vector2f(m_Text.getGlobalBounds().getSize().x + padding.x, m_Text.getGlobalBounds().getSize().y + padding.y));
	if (shouldBeCentered)
	{
		m_Shape.setPosition(Vector2f(position.x - (m_Shape.getSize().x / 2.0f), position.y));
	}
	else
	{
		m_Shape.setPosition(Vector2f(position.x, position.y));
	}
	const float positionX = ((m_Shape.getPosition().x + (m_Shape.getSize().x / 2.0f)) - (m_Text.getGlobalBounds().width / 2.0f));
	const float positionY = ((position.y + (m_Shape.getSize().y / 2.0f)) - (m_Text.getGlobalBounds().height));
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

void Button::Draw(RenderWindow& window) const
{
	window.draw(m_Shape);
	window.draw(m_Text);
}

void Button::UpdateText(const string& text)
{
	m_Text.setString(text);
}
