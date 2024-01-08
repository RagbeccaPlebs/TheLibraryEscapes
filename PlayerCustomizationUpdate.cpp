#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Update(float dtAsSeconds, RenderWindow& mainWindow)
{
	if (!b_FilesLoaded)
	{
		m_Player->m_PlayerTexture.LoadAllFiles();
		b_FilesLoaded = true;
	}
	mainWindow.setMouseCursorVisible(true);

	UpdateMousePositions(mainWindow);
	m_ContinueButton.Update(m_MousePosView);
	m_BackToMenuButton.Update(m_MousePosView);
	m_TurnRightButton.Update(m_MousePosView);
	m_TurnLeftButton.Update(m_MousePosView);
	m_BaseLayerButton.Update(m_MousePosView);
	m_LowerLayerButton.Update(m_MousePosView);
	m_CloakLayerButton.Update(m_MousePosView);
	m_FaceItemLayerButton.Update(m_MousePosView);
	m_HairLayerButton.Update(m_MousePosView);
	m_HatLayerButton.Update(m_MousePosView);
}

void PlayerCustomization::UpdateMousePositions(const RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}