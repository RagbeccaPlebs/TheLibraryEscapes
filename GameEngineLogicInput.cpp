﻿#include "GameEngineLogic.h"

using namespace sf;
using namespace std;

void GameEngineLogic::Input(RenderWindow& mainWindow, bool& isPlaying)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Input(mainWindow, b_PlayerCustomizationSelectorEnabled, isPlaying, m_PlayerSpawnLocation);
		return;
	}

	m_Player.HandleInput();
	InputInteractable(mainWindow);
}


void GameEngineLogic::InputInteractable(RenderWindow& mainWindow)
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
		{
			if (simpleBookInteractable->CanInteract(m_Player))
			{
				const pair<string, Vector2f> bookValue = simpleBookInteractable->Interact();
				m_EmotionNameOfFoundBook = bookValue.first;
				b_FoundBookOverlayActive = true;
			}
		}
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
				} else
				{
					doorInteractable->PlaySound();
				}
				
			}
		}
	}
}
