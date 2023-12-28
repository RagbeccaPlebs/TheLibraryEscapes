#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Input(RenderWindow& mainWindow, bool& isPlaying)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Input(mainWindow, b_PlayerCustomizationSelectorEnabled, isPlaying, m_PlayerSpawnLocation);
		return;
	}

	m_Player.HandleInput();
	InputInteractable();
}


void GameEngineLogic::InputInteractable()
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
		{
			if (simpleBookInteractable->CanInteract(m_Player))
			{
				simpleBookInteractable->Interact();
			}
		}
		for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
		{
			if (doorInteractable->CanInteract(m_Player))
			{
				if (doorInteractable->GetOpen())
				{
					doorInteractable->Interact();
				} else
				{
					doorInteractable->PlaySound();
				}
				
			}
		}
	}
}
