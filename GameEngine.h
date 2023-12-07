#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "Map.h"

class GameEngine {
private:
	//TextureHolder
	TextureHolder m_TextureHolder;

	//PlayerMovement
	PlayerMovement m_PlayerMovement;

	//Player
	Player m_Player;

	//Map
	Map m_Map;

	//Game states
	bool m_Paused;

	void loadMap();

	void detectCollisions(Player& player);

	const int MAX_RANGE_COLLISIONS_DETECTION = 5;
public:
	GameEngine();

	//To run the game, will call private functions inside here
	void draw(sf::RenderWindow& mainWindow);
	void update(float dtAsSeconds);
	void input(sf::RenderWindow& mainWindow);
	void setCenter(sf::View& mainView);
};