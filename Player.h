#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "PlayerMovement.h"

class Player {
private:
	enum lastPressed {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};

	lastPressed m_lastButtonPressed = lastPressed::DOWN;
	//Make sure buttons aren't equal to force correct placement of player
	lastPressed m_oldLastButtonPressed;

	int textureLocationX = 0;
	int textureLocationY = 0;

	//PlayerMovement
	PlayerMovement m_PM;

	PlayerMovement::SpriteSheet m_currentSpriteSheet;
	PlayerMovement::SingleSprite m_currentSprite;
	float m_SecondsSinceLastAnimationUpdate = 0;

	//The Sprites of the player (Of the layers)
	sf::Sprite m_SpriteBase;
	sf::Sprite m_SpriteLowerLayer;
	sf::Sprite m_SpriteCloak;
	sf::Sprite m_SpriteFaceItem;
	sf::Sprite m_SpriteHair;

	sf::Sprite setSpriteTextureLocation(sf::Sprite& sprite);

	//Send a part of the sprite
	sf::Sprite getSpriteBase();
	sf::Sprite getSpriteLowerLayer();
	sf::Sprite getSpriteCloak();
	sf::Sprite getSpriteFaceItem();
	sf::Sprite getSpriteHair();

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	//Where is the player
	sf::Vector2f m_Position;

	//How fast is the character
	float m_Speed = 50.0f;

	//Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	//Texture method
	void playerAnimationUpdate(bool isMoving);

	void setPositionAllSprites();

	//Math
	int getSequenceWithFour(int index);
	int getSequenceWithEight(int index);
public:
	Player();

	void spawn(sf::Vector2f startPosition);

	void handleInput();

	sf::FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	sf::FloatRect getFeet();
	sf::FloatRect getHead();
	sf::FloatRect getRight();
	sf::FloatRect getLeft();

	//Stop movement
	void stopDown(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopUp(float position);

	// Send a copy of the sprite to main
	std::array<sf::Sprite, 5> getSprites();

	void setTextureLocation(sf::Vector2i location);

	// Where is the center of the character
	sf::Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};