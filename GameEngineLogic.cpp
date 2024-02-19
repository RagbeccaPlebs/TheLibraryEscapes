﻿#include "GameEngineLogic.h"

#include "Engine.h"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
using namespace sf;

//CONSTRUCTORS
GameEngineLogic::GameEngineLogic(const RenderWindow& mainWindow) : m_PlayerCustomization(PlayerCustomization(m_Player, m_PlayerMovement, mainWindow))
{
	b_InteractablesLoaded = false;
	ifstream oldFile(Files::GAME_DATA_FILE);
	nlohmann::json data = json::parse(oldFile);
	oldFile.close();
	if (data.contains(Keywords::PLAYER_LOCATION_KEYWORD))
	{
		json nestedData = data.at(Keywords::PLAYER_LOCATION_KEYWORD);
		LoadMap(nestedData.at(Keywords::MAP_KEYWORD), Vector2f(nestedData.at(Keywords::MAP_X_KEYWORD), nestedData.at(Keywords::MAP_Y_KEYWORD)));
	}
	else
	{
		LoadMap("bridge", Vector2f(784.f, 920.f));
	}
	m_GameView.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	m_OverlayView.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	if (data.contains(Keywords::SETTINGS_KEYWORD))
	{
		m_Zoom = data.at(Keywords::SETTINGS_KEYWORD).at(Keywords::ZOOM_KEYWORD);
	}
	else
	{
		m_Zoom = 0.4f;
	}
	m_GameView.zoom(m_Zoom);
}

GameEngineLogic& GameEngineLogic::operator=(const GameEngineLogic& gameEngineLogic)
{
	if (this == &gameEngineLogic)
	{
		return *this;
	}
	this->m_Player = gameEngineLogic.m_Player;
	this->m_GameView = gameEngineLogic.m_GameView;
	this->m_Map = gameEngineLogic.m_Map;
	this->m_PlayerCustomization = gameEngineLogic.m_PlayerCustomization;
	return *this;
}

GameEngineLogic::GameEngineLogic(GameEngineLogic& gameEngineLogic) : m_PlayerCustomization(gameEngineLogic.m_PlayerCustomization)
{
	m_Player = gameEngineLogic.m_Player;
	m_Map = gameEngineLogic.m_Map;
	m_GameView = gameEngineLogic.m_GameView;
	m_PlayerMovement = gameEngineLogic.m_PlayerMovement;
	m_PlayerCustomization = gameEngineLogic.m_PlayerCustomization;
	m_PlayerSpawnLocation = gameEngineLogic.m_PlayerSpawnLocation;
	m_Zoom = gameEngineLogic.m_Zoom;
}

//DESTRUCTORS
void GameEngineLogic::UnloadAll() const
{
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		pushInteractable->Unload();
	}
}

void GameEngineLogic::ClearSounds()
{
	for (const DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		delete doorInteractable;
	}
	for (const PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		delete pushInteractable;
	}

	// If incorrectly deleted, delete again
	m_GameMapObjects.doorInteractables.clear();
	m_GameMapObjects.pushInteractables.clear();
}

//SAVING
void GameEngineLogic::SaveAll()
{
	if (!b_InteractablesLoaded || b_PlayerCustomizationSelectorEnabled)
	{
		return;
	}
	UnloadAll();

	//Save location to file
	ifstream oldFile(Files::GAME_DATA_FILE);
	json data = json::parse(oldFile);
	oldFile.close();
	json playerLocationValues;

	data[Keywords::PLAYER_LOCATION_KEYWORD][Keywords::MAP_KEYWORD] = m_Map->GetMapName();
	data[Keywords::PLAYER_LOCATION_KEYWORD][Keywords::MAP_X_KEYWORD] = m_Player.GetPosition().left;
	data[Keywords::PLAYER_LOCATION_KEYWORD][Keywords::MAP_Y_KEYWORD] = m_Player.GetPosition().top;

	std::ofstream newFile(Files::GAME_DATA_FILE);
	newFile << data;
	newFile.flush();
}

