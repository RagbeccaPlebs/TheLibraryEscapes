#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "PlayerMovement.h"
#include "PlayerTexture.h"

//Layers of the player look
enum Layer
{
	BASE,
	LOWER,
	CLOAK,
	FACE_ITEM,
	HAIR,
	HAT
};

class Player
{
	//States of which button was last pressed regarding the player movement

	//Storage of which button was last pressed
	Side m_LastButtonPressed = Side::UP;
	//Make sure buttons aren't equal to force correct placement of player
	Side m_OldLastButtonPressed;

	//The x and y location within the texture that should be displayed
	int m_TextureLocationX = 0;
	int m_TextureLocationY = 0;

	//Player Movement & Animation
	PlayerMovement m_PlayerMovement;

	//The Sprite-Sheet for animating a player
	PlayerMovement::SpriteSheet m_CurrentSpriteSheet;
	PlayerMovement::SingleSprite m_CurrentSprite;
	float m_SecondsSinceLastAnimationUpdate = 0;

	//Set initial textures from document
	void SetInitialTextures();
	void SetSpriteTextureLocationAllSprites();

	//The locations of the textures (Of the layers)
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

	//Update the sprite texture location with m_TextureLocationX and m_TextureLocationY
	void SetSpriteTextureLocation(sf::Sprite& sprite) const;

	// Which directions is the character currently moving in
	bool b_LeftPressed = false;
	bool b_RightPressed = false;
	bool b_UpPressed = false;
	bool b_DownPressed = false;
	bool b_ShiftPressed = false;

	//Pushing Variables
	Side m_SidePushing;
	bool b_Pushing = false;
	bool b_StartedPushing = false;
	bool b_ChangePushing = false;

	//Running Variables
	bool b_ChangeRunning = false;

	//Where is the player
	sf::Vector2f m_Position;

	//How fast is the character
	float m_Speed = Constant::PLAYER_WALK_SPEED;

	//Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	//Interactable locations
	sf::FloatRect m_InteractableBox;

	//Texture method
	void PlayerAnimationUpdate(bool isMoving);

	//Update ALL the sprite position of the sprites
	void SetPositionAllSprites();

	//Unique Math specific for Player calculations
	static int GetSequenceWithFour(int index);
	static int GetSequenceWithEight(int index);
public:
	//Constructor
	Player();

	//Spawn the player at the correct position
	void Spawn(sf::Vector2f startPosition);

	//Get the current position of the player
	sf::FloatRect GetPosition() const;

	// A rectangle representing the position of different parts of the sprite
	sf::FloatRect GetFeet() const;
	sf::FloatRect GetHead() const;
	sf::FloatRect GetRight() const;
	sf::FloatRect GetLeft() const;

	//Stop movement, used within the collision detection
	void StopDown(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopUp(float position);

	// Where is the center of the character, used for collision and view centralisation
	sf::Vector2f GetCenter() const;

	//For interaction and collision checks
	sf::FloatRect GetInteractableBox() const;

	//Public functions and variables used by the PlayerCustomization to change looks and locations
	PlayerTexture m_PlayerTexture;
	void SetTextureLocation(sf::Vector2i location);
	void SaveLayers() const;
	void UpdatePlayerTexture(Layer layer);

	//The Game Runners, will be called once every frame
	void HandleInput();
	void Update(float elapsedTime);
	std::vector<sf::Sprite*> GetSprites();

	//Utils
	static std::string GetFileName(const std::string& fileLocation);

	//Push movements
	void SetPushing(const Side& side);
	void StopPushing();

	bool GetDownPressed() const;
	bool GetRightPressed() const;
	bool GetLeftPressed() const;
	bool GetUpPressed() const;

	bool IsPushing() const;
};
