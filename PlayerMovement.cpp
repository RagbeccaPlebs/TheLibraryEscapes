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