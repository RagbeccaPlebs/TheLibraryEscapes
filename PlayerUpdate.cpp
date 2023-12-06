#include "Player.h"

using namespace sf;

void Player::update(float elapsedTime)
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
		m_lastButtonPressed = NONE;
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
	if (m_oldLastButtonPressed != m_lastButtonPressed && m_lastButtonPressed != NONE) {
		if (m_lastButtonPressed == UP) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			if (isMoving) m_currentSpriteSheet = m_PM.getWalkNorth();
			else m_currentSpriteSheet = m_PM.getIdleNorth();
		}
		else if (m_lastButtonPressed == RIGHT) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			if (isMoving) m_currentSpriteSheet = m_PM.getWalkEast();
			else m_currentSpriteSheet = m_PM.getIdleEast();
		}
		else if (m_lastButtonPressed == LEFT) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			if (isMoving) m_currentSpriteSheet = m_PM.getWalkWest();
			else m_currentSpriteSheet = m_PM.getIdleWest();
		}
		else if (m_lastButtonPressed == DOWN) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			if (isMoving) m_currentSpriteSheet = m_PM.getWalkSouth();
			else m_currentSpriteSheet = m_PM.getIdleSouth();
		}
		changedSheet = true;
	}
	else if (m_lastButtonPressed == NONE) {
		if (m_oldLastButtonPressed == UP) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			m_currentSpriteSheet = m_PM.getIdleNorth();
		}
		else if (m_oldLastButtonPressed == RIGHT) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			m_currentSpriteSheet = m_PM.getIdleEast();
		}
		else if (m_oldLastButtonPressed == LEFT) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			m_currentSpriteSheet = m_PM.getIdleWest();
		}
		else if (m_oldLastButtonPressed == DOWN) {
			m_oldLastButtonPressed = m_lastButtonPressed;
			m_currentSpriteSheet = m_PM.getIdleSouth();
		}
		changedSheet = true;
	}
	PlayerMovement::SingleSprite& currentSprite = m_currentSprite;

	if (changedSheet) {
		if (m_SecondsSinceLastAnimationUpdate >= m_currentSpriteSheet.animation_speed[0] && m_currentSpriteSheet.spriteLocation.size() > 1) {
			currentSprite.animation_speed = m_currentSpriteSheet.animation_speed[1];
			currentSprite.spriteLocation = m_currentSpriteSheet.spriteLocation[1];
			currentSprite.index = 1;
		}
		else {
			currentSprite.animation_speed = m_currentSpriteSheet.animation_speed[0];
			currentSprite.spriteLocation = m_currentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	else {
		if ((m_SecondsSinceLastAnimationUpdate >= currentSprite.animation_speed) &&
			(m_currentSpriteSheet.spriteLocation.size() > static_cast<unsigned long long>(currentSprite.index) + 1)) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animation_speed = m_currentSpriteSheet.animation_speed[currentSprite.index + 1];
			currentSprite.spriteLocation = m_currentSpriteSheet.spriteLocation[currentSprite.index + 1];
			currentSprite.index += currentSprite.index + 1;
		}
		else if (m_SecondsSinceLastAnimationUpdate >= currentSprite.animation_speed) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animation_speed = m_currentSpriteSheet.animation_speed[0];
			currentSprite.spriteLocation = m_currentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	setTextureLocation(currentSprite.spriteLocation);
}

//Stop versions
void Player::stopDown(float position)
{
	m_Position.y = position;
	setPositionAllSprites();
}

void Player::stopRight(float position)
{
	m_Position.x = position;
	setPositionAllSprites();
}

void Player::stopLeft(float position)
{
	m_Position.x = position;
	setPositionAllSprites();
}

void Player::stopUp(float position)
{
	m_Position.y = position;
	setPositionAllSprites();
}