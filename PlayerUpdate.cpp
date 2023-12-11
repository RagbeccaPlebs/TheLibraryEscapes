#include "Player.h"

using namespace sf;

void Player::Update(const float elapsedTime)
{
	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}

	SetPositionAllSprites();

	if (m_DownPressed || m_UpPressed || m_LeftPressed || m_RightPressed) {
		m_SecondsSinceLastAnimationUpdate += elapsedTime;
		PlayerAnimationUpdate(true);
	}
	else {
		m_SecondsSinceLastAnimationUpdate = 0;
		m_LastButtonPressed = NONE;
		PlayerAnimationUpdate(false);
	}

	// Update the rect for all body parts
	const FloatRect r = GetPosition();

	// Feet
	m_Feet.left = static_cast<float>(r.left + (r.width * .25));
	m_Feet.top = static_cast<float>(r.top + (r.height * .95));
	m_Feet.width = static_cast<float>(r.width - (r.width * .5));
	m_Feet.height = 1;

	// Head
	m_Head.left = static_cast<float>(r.left + (r.width * .25));
	m_Head.top = static_cast<float>(r.top + (r.height * .21));
	m_Head.width = static_cast<float>(r.width - (r.width * .5));
	m_Head.height = 1;

	// Right
	m_Right.left = static_cast<float>(r.left + (r.width * .8));
	m_Right.top = static_cast<float>(r.top + (r.height * .235));
	m_Right.width = 1;
	m_Right.height = static_cast<float>(r.height - (r.height * .3));

	// Left
	m_Left.left = static_cast<float>(r.left + (r.width * .2));
	m_Left.top = static_cast<float>(r.top + (r.height * .25));
	m_Left.width = 1;
	m_Left.height = static_cast<float>(r.height - (r.height * 0.3));
}

//Player animation
void Player::PlayerAnimationUpdate(const bool isMoving)
{
	bool changedSheet = false;
	if (m_OldLastButtonPressed != m_LastButtonPressed && m_LastButtonPressed != NONE) {
		if (m_LastButtonPressed == UP) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.GetWalkNorth();
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
		}
		else if (m_LastButtonPressed == RIGHT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.GetWalkEast();
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
		}
		else if (m_LastButtonPressed == LEFT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.GetWalkWest();
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
		}
		else if (m_LastButtonPressed == DOWN) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.GetWalkSouth();
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
		}
		changedSheet = true;
	}
	else if (m_LastButtonPressed == NONE) {
		if (m_OldLastButtonPressed == UP) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
		}
		else if (m_OldLastButtonPressed == RIGHT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
		}
		else if (m_OldLastButtonPressed == LEFT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
		}
		else if (m_OldLastButtonPressed == DOWN) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
		}
		changedSheet = true;
	}
	PlayerMovement::SingleSprite& currentSprite = m_CurrentSprite;

	if (changedSheet) {
		if (m_SecondsSinceLastAnimationUpdate >= m_CurrentSpriteSheet.animationSpeed[0] && m_CurrentSpriteSheet.spriteLocation.size() > 1) {
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[1];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[1];
			currentSprite.index = 1;
		}
		else {
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[0];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	else {
		if ((m_SecondsSinceLastAnimationUpdate >= currentSprite.animationSpeed) &&
			(m_CurrentSpriteSheet.spriteLocation.size() > static_cast<unsigned long long>(currentSprite.index) + 1)) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[currentSprite.index + 1];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[currentSprite.index + 1];
			currentSprite.index += currentSprite.index + 1;
		}
		else if (m_SecondsSinceLastAnimationUpdate >= currentSprite.animationSpeed) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[0];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	SetTextureLocation(currentSprite.spriteLocation);
}

//Stop versions
void Player::StopDown(const float position)
{
	m_Position.y = position;
	SetPositionAllSprites();
}

void Player::StopRight(const float position)
{
	m_Position.x = position;
	SetPositionAllSprites();
}

void Player::StopLeft(const float position)
{
	m_Position.x = position;
	SetPositionAllSprites();
}

void Player::StopUp(const float position)
{
	m_Position.y = position;
	SetPositionAllSprites();
}