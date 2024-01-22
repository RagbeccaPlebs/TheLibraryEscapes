#include "PlayerMovement.h"

using namespace sf;
using namespace std;

PlayerMovement::SpriteSheet PlayerMovement::GetIdleSouth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_IdleSouth;
	spriteSheet.animationSpeed = m_IdleAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleNorth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_IdleNorth;
	spriteSheet.animationSpeed = m_IdleAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleEast() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_IdleEast;
	spriteSheet.animationSpeed = m_IdleAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleWest() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_IdleWest;
	spriteSheet.animationSpeed = m_IdleAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingSouth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_PushingSouth;
	spriteSheet.animationSpeed = m_PushAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingNorth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_PushingNorth;
	spriteSheet.animationSpeed = m_PushAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingEast() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_PushingEast;
	spriteSheet.animationSpeed = m_PushAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingWest() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_PushingWest;
	spriteSheet.animationSpeed = m_PushAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkSouth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_WalkSouth;
	spriteSheet.animationSpeed = m_WalkAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkNorth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_WalkNorth;
	spriteSheet.animationSpeed = m_WalkAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkEast() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_WalkEast;
	spriteSheet.animationSpeed = m_WalkAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkWest() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_WalkWest;
	spriteSheet.animationSpeed = m_WalkAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningSouth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_RunningSouth;
	spriteSheet.animationSpeed = m_RunningAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningNorth() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_RunningNorth;
	spriteSheet.animationSpeed = m_RunningAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningEast() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_RunningEast;
	spriteSheet.animationSpeed = m_RunningAnimationSpeed;
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningWest() const
{
	SpriteSheet spriteSheet;
	spriteSheet.spriteLocation = m_RunningWest;
	spriteSheet.animationSpeed = m_RunningAnimationSpeed;
	return spriteSheet;
}
