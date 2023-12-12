#include "Player.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Player::Player() {
	SetInitialTextures();

	if (m_TextureBase.getSize().x > 0)
	{
		m_SpriteBase = Sprite(m_TextureBase);
	}

	if (m_TextureLowerLayer.getSize().x > 0)
	{
		m_SpriteLowerLayer = Sprite(m_TextureLowerLayer);
	}

	if (m_TextureCloak.getSize().x > 0)
	{
		m_SpriteCloak = Sprite(m_TextureCloak);
	}

	if (m_TextureFaceItem.getSize().x > 0)
	{
		m_SpriteFaceItem = Sprite(m_TextureFaceItem);
	}

	if (m_TextureHair.getSize().x > 0)
	{
		m_SpriteHair = Sprite(m_TextureHair);
	}

	if (m_TextureHat.getSize().x > 0)
	{
		m_SpriteHat = Sprite(m_TextureHat);
	}

	m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
}

void Player::Spawn(const Vector2f startPosition)
{
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	SetPositionAllSprites();
}

void Player::HandleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LastButtonPressed = LastPressed::LEFT;
		b_LeftPressed = true;
	}
	else
	{
		b_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_LastButtonPressed = LastPressed::RIGHT;
		b_RightPressed = true;
	}
	else
	{
		b_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_LastButtonPressed = LastPressed::UP;
		b_UpPressed = true;
	}
	else
	{
		b_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_LastButtonPressed = LastPressed::DOWN;
		b_DownPressed = true;
	}
	else
	{
		b_DownPressed = false;
	}
}

FloatRect Player::GetPosition()
{
	return m_SpriteBase.getGlobalBounds();
}

FloatRect Player::GetFeet()
{
	return m_Feet;
}

FloatRect Player::GetHead()
{
	return m_Head;
}

FloatRect Player::GetLeft()
{
	return m_Left;
}

FloatRect Player::GetRight()
{
	return m_Right;
}

Vector2f Player::GetCenter()
{
	const Vector2f centerLocation(
		m_Position.x + m_SpriteBase.getGlobalBounds().width / 2,
		m_Position.y + m_SpriteBase.getGlobalBounds().height / 2
	);
	return centerLocation;
}
