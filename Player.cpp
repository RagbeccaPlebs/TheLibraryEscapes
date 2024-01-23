#include "Player.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Player::Player() {
	SetInitialTextures();

	if (!m_TextureBaseLocation.empty())
	{
		m_SpriteBase = Sprite(TextureHolder::GetTexture(m_TextureBaseLocation));
	}

	if (!m_TextureLowerLayerLocation.empty())
	{
		m_SpriteLowerLayer = Sprite(TextureHolder::GetTexture(m_TextureLowerLayerLocation));
	}

	if (!m_TextureCloakLocation.empty())
	{
		m_SpriteCloak = Sprite(TextureHolder::GetTexture(m_TextureCloakLocation));
	}

	if (!m_TextureFaceItemLocation.empty())
	{
		m_SpriteFaceItem = Sprite(TextureHolder::GetTexture(m_TextureFaceItemLocation));
	}

	if (!m_TextureHairLocation.empty())
	{
		m_SpriteHair = Sprite(TextureHolder::GetTexture(m_TextureHairLocation));
	}

	if (!m_TextureHatLocation.empty())
	{
		m_SpriteHat = Sprite(TextureHolder::GetTexture(m_TextureHatLocation));
	}

	SetTextureLocation(m_PlayerMovement.GetIdleSouth().spriteLocation.at(0));

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
		m_LastButtonPressed = Side::LEFT;
		b_LeftPressed = true;
	}
	else
	{
		b_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_LastButtonPressed = Side::RIGHT;
		b_RightPressed = true;
	}
	else
	{
		b_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_LastButtonPressed = Side::UP;
		b_UpPressed = true;
	}
	else
	{
		b_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_LastButtonPressed = Side::DOWN;
		b_DownPressed = true;
	}
	else
	{
		b_DownPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		if (!b_ShiftPressed) b_ChangeRunning = true;
		b_ShiftPressed = true;
		
		m_Speed = Constant::PLAYER_RUN_SPEED;
	} else
	{
		if (b_ShiftPressed) b_ChangeRunning = true;
		b_ShiftPressed = false;
		m_Speed = Constant::PLAYER_WALK_SPEED;
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

FloatRect Player::GetInteractableBox() const
{
	return m_InteractableBox;
}

bool Player::GetDownPressed() const
{
	return b_DownPressed;
}

bool Player::GetLeftPressed() const
{
	return b_LeftPressed;
}

bool Player::GetRightPressed() const
{
	return b_RightPressed;
}

bool Player::GetUpPressed() const
{
	return b_UpPressed;
}


bool Player::IsPushing() const
{
	return b_Pushing;
}