#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class PlayerMovement {
public:
	struct SpriteSheet {
		std::vector<sf::Vector2i> spriteLocation;
		std::vector<float> animationSpeed;
	};

	struct SingleSprite {
		sf::Vector2i spriteLocation;
		float animationSpeed;
		int index;
	};

	SpriteSheet GetIdleSouth();
	SpriteSheet GetIdleNorth();
	SpriteSheet GetIdleEast();
	SpriteSheet GetIdleWest();
	SpriteSheet GetWalkSouth();
	SpriteSheet GetWalkNorth();
	SpriteSheet GetWalkEast();
	SpriteSheet GetWalkWest();
private:
	//Positions in sprite-map
	std::vector<sf::Vector2i> m_IdleSouth = { { sf::Vector2i(0,0) } };
	std::vector<sf::Vector2i> m_IdleNorth = { { sf::Vector2i(0,1) } };
	std::vector<sf::Vector2i> m_IdleEast = { { sf::Vector2i(0,2) } };
	std::vector<sf::Vector2i> m_IdleWest = { { sf::Vector2i(0,3) } };
	std::vector<sf::Vector2i> m_WalkSouth = { { sf::Vector2i(0,4), sf::Vector2i(1,4), sf::Vector2i(2,4),sf::Vector2i(3,4),sf::Vector2i(4,4),sf::Vector2i(5,4) } };
	std::vector<sf::Vector2i> m_WalkNorth = { { sf::Vector2i(0,5), sf::Vector2i(1,5), sf::Vector2i(2,5),sf::Vector2i(3,5),sf::Vector2i(4,5),sf::Vector2i(5,5) } };
	std::vector<sf::Vector2i> m_WalkEast = { { sf::Vector2i(0,6), sf::Vector2i(1,6), sf::Vector2i(2,6),sf::Vector2i(3,6),sf::Vector2i(4,6),sf::Vector2i(5,6) } };
	std::vector<sf::Vector2i> m_WalkWest = { { sf::Vector2i(0,7), sf::Vector2i(1,7), sf::Vector2i(2,7),sf::Vector2i(3,7),sf::Vector2i(4,7),sf::Vector2i(5,7) } };

	//Animation speed in seconds
	std::vector<float> m_IdleAnimationSpeed = { 0 };
	std::vector<float> m_WalkAnimationSpeed = { {.15f, .15f, .15f, .15f, .15f, .15f} };
};