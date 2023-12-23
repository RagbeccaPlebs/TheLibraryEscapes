#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

enum InteractableType
{
	DOOR,
	BOOK,
	NPC
};

class Interactable
{
protected:
	int m_Id;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Vector2f m_Position;
	sf::FloatRect m_CollisionBox;
	InteractableType m_InteractableType;

public:
	virtual void Update(float dtAsSeconds) = 0;
	void Draw(sf::RenderWindow& mainWindow);
	virtual std::pair<InteractableType, int> Interact() = 0;
	virtual bool CanInteract(Player& player) = 0;
	virtual ~Interactable() {}

	sf::Sprite GetSprite();
	sf::FloatRect GetCollisionBox();
	sf::Texture GetTexture();
	InteractableType GetInteractableType();
	int GetId() const;
};