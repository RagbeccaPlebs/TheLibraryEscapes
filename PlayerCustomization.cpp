#include "PlayerCustomization.h"

#include <future>

#include "Constants.h"
#include "Engine.h"

using namespace sf;
using namespace std;

//CONSTRUCTORS
PlayerCustomization::PlayerCustomization(Player& player, PlayerMovement& playerMovement, const RenderWindow& mainWindow, const Font& font) : m_PlayerMovement(playerMovement), m_Player(player)
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
	const Vector2f paddingButtons(100.f, 100.f);
	const Vector2f paddingCustomizationButtons(50.f,50.f);
	InitButtons(paddingButtons, paddingCustomizationButtons, hoverColor, idleColor, activeColor, screenWidth, screenHeight, font);
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

void PlayerCustomization::InitButtons(const Vector2f& paddingButtons, const Vector2f& paddingCustomizationButtons, const Color& hoverColor, const Color& idleColor, const Color& activeColor, const float screenWidth, const float screenHeight, const Font& font)
{
	const Vector2f continueButtonLocation(((screenWidth / 4.f) * 3.f), (screenHeight / 4.f) * 3.f);
	const Vector2f rightButtonLocation(((screenWidth / 4.f) * 3.f), (screenHeight / 2.f) + 100.f);
	const Vector2f leftButtonLocation(((screenWidth / 4.f)), (screenHeight / 2.f) + 100.f);
	const Vector2f backToMenuButtonLocation(((screenWidth / 4.f)), (screenHeight / 4.f) * 3.f);
	m_TurnLeftButton = Button(leftButtonLocation, paddingButtons, font,
		Message::LEFT_MESSAGE, 70, idleColor, hoverColor, activeColor, true);
	m_TurnRightButton = Button(rightButtonLocation, paddingButtons, font,
		Message::RIGHT_MESSAGE, 70, idleColor, hoverColor, activeColor, true);
	m_ContinueButton = Button(continueButtonLocation, paddingButtons, font,
		Message::CONTINUE_MESSAGE, 70, idleColor, hoverColor, activeColor, true);
	m_BackToMenuButton = Button(backToMenuButtonLocation, paddingButtons, font,
		Message::EXIT_TO_MENU_MESSAGE, 70, idleColor, hoverColor, activeColor, true);

	const Vector2f baseLayerButtonLocation((((screenWidth / 16.f) * 3.f)), (screenHeight / 4.f));
	const Vector2f lowerLayerButtonLocation((((screenWidth / 16.f) * 5.f)), (screenHeight / 4.f));
	const Vector2f cloakLayerButtonLocation((((screenWidth / 16.f) * 7.f)), (screenHeight / 4.f));
	const Vector2f faceItemLayerButtonLocation((((screenWidth / 16.f) * 9.f)), (screenHeight / 4.f));
	const Vector2f hairLayerButtonLocation((((screenWidth / 16.f) * 11.f)), (screenHeight / 4.f));
	const Vector2f hatLayerButtonLocation((((screenWidth / 16.f) * 13.f)), (screenHeight / 4.f));
	m_BaseLayerButton = Button(baseLayerButtonLocation, paddingCustomizationButtons, font, Message::SKIN_COLOR_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
	m_LowerLayerButton = Button(lowerLayerButtonLocation, paddingCustomizationButtons, font, Message::CLOTHES_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
	m_CloakLayerButton = Button(cloakLayerButtonLocation, paddingCustomizationButtons, font, Message::CLOAK_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
	m_FaceItemLayerButton = Button(faceItemLayerButtonLocation, paddingCustomizationButtons, font, Message::FACE_ITEM_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
	m_HairLayerButton = Button(hairLayerButtonLocation, paddingCustomizationButtons, font, Message::HAIR_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
	m_HatLayerButton = Button(hatLayerButtonLocation, paddingCustomizationButtons, font, Message::HAT_MESSAGE, 30, idleColor, hoverColor, activeColor, true);
}

//TURNING
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

//DRAW
void PlayerCustomization::Draw(RenderWindow& mainWindow)
{
	mainWindow.setView(m_ClothesView);

	m_TurnLeftButton.Draw(mainWindow);
	m_TurnRightButton.Draw(mainWindow);
	m_BackToMenuButton.Draw(mainWindow);
	m_ContinueButton.Draw(mainWindow);

	mainWindow.setView(m_PlayerView);

	RectangleShape r(Vector2f(20.f, 20.f));

	r.setPosition(0, 0);
	r.setFillColor(Color::Red);

	mainWindow.draw(r);
	for (const Sprite* sprite : m_Player.GetSprites()) {
		if (sprite->getTexture() != nullptr) {
			mainWindow.draw(*sprite);
		}
	}

	mainWindow.setView(m_ClothesView);
	m_BaseLayerButton.Draw(mainWindow);
	m_LowerLayerButton.Draw(mainWindow);
	m_CloakLayerButton.Draw(mainWindow);
	m_FaceItemLayerButton.Draw(mainWindow);
	m_HairLayerButton.Draw(mainWindow);
	m_HatLayerButton.Draw(mainWindow);
}

//INPUT
void PlayerCustomization::Input(RenderWindow& mainWindow, bool& isPlayerCustomizationSelectorEnabled, GameState& gameState, const Vector2f& playerSpawnLocation,
	const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		gameState = STOPPED;
	}

	if (m_ContinueButton.IsPressed())
	{
		m_Player.Spawn(playerSpawnLocation);
		m_Player.SaveLayers();
		m_Player.m_PlayerTexture.CleanAllFiles();
		b_FilesLoaded = false;
		isPlayerCustomizationSelectorEnabled = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		gameState = STOPPED;
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
		m_Player.UpdatePlayerTexture(BASE);
	}

	if (m_LowerLayerButton.IsPressed())
	{
		m_Player.UpdatePlayerTexture(LOWER);
	}

	if (m_CloakLayerButton.IsPressed())
	{
		m_Player.UpdatePlayerTexture(CLOAK);
	}

	if (m_FaceItemLayerButton.IsPressed())
	{
		m_Player.UpdatePlayerTexture(FACE_ITEM);
	}

	if (m_HairLayerButton.IsPressed())
	{
		m_Player.UpdatePlayerTexture(HAIR);
	}

	if (m_HatLayerButton.IsPressed())
	{
		m_Player.UpdatePlayerTexture(HAT);
	}
}

//UPDATE
void PlayerCustomization::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (!b_FilesLoaded)
	{
		m_Player.m_PlayerTexture.LoadAllFiles();
		b_FilesLoaded = true;
	}
	mainWindow.setMouseCursorVisible(true);

	m_MousePosView = mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));

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