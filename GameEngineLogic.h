﻿#pragma once
#include <SFML/Graphics.hpp>

#include "DoorInteractable.h"
#include "Player.h"
#include "Map.h"
#include "PlayerCustomization.h"
#include "SimpleBookInteractable.h"

class GameEngineLogic
{
	struct GameMapObjects
	{
		std::vector<SimpleBookInteractable*> simpleBookInteractables;
		std::vector<DoorInteractable*> doorInteractables;
	};
	//PlayerMovement
	PlayerMovement m_PlayerMovement;

	//Player
	Player m_Player;

	//Player Customization Engine
	PlayerCustomization m_PlayerCustomization;

	//Map & Values
	Map* m_Map;
	sf::Vector2f m_PlayerSpawnLocation;

	//Game play specific View
	sf::View m_GameView;
	sf::View m_OverlayView;
	float m_Zoom;

	//Game state
	bool b_PlayerCustomizationSelectorEnabled = true;

	void LoadMap(const std::string& mapName, sf::Vector2f spawnLocation);

	void DetectCollisions(Player& player);

	//Interactable
	void AddInteractableToCorrectVector(const std::vector<Interactable*>& interactables);

	GameMapObjects m_GameMapObjects;

	void UpdateInteractable(float dtAsSeconds);
	void InputInteractable();
	void DrawInteractable(sf::RenderWindow& mainWindow);
	void ClearInteractables();

	//E interaction
	bool b_EOverlayActive = false;
	void PressEToInteractCheck();
	void PressEToInteractOverlay(sf::RenderWindow& mainWindow);

	const int MAX_RANGE_COLLISIONS_DETECTION = 5;
public:
	GameEngineLogic(const sf::RenderWindow& mainWindow);
	GameEngineLogic& operator=(const GameEngineLogic& gameEngineLogic);
	~GameEngineLogic() = default;
	GameEngineLogic(GameEngineLogic& gameEngineLogic);

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWind, bool& isPlaying);

	void UpdateMap(const std::string& mapName, sf::Vector2f spawnLocation);
	void ClearSounds();
};
