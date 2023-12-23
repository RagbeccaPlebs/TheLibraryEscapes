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
}

void GameEngineLogic::UpdateInteractable(float dtAsSeconds)
{
	for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
	{
		simpleBookInteractable->Update(dtAsSeconds);
	}
}

