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

	if (b_CenterOverlayActive)
	{
		UpdateCenterOverlay(dtAsSeconds);
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
			isOverlayApplicable = true;
		}
	}

	b_BottomOverlayActive = isOverlayApplicable;
}

void GameEngineLogic::UpdateCenterOverlay(const float dtAsSeconds)
{
	m_SecondsSinceCenterOverlayActive += dtAsSeconds;
	m_Opacity = static_cast<Uint8>(255 - (255 * (m_SecondsSinceCenterOverlayActive / TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS)));
	m_Opacity = max(m_Opacity, static_cast<Uint8>(0));
	if (m_SecondsSinceCenterOverlayActive > TIME_OF_CENTER_OVERLAY_ON_SCREEN_IN_SECONDS)
	{
		ResetCenterOverlay();
	}
	else
	{
		b_CenterOverlayActive = true;
	}
}

void GameEngineLogic::ResetCenterOverlay()
{
	b_CenterOverlayActive = false;
	m_SecondsSinceCenterOverlayActive = 0;
	m_OverlayCenterText = "";
	m_Opacity = 255;
}

