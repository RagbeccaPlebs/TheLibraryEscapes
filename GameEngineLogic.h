#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

class GameEngineLogic {
private:
	//PlayerMovement
	PlayerMovement m_PlayerMovement;

	//Player
	Player m_Player;

	//Map
	Map m_Map;

	void LoadMap(const std::string& mapName);

	void DetectCollisions(Player& player);

	const int MAX_RANGE_COLLISIONS_DETECTION = 5;
public:
	GameEngineLogic();

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::View* mainView);
	void Input(sf::RenderWindow& mainWindow);
};