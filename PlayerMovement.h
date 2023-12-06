#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class PlayerMovement {
public:
	struct SpriteSheet {
		std::vector<sf::Vector2i> spriteLocation;
		std::vector<float> animation_speed;
	};

	struct SingleSprite {
		sf::Vector2i spriteLocation;
		float animation_speed;
		int index;
	};

	SpriteSheet getIdleSouth();
	SpriteSheet getIdleNorth();
	SpriteSheet getIdleEast();
	SpriteSheet getIdleWest();
	SpriteSheet getWalkSouth();
	SpriteSheet getWalkNorth();
	SpriteSheet getWalkEast();
	SpriteSheet getWalkWest();
private:
	//Positions in spritemap
	std::vector<sf::Vector2i> idle_south = { { sf::Vector2i(0,0) } };
	std::vector<sf::Vector2i> idle_north = { { sf::Vector2i(0,1) } };
	std::vector<sf::Vector2i> idle_east = { { sf::Vector2i(0,2) } };
	std::vector<sf::Vector2i> idle_west = { { sf::Vector2i(0,3) } };
	std::vector<sf::Vector2i> walk_south = { { sf::Vector2i(0,4), sf::Vector2i(1,4), sf::Vector2i(2,4),sf::Vector2i(3,4),sf::Vector2i(4,4),sf::Vector2i(5,4) } };
	std::vector<sf::Vector2i> walk_north = { { sf::Vector2i(0,5), sf::Vector2i(1,5), sf::Vector2i(2,5),sf::Vector2i(3,5),sf::Vector2i(4,5),sf::Vector2i(5,5) } };
	std::vector<sf::Vector2i> walk_east = { { sf::Vector2i(0,6), sf::Vector2i(1,6), sf::Vector2i(2,6),sf::Vector2i(3,6),sf::Vector2i(4,6),sf::Vector2i(5,6) } };
	std::vector<sf::Vector2i> walk_west = { { sf::Vector2i(0,7), sf::Vector2i(1,7), sf::Vector2i(2,7),sf::Vector2i(3,7),sf::Vector2i(4,7),sf::Vector2i(5,7) } };

	//Animation speed in seconds
	std::vector<float> idle_animation_speed = { 0 };
	std::vector<float> walk_animation_speed = { {.15f, .15f, .15f, .15f, .15f, .15f} };
};