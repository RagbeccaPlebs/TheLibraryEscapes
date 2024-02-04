#include "Constants.h"
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
	for (PushInteractable* pushInteractable : m_GameMapObjects.pushInteractables)
	{
		if (pushInteractable->CanInteract(m_Player))
		{
			pair<string, Vector2f> pushInteractableReturn = pushInteractable->Interact();
			if (pushInteractableReturn.first == Message::CORRECT_LOCATION_MESSAGE)
			{
				m_OverlayCenterText = pushInteractable->Message();
				b_CenterOverlayActive = true;
				pushInteractable->PlayAlternativeSound();
			}
			else if (pushInteractableReturn.first == Keywords::PUSHABLE_OBJECT_KEYWORD)
			{
				pushInteractable->PlayPushSound();
			}
		}
	}
	InputInteractable();
}


void GameEngineLogic::InputInteractable()
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
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
						m_OverlayCenterText = doorInteractable->Message();
						b_CenterOverlayActive = true;
						doorInteractable->PlaySound();
					}
				}

			}
		}
		for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
		{
			if (pickupInventoryInteractable->CanInteract(m_Player))
			{
				pickupInventoryInteractable->Interact();
				ResetCenterOverlay();
				m_OverlayCenterText = pickupInventoryInteractable->Message();
				b_CenterOverlayActive = true;
			}
		}
	}
}
