#include "GameEngineLogic.h"

#include "Engine.h"
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
using namespace sf;

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

void GameEngineLogic::UnloadAll() const
{
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		pushInteractable->Unload();
	}
}

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

void GameEngineLogic::CheckForFinishingCondition()
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
	if (foundAllBooks) b_FinishingCondition = foundAllBooks;
}