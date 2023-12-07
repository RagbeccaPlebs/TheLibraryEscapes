#include "Player.h"

using namespace sf;

void Player::update(const float elapsedTime)
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

	setPositionAllSprites();

	if (m_DownPressed || m_UpPressed || m_LeftPressed || m_RightPressed) {
		m_SecondsSinceLastAnimationUpdate += elapsedTime;
		playerAnimationUpdate(true);
	}
	else {
		m_SecondsSinceLastAnimationUpdate = 0;
		m_LastButtonPressed = NONE;
		playerAnimationUpdate(false);
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();

	// Feet
	m_Feet.left = r.left + (r.width * .25);
	m_Feet.top = r.top + (r.height * .95);
	m_Feet.width = r.width - (r.width * .5);
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + (r.width * .25);
	m_Head.top = r.top + (r.height * .21);
	m_Head.width = r.width - (r.width * .5);
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + (r.width * .8);
	m_Right.top = r.top + (r.height * .235);
	m_Right.width = 1;
	m_Right.height = r.height - (r.height * .3);

	// Left
	m_Left.left = r.left + (r.width * .2);
	m_Left.top = r.top + (r.height * .25);
	m_Left.width = 1;
	m_Left.height = r.height - (r.height * 0.3);
}

//Player animation
void Player::playerAnimationUpdate(bool isMoving)
{
	bool changedSheet = false;
	if (m_OldLastButtonPressed != m_LastButtonPressed && m_LastButtonPressed != NONE) {
		if (m_LastButtonPressed == UP) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.getWalkNorth();
			else m_CurrentSpriteSheet = m_PlayerMovement.getIdleNorth();
		}
		else if (m_LastButtonPressed == RIGHT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.getWalkEast();
			else m_CurrentSpriteSheet = m_PlayerMovement.getIdleEast();
		}
		else if (m_LastButtonPressed == LEFT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.getWalkWest();
			else m_CurrentSpriteSheet = m_PlayerMovement.getIdleWest();
		}
		else if (m_LastButtonPressed == DOWN) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			if (isMoving) m_CurrentSpriteSheet = m_PlayerMovement.getWalkSouth();
			else m_CurrentSpriteSheet = m_PlayerMovement.getIdleSouth();
		}
		changedSheet = true;
	}
	else if (m_LastButtonPressed == NONE) {
		if (m_OldLastButtonPressed == UP) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.getIdleNorth();
		}
		else if (m_OldLastButtonPressed == RIGHT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.getIdleEast();
		}
		else if (m_OldLastButtonPressed == LEFT) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.getIdleWest();
		}
		else if (m_OldLastButtonPressed == DOWN) {
			m_OldLastButtonPressed = m_LastButtonPressed;
			m_CurrentSpriteSheet = m_PlayerMovement.getIdleSouth();
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
	setTextureLocation(currentSprite.spriteLocation);
}

//Stop versions
void Player::stopDown(const float position)
{
	m_Position.y = position;
	setPositionAllSprites();
}

void Player::stopRight(const float position)
{
	m_Position.x = position;
	setPositionAllSprites();
}

void Player::stopLeft(const float position)
{
	m_Position.x = position;
	setPositionAllSprites();
}

void Player::stopUp(const float position)
{
	m_Position.y = position;
	setPositionAllSprites();
}