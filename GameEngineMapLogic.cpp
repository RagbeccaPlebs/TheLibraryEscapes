#include "GameEngineLogic.h"

using namespace std;
using namespace sf;

void GameEngineLogic::LoadMap(const string& mapName, Vector2f spawnLocation)
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
			PickupInventoryInteractable* pickupInventoryInteractable = dynamic_cast<PickupInventoryInteractable*>(interactable);
			m_GameMapObjects.pickupInventoryInteractables.push_back(pickupInventoryInteractable);
		}
		else if (interactable->GetInteractableType() == DOOR)
		{
			DoorInteractableTemplate* doorInteractableTemplate = dynamic_cast<DoorInteractableTemplate*>(interactable);
			if (doorInteractableTemplate->GetDoorInteractableType() == SIMPLE_DOOR)
			{
				m_GameMapObjects.doorInteractables.push_back(dynamic_cast<DoorInteractable*>(doorInteractableTemplate));
			}
		}
		else if (interactable->GetInteractableType() == OBJECT)
		{
			PushInteractable* pushInteractable = dynamic_cast<PushInteractable*>(interactable);
			if (pushInteractable->GetPushType() == LOCATION_PUSH)
			{
				m_GameMapObjects.pushInteractables.push_back(dynamic_cast<LocationPushInteractable*>(pushInteractable));
			}
			else if (pushInteractable->GetPushType() == RANDOM_PUSH)
			{
				m_GameMapObjects.pushInteractables.push_back(dynamic_cast<RandomPushInteractable*>(pushInteractable));
			}
		}
		else if (interactable->GetInteractableType() == NPC)
		{

		}
	}
	b_InteractablesLoaded = true;
}
