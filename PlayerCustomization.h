#pragma once

#include "Button.h"
#include "Player.h"

class PlayerCustomization
{
	//PlayerMovement
	PlayerMovement& m_PlayerMovement;

	//Player
	Player& m_Player;

	//The direction the player is facing
	Side m_Direction = DOWN;

	//Functions to move character
	void TurnCharacter(Side direction);
	void TurnCharacterLeft();
	void TurnCharacterRight();

	//Buttons to move character
	Button m_TurnLeftButton;
	Button m_TurnRightButton;
	Button m_ContinueButton;
	Button m_BackToMenuButton;

	//Customization Buttons
	Button m_BaseLayerButton;
	Button m_LowerLayerButton;
	Button m_CloakLayerButton;
	Button m_FaceItemLayerButton;
	Button m_HairLayerButton;
	Button m_HatLayerButton;

	// Mouse Positions
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;

	//Game Player Customization specific Views
	sf::View m_ClothesView;
	sf::View m_PlayerView;

	//Are the customization files loaded?
	bool b_FilesLoaded = false;

	//Initialise the buttons and place them in the correct position
	void InitButtons(const sf::Vector2f& paddingButtons, const sf::Vector2f& paddingCustomizationButtons, const sf::Color& hoverColor, const sf::Color& idleColor,
		const sf::Color& activeColor, float screenWidth, float screenHeight, const sf::Font& font);
public:
	//Constructors, destructors and copy assignment operators
	PlayerCustomization() = default;
	PlayerCustomization(Player& player, PlayerMovement& playerMovement, const sf::RenderWindow& mainWindow, const sf::Font& font);
	PlayerCustomization& operator=(const PlayerCustomization& playerCustomization);
	~PlayerCustomization() = default;
	PlayerCustomization(PlayerCustomization& playerCustomization);

	//Game Logic Runners
	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayerCustomizationSelectorEnabled, GameState& gameState, const sf::Vector2f& playerSpawnLocation,
		const bool& isEscapePressed);
};