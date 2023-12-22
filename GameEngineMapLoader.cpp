#include "BookInteractable.h"
#include "GameEngineLogic.h"
#include "SimpleBookInteractable.h"

using namespace std;

void GameEngineLogic::LoadMap(const string& mapName)
{
	m_Map = new Map(mapName);

	m_PlayerSpawnLocation = m_Map->GetPlayerSpawnLocation("south");
	for (int i = 0; i < m_Map->GetInteractables().size(); i++)
	{
		InteractableType t2 = m_Map->GetInteractables().at(i)->GetInteractableType();
		if (m_Map->GetInteractables().at(i)->GetInteractableType() == BOOK)
		{
			auto* bookInteractableChild = dynamic_cast<BookInteractable*>(m_Map->GetInteractables().at(i));
			if (bookInteractableChild->GetBookInteractableType() == SIMPLE)
			{
				auto* simpleBookInteracbleChild =  dynamic_cast<SimpleBookInteractable*>(bookInteractableChild);
				if (simpleBookInteracbleChild)
				{
					printf("WE GOT IT!\n");
				}
			}
		}
	}
}
