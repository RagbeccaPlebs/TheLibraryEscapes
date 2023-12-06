#include "PlayerMovement.h"

using namespace sf;
using namespace std;

PlayerMovement::SpriteSheet PlayerMovement::getIdleSouth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = idle_south;
    spriteSheet.animation_speed = idle_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleNorth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = idle_north;
    spriteSheet.animation_speed = idle_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleEast()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = idle_east;
    spriteSheet.animation_speed = idle_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getIdleWest()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = idle_west;
    spriteSheet.animation_speed = idle_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkSouth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = walk_south;
    spriteSheet.animation_speed = walk_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkNorth()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = walk_north;
    spriteSheet.animation_speed = walk_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkEast()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = walk_east;
    spriteSheet.animation_speed = walk_animation_speed;
    return spriteSheet;
}

PlayerMovement::SpriteSheet PlayerMovement::getWalkWest()
{
    SpriteSheet spriteSheet;
    spriteSheet.spriteLocation = walk_west;
    spriteSheet.animation_speed = walk_animation_speed;
    return spriteSheet;
}