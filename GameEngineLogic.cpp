﻿#include "GameEngineLogic.h"

#include "Engine.h"

using namespace sf;
using namespace std;

GameEngineLogic::GameEngineLogic(const RenderWindow& mainWindow) : m_PlayerCustomization(PlayerCustomization(&m_Player, &m_PlayerMovement, mainWindow))
{
	//TODO SAVING GAME
	LoadMap("bridge", Vector2f(784.f, 920.f));
	m_GameView.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	m_GameView.zoom(.4f);
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
}

void GameEngineLogic::ClearSounds()
{
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		delete doorInteractable;
	}
}

void GameEngineLogic::UpdateMap(const string& mapName, const Vector2f spawnLocation)
{
	LoadMap(mapName, spawnLocation);
}




