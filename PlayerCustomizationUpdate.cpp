#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (!b_FilesLoaded)
	{
		m_Player->m_PlayerTexture.LoadAllFiles();
		b_FilesLoaded = true;
	}
	mainWindow.setMouseCursorVisible(true);

	UpdateMousePositions(mainWindow);
	m_ContinueButton.Update(m_MousePosView, mainWindow);
	m_BackToMenuButton.Update(m_MousePosView, mainWindow);
	m_TurnRightButton.Update(m_MousePosView, mainWindow);
	m_TurnLeftButton.Update(m_MousePosView, mainWindow);
	m_BaseLayerButton.Update(m_MousePosView, mainWindow);
	m_LowerLayerButton.Update(m_MousePosView, mainWindow);
	m_CloakLayerButton.Update(m_MousePosView, mainWindow);
	m_FaceItemLayerButton.Update(m_MousePosView, mainWindow);
	m_HairLayerButton.Update(m_MousePosView, mainWindow);
	m_HatLayerButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_ContinueButton.Press(m_MousePosView);
		m_BackToMenuButton.Press(m_MousePosView);
		m_TurnRightButton.Press(m_MousePosView);
		m_TurnLeftButton.Press(m_MousePosView);
		m_BaseLayerButton.Press(m_MousePosView);
		m_LowerLayerButton.Press(m_MousePosView);
		m_CloakLayerButton.Press(m_MousePosView);
		m_FaceItemLayerButton.Press(m_MousePosView);
		m_HairLayerButton.Press(m_MousePosView);
		m_HatLayerButton.Press(m_MousePosView);
	}
}

void PlayerCustomization::UpdateMousePositions(const RenderWindow& mainWindow)
{
	m_MousePosScreen = sf::Mouse::getPosition();
	m_MousePosWindow = sf::Mouse::getPosition(mainWindow);
	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
}