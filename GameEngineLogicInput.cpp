#include "GameEngineLogic.h"

using namespace sf;
using namespace std;

void GameEngineLogic::Input(RenderWindow& mainWindow, bool& isPlaying, bool& isPaused, const bool& isEscapePressed)
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
				if (!simpleBookInteractable->GetActive())
				{
					continue;
				}
				const pair<string, Vector2f> bookValue = simpleBookInteractable->Interact();
				string emotion = bookValue.first;
				ResetCenterOverlay();
				m_OverlayCenterText = "You found a " + emotion + " book!";
				b_CenterOverlayActive = true;
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
				}
				else
				{
					if (!doorInteractable->TryUnlocking())
					{
						ResetCenterOverlay();
						m_OverlayCenterText = "The door is locked!";
						b_CenterOverlayActive = true;
						doorInteractable->PlaySound();
					}
				}

			}
		}
	}
}
