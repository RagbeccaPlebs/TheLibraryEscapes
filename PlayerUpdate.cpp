#include "Player.h"

using namespace sf;

void Player::Update(const float elapsedTime)
{
	if (b_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	if (b_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (b_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (b_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}

	SetPositionAllSprites();

	if (b_DownPressed || b_UpPressed || b_LeftPressed || b_RightPressed) {
		m_SecondsSinceLastAnimationUpdate += elapsedTime;
		PlayerAnimationUpdate(true);
	}
	else
	{
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

	//Update the Interactable Boxes
	m_InteractableBox.left = m_Left.left;
	m_InteractableBox.top = m_Head.top;
	m_InteractableBox.width = (m_Right.left - m_Left.left) + m_Right.width;
	m_InteractableBox.height = (m_Feet.top - m_Head.top) + m_Feet.height;

	m_PushInteractableBox.left = m_Left.left;
	m_PushInteractableBox.top = (r.top + (r.height / 2.f));
	m_PushInteractableBox.width = (m_Right.left - m_Left.left) + m_Right.width;
	m_PushInteractableBox.height = (r.height / 4.f);
}
//Player animation
void Player::PlayerAnimationUpdate(const bool isMoving)
{
	bool changedSheet = false;
	if ((b_StartedPushing || (b_Pushing && m_OldLastButtonPressed != m_LastButtonPressed)) && m_LastButtonPressed != NONE && m_LastButtonPressed == m_SidePushing) {
		b_Pushing = true;
		b_StartedPushing = false;
		switch (m_LastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingNorth();
			break;
		case RIGHT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingEast();
			break;
		case LEFT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingWest();
			break;
		case DOWN:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingSouth();
			break;
		}
		m_OldLastButtonPressed = m_LastButtonPressed;
		changedSheet = true;
	}
	else if (b_ChangeRunning || (m_OldLastButtonPressed != m_LastButtonPressed && m_LastButtonPressed != NONE)) {
		switch (m_LastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningNorth();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkNorth();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
			break;
		case RIGHT:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningEast();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkEast();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
			break;
		case LEFT:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningWest();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkWest();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
			break;
		case DOWN:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningSouth();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkSouth();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
			break;
		}
		if (b_ChangeRunning) b_ChangeRunning = false;
		m_OldLastButtonPressed = m_LastButtonPressed;
		changedSheet = true;
	}
	else if (m_LastButtonPressed == NONE) {
		switch (m_OldLastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
			break;
		case RIGHT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
			break;
		case LEFT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
			break;
		case DOWN:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
			break;
		}
		m_OldLastButtonPressed = m_LastButtonPressed;
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
		if (m_SecondsSinceLastAnimationUpdate >= currentSprite.animationSpeed &&
			m_CurrentSpriteSheet.spriteLocation.size() > static_cast<unsigned long long>(currentSprite.index) + 1) {
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

void Player::SetPushing(const Side& side)
{
	b_StartedPushing = true;
	m_SidePushing = side;
}

void Player::StopPushing()
{
	b_Pushing = false;
}
