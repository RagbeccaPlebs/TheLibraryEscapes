#include "PlayerCustomization.h"

#include <future>

#include "Constants.h"
#include "Engine.h"

using namespace sf;
using namespace std;

void PlayerCustomization::TurnCharacter(const Side direction)
{
	m_Direction = direction;
	switch (direction)
	{
	case NONE:
		//NONE should act like DOWN
	case DOWN:
		m_Player.SetTextureLocation(m_PlayerMovement.GetIdleSouth().spriteLocation[0]);
		break;
	case LEFT:
		m_Player.SetTextureLocation(m_PlayerMovement.GetIdleWest().spriteLocation[0]);
		break;
	case UP:
		m_Player.SetTextureLocation(m_PlayerMovement.GetIdleNorth().spriteLocation[0]);
		break;
	case RIGHT:
		m_Player.SetTextureLocation(m_PlayerMovement.GetIdleEast().spriteLocation[0]);
		break;

	}
}

void PlayerCustomization::TurnCharacterLeft()
{
	switch (m_Direction)
	{
	case NONE:
		//NONE should act like DOWN
	case DOWN:
		TurnCharacter(LEFT);
		break;
	case LEFT:
		TurnCharacter(UP);
		break;
	case UP:
		TurnCharacter(RIGHT);
		break;
	case RIGHT:
		TurnCharacter(DOWN);
		break;
	}
}

void PlayerCustomization::TurnCharacterRight()
{
	switch (m_Direction)
	{
	case NONE:
		//NONE should act like DOWN
	case DOWN:
		TurnCharacter(RIGHT);
		break;
	case RIGHT:
		TurnCharacter(UP);
		break;
	case UP:
		TurnCharacter(LEFT);
		break;
	case LEFT:
		TurnCharacter(DOWN);
		break;
	}
}

PlayerCustomization::PlayerCustomization(Player& player, PlayerMovement& playerMovement, const RenderWindow& mainWindow) : m_PlayerMovement(playerMovement), m_Player(player)
{
	const float screenWidth = static_cast<float>(mainWindow.getSize().x);
	const float screenHeight = static_cast<float>(mainWindow.getSize().y);

	future<bool> areFilesLoaded = std::async(std::launch::async, &PlayerTexture::LoadAllFiles, &(m_Player.m_PlayerTexture));
	b_FilesLoaded = areFilesLoaded.get();

	m_ClothesView = mainWindow.getDefaultView();
	m_ClothesView.setCenter(Vector2f(screenWidth / 2.f, screenHeight / 2.f));
	m_PlayerView = mainWindow.getDefaultView();
	m_PlayerView.zoom(0.1f);

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f sizeButtons(300.f, 100.f);
	const Vector2f sizeCustomizationButtons(200.f, 100.f);
	InitButtons(sizeButtons, sizeCustomizationButtons, hoverColor, idleColor, activeColor, screenWidth, screenHeight);
	m_Player.Spawn(Vector2f(m_PlayerView.getCenter().x - (m_PlayerView.getSize().x / 12.0f), m_PlayerView.getCenter().y));
}


PlayerCustomization& PlayerCustomization::operator=(const PlayerCustomization& playerCustomization)
{
	if (this == &playerCustomization)
	{
		return *this;
	}
	this->m_Player = playerCustomization.m_Player;
	this->m_PlayerMovement = playerCustomization.m_PlayerMovement;
	this->m_ClothesView = playerCustomization.m_ClothesView;
	this->m_BackToMenuButton = playerCustomization.m_BackToMenuButton;
	this->m_ContinueButton = playerCustomization.m_ContinueButton;
	this->m_TurnLeftButton = playerCustomization.m_TurnLeftButton;
	this->m_TurnRightButton = playerCustomization.m_TurnRightButton;

	return *this;
}

PlayerCustomization::PlayerCustomization(PlayerCustomization& playerCustomization) : m_PlayerMovement(playerCustomization.m_PlayerMovement), m_Player(playerCustomization.m_Player)
{
	m_ClothesView = playerCustomization.m_ClothesView;
	m_BackToMenuButton = playerCustomization.m_BackToMenuButton;
	m_ContinueButton = playerCustomization.m_ContinueButton;
	m_TurnLeftButton = playerCustomization.m_TurnLeftButton;
	m_TurnRightButton = playerCustomization.m_TurnRightButton;
}

void PlayerCustomization::InitButtons(const Vector2f& sizeButtons, const Vector2f& sizeCustomizationButtons, const Color& hoverColor, const Color& idleColor, const Color& activeColor, const float screenWidth, const float screenHeight)
{
	const Vector2f continueButtonLocation(((screenWidth / 4.f) * 3.f - (sizeButtons.x / 2.f)), (screenHeight / 4.f) * 3.f);
	const Vector2f rightButtonLocation(((screenWidth / 4.f) * 3.f - (sizeButtons.x / 2.f)), (screenHeight / 2.f) + 100.f);
	const Vector2f leftButtonLocation(((screenWidth / 4.f) - (sizeButtons.x / 2.f)), (screenHeight / 2.f) + 100.f);
	const Vector2f backToMenuButtonLocation(((screenWidth / 4.f) - (sizeButtons.x / 2.f)), (screenHeight / 4.f) * 3.f);
	m_TurnLeftButton = Button(leftButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::LEFT_MESSAGE, 40, idleColor, hoverColor, activeColor);
	m_TurnRightButton = Button(rightButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::RIGHT_MESSAGE, 40, idleColor, hoverColor, activeColor);
	m_ContinueButton = Button(continueButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::CONTINUE_MESSAGE, 40, idleColor, hoverColor, activeColor);
	m_BackToMenuButton = Button(backToMenuButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::EXIT_TO_MENU_MESSAGE, 40, idleColor, hoverColor, activeColor);

	const Vector2f baseLayerButtonLocation((((screenWidth / 16.f) * 3.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	const Vector2f lowerLayerButtonLocation((((screenWidth / 16.f) * 5.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	const Vector2f cloakLayerButtonLocation((((screenWidth / 16.f) * 7.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	const Vector2f faceItemLayerButtonLocation((((screenWidth / 16.f) * 9.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	const Vector2f hairLayerButtonLocation((((screenWidth / 16.f) * 11.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	const Vector2f hatLayerButtonLocation((((screenWidth / 16.f) * 13.f) - (sizeCustomizationButtons.x / 2.f)), (screenHeight / 4.f));
	m_BaseLayerButton = Button(baseLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::SKIN_COLOR_MESSAGE, 30, idleColor, hoverColor, activeColor);
	m_LowerLayerButton = Button(lowerLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::CLOTHES_MESSAGE, 30, idleColor, hoverColor, activeColor);
	m_CloakLayerButton = Button(cloakLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::CLOAK_MESSAGE, 30, idleColor, hoverColor, activeColor);
	m_FaceItemLayerButton = Button(faceItemLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::FACE_ITEM_MESSAGE, 30, idleColor, hoverColor, activeColor);
	m_HairLayerButton = Button(hairLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::HAIR_MESSAGE, 30, idleColor, hoverColor, activeColor);
	m_HatLayerButton = Button(hatLayerButtonLocation, sizeCustomizationButtons, Files::FONT_FILE, Message::HAT_MESSAGE, 30, idleColor, hoverColor, activeColor);
}

