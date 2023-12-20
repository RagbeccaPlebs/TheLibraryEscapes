﻿#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "PlayerCustomization.h"

class GameEngineLogic {
private:
	//PlayerMovement
	PlayerMovement m_PlayerMovement;

	//Player
	Player m_Player;

	//Player Customization Engine
	PlayerCustomization m_PlayerCustomization;

	//Map & Values
	Map m_Map;
	sf::Vector2f m_PlayerSpawnLocation;

	//Game play specific View
	sf::View m_GameView;

	//Game state
	bool b_PlayerCustomizationSelectorEnabled = true;

	void LoadMap(const std::string& mapName);

	void DetectCollisions(Player& player);

	const int MAX_RANGE_COLLISIONS_DETECTION = 5;
public:
	GameEngineLogic(const sf::RenderWindow& mainWindow);
	GameEngineLogic& operator=(const GameEngineLogic& gameEngineLogic);
	~GameEngineLogic() = default;
	GameEngineLogic(GameEngineLogic& gameEngineLogic);

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWind, bool& isPlaying);
};
