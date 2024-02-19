#include "PlayerMovement.h"

using namespace sf;
using namespace std;

PlayerMovement::SpriteSheet PlayerMovement::GetIdleSouth() const
{
	static SpriteSheet spriteSheet(m_IdleSouth, m_IdleAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleNorth() const
{
	static SpriteSheet spriteSheet(m_IdleNorth, m_IdleAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleEast() const
{
	static SpriteSheet spriteSheet(m_IdleEast, m_IdleAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetIdleWest() const
{
	static SpriteSheet spriteSheet(m_IdleWest, m_IdleAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingSouth() const
{
	static SpriteSheet spriteSheet(m_PushingSouth, m_PushAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingNorth() const
{
	static SpriteSheet spriteSheet(m_PushingNorth, m_PushAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingEast() const
{
	static SpriteSheet spriteSheet(m_PushingEast, m_PushAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetPushingWest() const
{
	static SpriteSheet spriteSheet(m_PushingWest, m_PushAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkSouth() const
{
	static SpriteSheet spriteSheet(m_WalkSouth, m_WalkAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkNorth() const
{
	static SpriteSheet spriteSheet(m_WalkNorth, m_WalkAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkEast() const
{
	static SpriteSheet spriteSheet(m_WalkEast, m_WalkAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetWalkWest() const
{
	static SpriteSheet spriteSheet(m_WalkWest, m_WalkAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningSouth() const
{
	static SpriteSheet spriteSheet(m_RunningSouth, m_RunningAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningNorth() const
{
	static SpriteSheet spriteSheet(m_RunningNorth, m_RunningAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningEast() const
{
	static SpriteSheet spriteSheet(m_RunningEast, m_RunningAnimationSpeed);
	return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::GetRunningWest() const
{
	static SpriteSheet spriteSheet(m_RunningWest, m_RunningAnimationSpeed);
	return spriteSheet;
}
