#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Update(dtAsSeconds, mainWindow);
		return;
	}
	mainWindow.setMouseCursorVisible(false);

	m_Player.Update(dtAsSeconds);

	//Detect collisions
	DetectCollisions(m_Player);

	m_GameView.setCenter(m_Player.GetCenter());

	UpdateInteractable(dtAsSeconds);

	PressEToInteractCheck();
}

void GameEngineLogic::UpdateInteractable(float dtAsSeconds)
{
	for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
	{
		simpleBookInteractable->Update(dtAsSeconds);
	}
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		doorInteractable->Update(dtAsSeconds);
	}
}

void GameEngineLogic::PressEToInteractCheck()
{
	bool isOverlayApplicable = false;
	for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
	{
		if (simpleBookInteractable->CanInteract(m_Player))
		{
			isOverlayApplicable = true;
		}
	}
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		if (doorInteractable->CanInteract(m_Player))
		{
			if (doorInteractable->GetOpen())
			{
				isOverlayApplicable = true;
			}
		}
	}

	b_EOverlayActive = isOverlayApplicable;
}

