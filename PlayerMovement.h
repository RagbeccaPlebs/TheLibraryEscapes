#pragma once
#include <SFML/Graphics.hpp>

class PlayerMovement
{
public:
	//A struct that holds a sheet op positions and the animation speed for that sheet
	struct SpriteSheet {
		std::vector<sf::Vector2i> spriteLocation;
		std::vector<float> animationSpeed;
	};

	//A struct that holds a single position of the animation, with the speed and index of said position
	struct SingleSprite {
		sf::Vector2i spriteLocation;
		float animationSpeed;
		int index;
	};

	//All functions to get specific sprite sheets e.g. looking one way
	PlayerMovement::SpriteSheet GetIdleSouth() const;
	PlayerMovement::SpriteSheet GetIdleNorth() const;
	PlayerMovement::SpriteSheet GetIdleEast() const;
	PlayerMovement::SpriteSheet GetIdleWest() const;
	PlayerMovement::SpriteSheet GetPushingSouth() const;
	PlayerMovement::SpriteSheet GetPushingNorth() const;
	PlayerMovement::SpriteSheet GetPushingEast() const;
	PlayerMovement::SpriteSheet GetPushingWest() const;
	PlayerMovement::SpriteSheet GetWalkSouth() const;
	PlayerMovement::SpriteSheet GetWalkNorth() const;
	PlayerMovement::SpriteSheet GetWalkEast() const;
	PlayerMovement::SpriteSheet GetWalkWest() const;
	PlayerMovement::SpriteSheet GetRunningSouth() const;
	PlayerMovement::SpriteSheet GetRunningNorth() const;
	PlayerMovement::SpriteSheet GetRunningEast() const;
	PlayerMovement::SpriteSheet GetRunningWest() const;
private:
	//All textures within a Sprite that form one generic animated look
	std::vector<sf::Vector2i> m_IdleSouth = { { sf::Vector2i(0,0) } };
	std::vector<sf::Vector2i> m_IdleNorth = { { sf::Vector2i(0,1) } };
	std::vector<sf::Vector2i> m_IdleEast = { { sf::Vector2i(0,2) } };
	std::vector<sf::Vector2i> m_IdleWest = { { sf::Vector2i(0,3) } };
	std::vector<sf::Vector2i> m_PushingSouth = { { sf::Vector2i(1,0), sf::Vector2i(2,0) } };
	std::vector<sf::Vector2i> m_PushingNorth = { { sf::Vector2i(1,1), sf::Vector2i(2,1) } };
	std::vector<sf::Vector2i> m_PushingEast = { { sf::Vector2i(1,2), sf::Vector2i(2,2) } };
	std::vector<sf::Vector2i> m_PushingWest = { { sf::Vector2i(1,3), sf::Vector2i(2,3) } };
	std::vector<sf::Vector2i> m_WalkSouth = { { sf::Vector2i(0,4), sf::Vector2i(1,4), sf::Vector2i(2,4),sf::Vector2i(3,4),sf::Vector2i(4,4),sf::Vector2i(5,4) } };
	std::vector<sf::Vector2i> m_WalkNorth = { { sf::Vector2i(0,5), sf::Vector2i(1,5), sf::Vector2i(2,5),sf::Vector2i(3,5),sf::Vector2i(4,5),sf::Vector2i(5,5) } };
	std::vector<sf::Vector2i> m_WalkEast = { { sf::Vector2i(0,6), sf::Vector2i(1,6), sf::Vector2i(2,6),sf::Vector2i(3,6),sf::Vector2i(4,6),sf::Vector2i(5,6) } };
	std::vector<sf::Vector2i> m_WalkWest = { { sf::Vector2i(0,7), sf::Vector2i(1,7), sf::Vector2i(2,7),sf::Vector2i(3,7),sf::Vector2i(4,7),sf::Vector2i(5,7) } };
	std::vector<sf::Vector2i> m_RunningSouth = { { sf::Vector2i(0,4), sf::Vector2i(1,4), sf::Vector2i(6,4),sf::Vector2i(3,4),sf::Vector2i(4,4),sf::Vector2i(7,4) } };
	std::vector<sf::Vector2i> m_RunningNorth = { { sf::Vector2i(0,5), sf::Vector2i(1,5), sf::Vector2i(6,5),sf::Vector2i(3,5),sf::Vector2i(4,5),sf::Vector2i(7,5) } };
	std::vector<sf::Vector2i> m_RunningEast = { { sf::Vector2i(0,6), sf::Vector2i(1,6), sf::Vector2i(6,6),sf::Vector2i(3,6),sf::Vector2i(4,6),sf::Vector2i(7,6) } };
	std::vector<sf::Vector2i> m_RunningWest = { { sf::Vector2i(0,7), sf::Vector2i(1,7), sf::Vector2i(6,7),sf::Vector2i(3,7),sf::Vector2i(4,7),sf::Vector2i(7,7) } };

	//Animation speed in seconds for a Sprite Sheet
	std::vector<float> m_IdleAnimationSpeed = { 0 };
	std::vector<float> m_PushAnimationSpeed = { {.3f, .3f} };
	std::vector<float> m_WalkAnimationSpeed = { {.135f, .135f, .135f, .135f, .135f, .135f} };
	std::vector<float> m_RunningAnimationSpeed = { {.08f, .055f, .125f, .08f, .055f, .125f} };
};