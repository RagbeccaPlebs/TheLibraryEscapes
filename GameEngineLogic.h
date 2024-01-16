#pragma once
#include <SFML/Graphics.hpp>

#include "DoorInteractable.h"
#include "Player.h"
#include "Map.h"
#include "PlayerCustomization.h"
#include "SimpleBookInteractable.h"

enum LOCATION_IN_VIEW
{
	CENTER,
	BOTTOM
};

class GameEngineLogic
{
	struct GameMapObjects
	{
		std::vector<DoorInteractable*> doorInteractables;
		std::vector<PickupInventoryInteractable*> pickupInventoryInteractables;
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
	void InputInteractable(sf::RenderWindow& mainWindow);
	void DrawInteractable(sf::RenderWindow& mainWindow);
	void ClearInteractables();

	//E interaction
	bool b_BottomOverlayActive = false;
	bool b_CenterOverlayActive = false;
	std::string m_OverlayCenterText;
	const float TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS = 5.f;
	sf::Uint8 m_Opacity = 255;
	float m_SecondsSinceCenterOverlayActive = 0.f;

	void PressEToInteractCheck();
	void TextOverlay(sf::RenderWindow& mainWindow, const std::string& writtenText, const LOCATION_IN_VIEW locationInView, int fontSize, bool useOpacity);
	void UpdateCenterOverlay(float dtAsSeconds);

	void ResetCenterOverlay();

	const int MAX_RANGE_COLLISIONS_DETECTION = 5;
public:
	GameEngineLogic(const sf::RenderWindow& mainWindow);
	GameEngineLogic& operator=(const GameEngineLogic& gameEngineLogic);
	~GameEngineLogic() = default;
	GameEngineLogic(GameEngineLogic& gameEngineLogic);

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlaying, bool& isPaused, const bool& isEscapePressed);

	void UpdateMap(const std::string& mapName, sf::Vector2f spawnLocation);
	void ClearSounds() const;
};
