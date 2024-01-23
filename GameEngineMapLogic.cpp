#include "BookInteractable.h"
#include "GameEngineLogic.h"
#include "SimpleBookInteractable.h"

using namespace std;
using namespace sf;

void GameEngineLogic::LoadMap(const string& mapName, Vector2f spawnLocation)
{
	m_Map = new Map(mapName);

	m_PlayerSpawnLocation = spawnLocation;

	AddInteractableToCorrectVector(m_Map->GetInteractables());
}

void GameEngineLogic::ClearInteractables()
{
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		pushInteractable->Unload();
	}
	for (const DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		delete doorInteractable;
	}
	m_GameMapObjects.doorInteractables.clear();
	m_GameMapObjects.pickupInventoryInteractables.clear();
	m_GameMapObjects.pushInteractables.clear();
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
		}
		else if (interactable->GetInteractableType() == NPC)
		{

		}
	}
}
