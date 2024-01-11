#include "GameEngineLogic.h"

using namespace sf;
using namespace std;

void GameEngineLogic::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Update(dtAsSeconds, mainWindow, isLeftClicked);
		return;
	}
	mainWindow.setMouseCursorVisible(false);

	m_Player.Update(dtAsSeconds);

	//Detect collisions
	DetectCollisions(m_Player);

	m_GameView.setCenter(m_Player.GetCenter());

	UpdateInteractable(dtAsSeconds);

	PressEToInteractCheck();

	if (b_FoundBookOverlayActive)
	{
		UpdateFoundBookOverlay(dtAsSeconds);
	}
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

void GameEngineLogic::UpdateFoundBookOverlay(const float dtAsSeconds)
{
	m_SecondsSinceOverlayActive += dtAsSeconds;
	m_Opacity = static_cast<Uint8>(255 - (255 * (m_SecondsSinceOverlayActive / TIME_OF_BOOK_OVERLAY_ON_SCREEN_IN_SECONDS)));
	m_Opacity = max(m_Opacity, static_cast<Uint8>(0));
	if (m_SecondsSinceOverlayActive > TIME_OF_BOOK_OVERLAY_ON_SCREEN_IN_SECONDS)
	{
		b_FoundBookOverlayActive = false;
		m_SecondsSinceOverlayActive = 0;
		m_EmotionNameOfFoundBook = "";
		m_Opacity = 255;
	}
	else
	{
		b_FoundBookOverlayActive = true;
	}
}

