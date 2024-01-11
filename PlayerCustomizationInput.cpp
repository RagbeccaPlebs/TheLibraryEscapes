#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Input(RenderWindow& mainWindow, bool& isPlayerCustomizationSelectorEnabled, bool& isPlaying, const Vector2f& playerSpawnLocation,
	const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		isPlaying = false;
	}

	if (m_ContinueButton.IsPressed())
	{
		m_Player->Spawn(playerSpawnLocation);
		m_Player->SaveLayers();
		m_Player->m_PlayerTexture.CleanAllFiles();
		b_FilesLoaded = false;
		isPlayerCustomizationSelectorEnabled = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		isPlaying = false;
	}

	if (m_TurnLeftButton.IsPressed())
	{
		TurnCharacterLeft();
	}

	if (m_TurnRightButton.IsPressed())
	{
		TurnCharacterRight();
	}

	if (m_BaseLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(BASE);
	}

	if (m_LowerLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(LOWER);
	}

	if (m_CloakLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(CLOAK);
	}

	if (m_FaceItemLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(FACE_ITEM);
	}

	if (m_HairLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(HAIR);
	}

	if (m_HatLayerButton.IsPressed())
	{
		m_Player->UpdatePlayerTexture(HAT);
	}
}