#include "PlayerMovement.h"

using namespace sf;
using namespace std;

PlayerMovement::SpriteSheet PlayerMovement::getIdleSouth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_IdleSouth;
    spriteSheet.animationSpeed = m_IdleAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleNorth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_IdleNorth;
    spriteSheet.animationSpeed = m_IdleAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleEast()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_IdleEast;
    spriteSheet.animationSpeed = m_IdleAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleWest()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_IdleWest;
    spriteSheet.animationSpeed = m_IdleAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkSouth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_WalkSouth;
    spriteSheet.animationSpeed = m_WalkAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkNorth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_WalkNorth;
    spriteSheet.animationSpeed = m_WalkAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkEast()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_WalkEast;
    spriteSheet.animationSpeed = m_WalkAnimationSpeed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkWest()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = m_WalkWest;
    spriteSheet.animationSpeed = m_WalkAnimationSpeed;
    return spriteSheet;
}