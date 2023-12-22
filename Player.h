#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "PlayerMovement.h"
#include "PlayerTexture.h"

class Player
{
	enum LastPressed {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	LastPressed m_LastButtonPressed = LastPressed::UP;
	//Make sure buttons aren't equal to force correct placement of player
	LastPressed m_OldLastButtonPressed;

	int m_TextureLocationX = 0;
	int m_TextureLocationY = 0;

	//Player Movement & Animation
	PlayerMovement m_PlayerMovement;

	PlayerMovement::SpriteSheet m_CurrentSpriteSheet;
	PlayerMovement::SingleSprite m_CurrentSprite;
	float m_SecondsSinceLastAnimationUpdate = 0;

	//Player looks
	void SetInitialTextures();
	void SetSpriteTextureLocationAllSprites();

	std::string m_TextureBaseLocation;
	std::string m_TextureLowerLayerLocation;
	std::string m_TextureCloakLocation;
	std::string m_TextureFaceItemLocation;
	std::string m_TextureHairLocation;
	std::string m_TextureHatLocation;

	//The Sprites of the player (Of the layers)
	sf::Sprite m_SpriteBase = sf::Sprite();
	sf::Sprite m_SpriteLowerLayer = sf::Sprite();
	sf::Sprite m_SpriteCloak = sf::Sprite();
	sf::Sprite m_SpriteFaceItem = sf::Sprite();
	sf::Sprite m_SpriteHair = sf::Sprite();
	sf::Sprite m_SpriteHat = sf::Sprite();

	void SetSpriteTextureLocation(sf::Sprite& sprite) const;

	// Which directions is the character currently moving in
	bool b_LeftPressed = false;
	bool b_RightPressed = false;
	bool b_UpPressed = false;
	bool b_DownPressed = false;

	//Where is the player
	sf::Vector2f m_Position;

	//How fast is the character
	float m_Speed = 50.0f;

	//Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	//Interactable locations
	sf::FloatRect m_InteractableBox;

	//Texture method
	void PlayerAnimationUpdate(bool isMoving);

	void SetPositionAllSprites();

	//Math
	int GetSequenceWithFour(int index);
	int GetSequenceWithEight(int index);
public:
	Player();

	void Spawn(sf::Vector2f startPosition);

	void HandleInput();

	sf::FloatRect GetPosition();

	// A rectangle representing the position of different parts of the sprite
	sf::FloatRect GetFeet();
	sf::FloatRect GetHead();
	sf::FloatRect GetRight();
	sf::FloatRect GetLeft();

	//Stop movement
	void StopDown(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopUp(float position);

	// Send a copy of the sprite to main
	std::vector<sf::Sprite*> GetSprites();

	void SetTextureLocation(sf::Vector2i location);

	// Where is the center of the character
	sf::Vector2f GetCenter();

	sf::FloatRect GetInteractableBox();

	// We will call this function once every frame
	void Update(float elapsedTime);

	void UpdatePlayerTexture();

	//Public Player Looks
	PlayerTexture playerTexture;
};
