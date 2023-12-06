#include "Player.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Player::Player() {
	m_SpriteBase = Sprite(TextureHolder::GetTexture("assets/graphics/player/char_a_p1_0bas_humn_v00.png"));
	m_SpriteLowerLayer = Sprite(TextureHolder::GetTexture("assets/graphics/player/char_a_p1_1out_pfpn_v01.png"));
	m_SpriteCloak = Sprite(TextureHolder::GetTexture("assets/graphics/player/char_a_p1_2clo_lnpl_v07.png"));
	m_SpriteHair = Sprite(TextureHolder::GetTexture("assets/graphics/player/char_a_p1_5hat_pnty_v03.png"));

	m_currentSpriteSheet = m_PM.getIdleSouth();
}

void Player::spawn(Vector2f startPosition)
{
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	setPositionAllSprites();
}

void Player::handleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_lastButtonPressed = lastPressed::LEFT;
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_lastButtonPressed = lastPressed::RIGHT;
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_lastButtonPressed = lastPressed::UP;
		m_UpPressed = true;
	}
	else
	{
		m_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_lastButtonPressed = lastPressed::DOWN;
		m_DownPressed = true;
	}
	else
	{
		m_DownPressed = false;
	}
}

FloatRect Player::getPosition()
{
	return m_SpriteBase.getGlobalBounds();
}

FloatRect Player::getFeet()
{
	return m_Feet;
}

FloatRect Player::getHead()
{
	return m_Head;
}

FloatRect Player::getLeft()
{
	return m_Left;
}

FloatRect Player::getRight()
{
	return m_Right;
}

Vector2f Player::getCenter()
{
	return Vector2f(
		m_Position.x + m_SpriteBase.getGlobalBounds().width / 2,
		m_Position.y + m_SpriteBase.getGlobalBounds().height / 2
	);
}