//CONDITION CHECKING
bool GameEngineLogic::CheckForFinishingCondition()
{
	ifstream booksFile(Files::BOOKS_DATA_FILE);
	json booksTotal = json::parse(booksFile);
	booksFile.close();
	ifstream gameDataFile(Files::GAME_DATA_FILE);
	json booksFound = json::parse(gameDataFile);
	gameDataFile.close();

	vector<int> idsOfFoundBooks;

	for (const json& foundBooks : booksFound.at(Keywords::BOOK_KEYWORD))
	{
		idsOfFoundBooks.push_back(foundBooks.at(Keywords::ID_KEYWORD));
	}

	bool foundAllBooks = true;
	for (const json& books : booksTotal.at(Keywords::BOOK_KEYWORD))
	{
		if (std::find(idsOfFoundBooks.begin(), idsOfFoundBooks.end(), books.at(Keywords::ID_KEYWORD)) == idsOfFoundBooks.end())
		{
			foundAllBooks = false;
		}
	}
	return foundAllBooks;
}

//DRAW
void GameEngineLogic::Draw(RenderWindow& mainWindow)
{

	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Draw(mainWindow);
		return;
	}

	mainWindow.setView(m_GameView);

	const int amountOfMapLayers = static_cast<int>(m_Map->GetMapLayers().size());
	for (int i = 0; i < amountOfMapLayers; i++)
	{
		for (TiledMapLoader::MapLayer& mapLayer : m_Map->GetMapLayers())
		{
			if (mapLayer.id == i + 1 && mapLayer.name != Constant::MAP_COLLISION_LEVEL_NAME)
			{
				mainWindow.draw(mapLayer.rVa, &m_Map->GetTextureTiles());
			}
		}
	}

	DrawInteractable(mainWindow);

	for (const Sprite* sprite : m_Player.GetSprites())
	{
		if (sprite->getTexture() != nullptr) {
			mainWindow.draw(*sprite);
		}
	}

	mainWindow.setView(m_OverlayView);
	if (b_BottomOverlayActive)
	{
		TextOverlay(mainWindow, Message::PRESS_E_TO_INTERACT_MESSAGE, BOTTOM, 40, false);
	}
	if (b_CenterOverlayActive)
	{
		TextOverlay(mainWindow, m_OverlayCenterText, CENTER, 60, true);
	}
}

void GameEngineLogic::DrawInteractable(RenderWindow& mainWindow) const
{
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		doorInteractable->Draw(mainWindow);
	}
	for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
	{
		if (pickupInventoryInteractable->GetActive())
		{
			pickupInventoryInteractable->Draw(mainWindow);
		}
	}
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		pushInteractable->Draw(mainWindow);
	}
}

void GameEngineLogic::TextOverlay(RenderWindow& mainWindow, const string& writtenText, const OverlayLocationInView locationInView, int fontSize, bool useOpacity) const
{
	RectangleShape shape;
	Text text;
	text.setString(writtenText);

	Font font;
	font.loadFromFile(Files::FONT_FILE);

	text.setFont(font);

	if (useOpacity)
	{
		const Color whiteColor(255, 255, 255, m_Opacity);
		const Color darkerColor(0, 0, 0, (m_Opacity / 2));
		text.setFillColor(whiteColor);
		shape.setFillColor(darkerColor);
	}
	else
	{
		const Color darkerColor(0, 0, 0, 127);
		text.setFillColor(Color::White);
		shape.setFillColor(darkerColor);
	}

	text.setCharacterSize(fontSize);

	Vector2f dimension;
	Vector2f position;

	switch (locationInView)
	{
	case CENTER:
		dimension = { text.getGlobalBounds().width * 1.25f, text.getGlobalBounds().height * 1.5f };
		position = { mainWindow.getView().getCenter().x - (dimension.x / 2.f), mainWindow.getView().getCenter().y - (dimension.y / 2.f) };
		break;
	case BOTTOM:
		dimension = { text.getGlobalBounds().width * 1.25f, text.getGlobalBounds().height * 1.5f };
		position = { mainWindow.getView().getCenter().x - (dimension.x / 2.f), mainWindow.getView().getCenter().y + (mainWindow.getView().getSize().y / 4.f) };
		break;
	}

	shape.setSize(dimension);
	shape.setPosition(position);
	const float positionX = ((position.x + (dimension.x / 2.0f)) - (text.getGlobalBounds().width / 2.0f));
	const float positionY = ((position.y + (dimension.y / 2.0f)) - (text.getGlobalBounds().height));
	text.setPosition(positionX, positionY);

	mainWindow.draw(shape);
	mainWindow.draw(text);
}

