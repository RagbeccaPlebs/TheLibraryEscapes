#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

class GameEngine {
private:
	//Window
	sf::RenderWindow m_Window;

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

	void draw(sf::RenderWindow& mainWindow);
	void update(float dtAsSeconds);
	void input(sf::RenderWindow& mainWindow);
	void setCenter(sf::View& mainView);
};