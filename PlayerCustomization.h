#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Player.h"

class PlayerCustomization
{
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	//PlayerMovement
	PlayerMovement* m_PlayerMovement;

	//Player
	Player* m_Player;

	Direction m_Direction = DOWN;

	void TurnCharacter(Direction direction);
	void TurnCharacterLeft();
	void TurnCharacterRight();

	Button m_TurnLeftButton;
	Button m_TurnRightButton;
	Button m_ContinueButton;
	Button m_BackToMenuButton;

	// Mouse Positions
	sf::Vector2i m_MousePosScreen;
	sf::Vector2i m_MousePosWindow;
	sf::Vector2f m_MousePosView;

	//Game Player Customization specific Views
	sf::View m_ClothesView;
	sf::View m_PlayerView;

	void UpdateMousePositions(const sf::RenderWindow& mainWindow);
public:
	PlayerCustomization() = default;
	PlayerCustomization(Player* player, PlayerMovement* playerMovement, const sf::RenderWindow& mainWindow);
	PlayerCustomization& operator=(const PlayerCustomization& playerCustomization);
	~PlayerCustomization() = default;
	PlayerCustomization(PlayerCustomization& playerCustomization);

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWindow, bool& isPlayerCustomizationSelectorEnabled, bool& isPlaying, const sf::Vector2f& playerSpawnLocation);
};