//INPUT
void GameEngineLogic::Input(RenderWindow& mainWindow, bool& isPlaying, bool& isPaused, const bool& isEscapePressed, bool& hasWon)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Input(mainWindow, b_PlayerCustomizationSelectorEnabled, isPlaying, m_PlayerSpawnLocation, isEscapePressed);
		return;
	}
	if (isEscapePressed)
	{
		isPaused = !isPaused;
	}

	m_Player.HandleInput();
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		if (pushInteractable->CanInteract(m_Player))
		{
			pair<string, Vector2f> pushInteractableReturn = pushInteractable->Interact();
			if (pushInteractableReturn.first == Message::CORRECT_LOCATION_MESSAGE)
			{
				if (pushInteractable->GetPushSoundStatus() == SoundSource::Playing) pushInteractable->StopPushSound();
				m_OverlayCenterText = pushInteractable->Message();
				b_CenterOverlayActive = true;
				pushInteractable->PlayAlternativeSound();
			}
			else if (pushInteractableReturn.first == Keywords::PUSHABLE_OBJECT_KEYWORD)
			{
				pushInteractable->PlayPushSound();
			}
		}
		else
		{
			if (pushInteractable->GetPushSoundStatus() == SoundSource::Playing) pushInteractable->StopPushSound();
		}
	}
	InputInteractable(hasWon);
}


void GameEngineLogic::InputInteractable(bool& hasWon)
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
		{
			if (doorInteractable->CanInteract(m_Player))
			{
				if (doorInteractable->GetOpen())
				{
					pair<string, Vector2f> mapValue = doorInteractable->Interact();
					ClearInteractables();
					LoadMap(mapValue.first, mapValue.second);
					m_Player.Spawn(m_PlayerSpawnLocation);
				}
				else
				{
					if (!doorInteractable->TryUnlocking())
					{
						ResetCenterOverlay();
						m_OverlayCenterText = doorInteractable->Message();
						b_CenterOverlayActive = true;
						doorInteractable->PlaySound();
					}
				}

			}
		}
		for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
		{
			if (pickupInventoryInteractable->CanInteract(m_Player))
			{
				pickupInventoryInteractable->Interact();
				ResetCenterOverlay();
				m_OverlayCenterText = pickupInventoryInteractable->Message();
				b_CenterOverlayActive = true;
				if (pickupInventoryInteractable->GetPickupType() == BOOK)
				{
					hasWon = CheckForFinishingCondition();
				}
			}
		}
	}
}

//UPDATE
void GameEngineLogic::Update(const float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Update(dtAsSeconds, mainWindow, isLeftClicked);
		return;
	}
	mainWindow.setMouseCursorVisible(false);

	m_Player.Update(dtAsSeconds);

	//Detect collisions
	DetectCollisions(m_Player);

	m_GameView.setCenter(m_Player.GetCenter());

	UpdateInteractable(dtAsSeconds);

	PressEToInteractCheck();

	if (b_CenterOverlayActive)
	{
		UpdateCenterOverlay(dtAsSeconds);
	}

	UpdateConditions();
}

