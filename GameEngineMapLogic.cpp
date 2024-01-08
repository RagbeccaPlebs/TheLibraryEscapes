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
	for (const DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		delete doorInteractable;
	}
	m_GameMapObjects.doorInteractables.clear();
	m_GameMapObjects.simpleBookInteractables.clear();
}

void GameEngineLogic::AddInteractableToCorrectVector(const vector<Interactable*>& interactables)
{
	for (Interactable* interactable : interactables)
	{
		if (interactable->GetInteractableType() == BOOK)
		{
			BookInteractable* bookInteractableChild = dynamic_cast<BookInteractable*>(interactable);
			if (bookInteractableChild->GetBookInteractableType() == SIMPLE)
			{
				m_GameMapObjects.simpleBookInteractables.push_back(dynamic_cast<SimpleBookInteractable*>(bookInteractableChild));
			}
		}
		else if (interactable->GetInteractableType() == DOOR)
		{
			DoorInteractableTemplate* doorInteractableTemplate = dynamic_cast<DoorInteractableTemplate*>(interactable);
			if (doorInteractableTemplate->GetDoorInteractableType() == SIMPLE_DOOR)
			{
				m_GameMapObjects.doorInteractables.push_back(dynamic_cast<DoorInteractable*>(doorInteractableTemplate));
			}
		}
		else if (interactable->GetInteractableType() == NPC)
		{

		}
	}
}
