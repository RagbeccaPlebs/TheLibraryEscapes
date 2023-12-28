#include "BookInteractable.h"
#include "GameEngineLogic.h"
#include "SimpleBookInteractable.h"

using namespace std;

void GameEngineLogic::LoadMap(const string& mapName)
{
	m_Map = new Map(mapName);

	m_PlayerSpawnLocation = m_Map->GetPlayerSpawnLocation("south");

	AddInteractableToCorrectVector(m_Map->GetInteractables());
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