void GameEngineLogic::UpdateInteractable(const float dtAsSeconds)
{
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		doorInteractable->Update(dtAsSeconds, m_Player);
	}
	for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
	{
		pickupInventoryInteractable->Update(dtAsSeconds, m_Player);
	}
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		pushInteractable->Update(dtAsSeconds, m_Player);
	}
}

void GameEngineLogic::PressEToInteractCheck()
{
	bool isOverlayApplicable = false;
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		if (doorInteractable->CanInteract(m_Player))
		{
			isOverlayApplicable = true;
		}
	}
	for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
	{
		if (pickupInventoryInteractable->CanInteract(m_Player))
		{
			isOverlayApplicable = true;
		}
	}

	b_BottomOverlayActive = isOverlayApplicable;
}

void GameEngineLogic::UpdateCenterOverlay(const float dtAsSeconds)
{
	m_SecondsSinceCenterOverlayActive += dtAsSeconds;
	m_Opacity = static_cast<Uint8>(255 - (255 * (m_SecondsSinceCenterOverlayActive / Constant::TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS)));
	m_Opacity = max(m_Opacity, static_cast<Uint8>(0));
	if (m_SecondsSinceCenterOverlayActive > Constant::TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS)
	{
		ResetCenterOverlay();
	}
	else
	{
		b_CenterOverlayActive = true;
	}
}

void GameEngineLogic::ResetCenterOverlay()
{
	b_CenterOverlayActive = false;
	m_SecondsSinceCenterOverlayActive = 0;
	m_OverlayCenterText = Constant::EMPTY_STRING;
	m_Opacity = 255;
}

void GameEngineLogic::UpdateConditions() const
{
	for (TiledMapLoader::MapCondition* mapCondition : m_GameMapObjects.mapConditions)
	{
		if (mapCondition->activated)
		{
			continue;
		}
		bool allConditionsMet = true;
		for (const Interactable* conditionInteractable : mapCondition->conditions)
		{
			if (!conditionInteractable->GetConditionMet())
			{
				allConditionsMet = false;
			}
		}

		if (!allConditionsMet)
		{
			continue;
		}
		for (const TiledMapLoader::Operation& operation : mapCondition->operations)
		{
			HandleOperation(operation);
		}
		mapCondition->activated = true;
	}
}

void GameEngineLogic::HandleOperation(const TiledMapLoader::Operation& operation)
{
	switch (operation.action)
	{
	case TiledMapLoader::SHOW:
	{
		operation.interactable->Activate();
		break;
	}
	}
}

