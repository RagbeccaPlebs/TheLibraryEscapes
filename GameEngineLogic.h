#pragma once

#include "DoorInteractable.h"
#include "Player.h"
#include "Map.h"
#include "PlayerCustomization.h"
#include "PushInteractable.h"
#include "SimpleBookInteractable.h"

//Locations in which the Overlays come in
enum OverlayLocationInView
{
	CENTER,
	BOTTOM
};

class GameEngineLogic
{
	//Interactables within the map
	struct GameMapObjects
	{
		std::vector<DoorInteractable*> doorInteractables;
		std::vector<PickupInventoryInteractable*> pickupInventoryInteractables;
		std::vector<PushInteractable*> pushInteractables;
		std::vector<TiledMapLoader::MapCondition*> mapConditions;
	};

	//If interactables are loaded?
	bool b_InteractablesLoaded = false;

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

	//Detect collisions with the map
	void DetectCollisions(Player& player) const;

	//Add interactables to the correct specific vectors
	void AddInteractableToCorrectVector(const std::vector<Interactable*>& interactables);

	//The interactable vectors
	GameMapObjects m_GameMapObjects;

	//The Game Interactables Runners
	void UpdateInteractable(float dtAsSeconds);
	void InputInteractable(bool& hasWon);
	void DrawInteractable(sf::RenderWindow& mainWindow) const;
	void ClearInteractables();

	//Overlay Specific Values
	bool b_BottomOverlayActive = false;
	bool b_CenterOverlayActive = false;
	std::string m_OverlayCenterText;
	sf::Uint8 m_Opacity = 255;
	float m_SecondsSinceCenterOverlayActive = 0.f;

	//Checks for Interactables and Interaction Range
	void PressEToInteractCheck();

	//Overlay Specific Functions
	void TextOverlay(sf::RenderWindow& mainWindow, const std::string& writtenText, const OverlayLocationInView locationInView, int fontSize, bool useOpacity) const;
	void UpdateCenterOverlay(float dtAsSeconds);
	void ResetCenterOverlay();

	//The Conditions Check
	void UpdateConditions() const;
	static void HandleOperation(const TiledMapLoader::Operation& operation);
public:
	//Constructors, destructors and copy assignment operators
	explicit GameEngineLogic(const sf::RenderWindow& mainWindow);
	GameEngineLogic& operator=(const GameEngineLogic& gameEngineLogic);
	~GameEngineLogic() = default;
	GameEngineLogic(GameEngineLogic& gameEngineLogic);

	//The Game Runners
	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlaying, bool& isPaused, const bool& isEscapePressed, bool& hasWon);

	//Load the map from the mapName and the location where the player should spawn
	void LoadMap(const std::string& mapName, sf::Vector2f spawnLocation);

	//Destructor for sounds
	void ClearSounds();
	//Unloading of Game
	void UnloadAll() const;
	//Saving of Game
	void SaveAll();
	//Finish Check
	static bool CheckForFinishingCondition();
};