//COLLISION DETECTION
void GameEngineLogic::DetectCollisions(Player& player) const
{
	const FloatRect detectionZone = player.GetPosition();

	constexpr int TILE_SIZE = Constant::STANDARD_TILE_SIZE;

	// Make a FloatRect to test each block
	FloatRect block(0, 0, TILE_SIZE, TILE_SIZE);

	// Build a zone around the player to detect collisions
	int startX = static_cast<int>(detectionZone.left / TILE_SIZE);
	int startY = static_cast<int>(detectionZone.top / TILE_SIZE);
	int endX = static_cast<int>(detectionZone.left / TILE_SIZE) + Constant::MAX_RANGE_COLLISIONS_DETECTION;
	int endY = static_cast<int>(detectionZone.top / TILE_SIZE) + Constant::MAX_RANGE_COLLISIONS_DETECTION;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0) {
		startX = 0;
	}
	if (startY < 0) {
		startY = 0;
	}
	if (endX >= m_Map->GetMapSize().x) {
		endX = m_Map->GetMapSize().x;
	}
	if (endY >= m_Map->GetMapSize().y) {
		endY = m_Map->GetMapSize().y;
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{

			// Is character colliding with a regular block
			if (m_Map->GetArrayCollisionLevel()[y][x] >= 1)
			{
				// Initialize the starting position of the current block
				block.left = static_cast<float>(x * TILE_SIZE);
				block.top = static_cast<float>(y * TILE_SIZE);

				if (player.GetRight().intersects(block))
				{
					player.StopRight(block.left - (player.GetRight().left - player.GetPosition().left + player.GetRight().width));
				}
				else if (player.GetLeft().intersects(block))
				{
					player.StopLeft(block.left + (player.GetCenter().x - player.GetLeft().left));
				}

				if (player.GetFeet().intersects(block))
				{
					player.StopDown(block.top - player.GetFeet().top + player.GetPosition().top - 1);
				}
				else if (player.GetHead().intersects(block))
				{
					player.StopUp(block.top + block.height - (player.GetHead().top - player.GetPosition().top));
				}
			}

		}

	}

	//Push interactables check
	for (const PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		if (player.GetRight().intersects(pushInteractable->GetCollisionBox()))
		{
			player.StopRight(pushInteractable->GetCollisionBox().left - (player.GetRight().left - player.GetPosition().left + player.GetRight().width));
		}
		else if (player.GetLeft().intersects(pushInteractable->GetCollisionBox()))
		{
			player.StopLeft(pushInteractable->GetCollisionBox().left + (player.GetCenter().x - player.GetLeft().left));
		}

		if (player.GetFeet().intersects(pushInteractable->GetCollisionBox()))
		{
			player.StopDown(pushInteractable->GetCollisionBox().top - player.GetFeet().top + player.GetPosition().top - 1);
		}
		else if (player.GetHead().intersects(pushInteractable->GetCollisionBox()))
		{
			player.StopUp(pushInteractable->GetCollisionBox().top + pushInteractable->GetCollisionBox().height - (player.GetHead().top - player.GetPosition().top));
		}
	}
}

//MAP LOGIC
void GameEngineLogic::LoadMap(const string& mapName, const Vector2f spawnLocation)
{
	m_Map = new Map(mapName);

	m_PlayerSpawnLocation = spawnLocation;

	AddInteractableToCorrectVector(m_Map->GetInteractables());
	m_GameMapObjects.mapConditions = m_Map->GetMapConditions();
}

void GameEngineLogic::ClearInteractables()
{
	UnloadAll();

	for (const DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		delete doorInteractable;
	}
	for (const PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		delete pushInteractable;
	}
	m_GameMapObjects.doorInteractables.clear();
	m_GameMapObjects.pickupInventoryInteractables.clear();
	m_GameMapObjects.pushInteractables.clear();
	m_GameMapObjects.mapConditions.clear();
	b_InteractablesLoaded = false;
}

void GameEngineLogic::AddInteractableToCorrectVector(const vector<Interactable*>& interactables)
{
	for (Interactable* interactable : interactables)
	{
		if (interactable->GetInteractableType() == PICKUP)
		{
			auto* pickupInventoryInteractable = dynamic_cast<PickupInventoryInteractable*>(interactable);
			m_GameMapObjects.pickupInventoryInteractables.push_back(pickupInventoryInteractable);
		}
		else if (interactable->GetInteractableType() == DOOR)
		{
			auto* doorInteractableTemplate = dynamic_cast<DoorInteractableTemplate*>(interactable);
			if (doorInteractableTemplate->GetDoorInteractableType() == SIMPLE_DOOR)
			{
				m_GameMapObjects.doorInteractables.push_back(dynamic_cast<DoorInteractable*>(doorInteractableTemplate));
			}
		}
		else if (interactable->GetInteractableType() == PUSH_OBJECT)
		{
			auto* pushInteractable = dynamic_cast<PushInteractable*>(interactable);
			if (pushInteractable->GetPushType() == LOCATION_PUSH)
			{
				m_GameMapObjects.pushInteractables.push_back(dynamic_cast<LocationPushInteractable*>(pushInteractable));
			}
			else if (pushInteractable->GetPushType() == RANDOM_PUSH)
			{
				m_GameMapObjects.pushInteractables.push_back(dynamic_cast<RandomPushInteractable*>(pushInteractable));
			}
		}
	}
	b_InteractablesLoaded = true;
}