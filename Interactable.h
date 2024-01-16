#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

enum InteractableType
{
	DOOR,
	PICKUP,
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
	bool b_Active = false;
public:
	virtual void Update(float dtAsSeconds) = 0;
	void Draw(sf::RenderWindow& mainWindow);
	virtual std::pair<std::string, sf::Vector2f> Interact() = 0;
	virtual bool CanInteract(Player& player);
	virtual ~Interactable() = default;

	virtual std::string Message() = 0;

	sf::Sprite GetSprite();
	sf::FloatRect GetCollisionBox() const;
	sf::Texture GetTexture();
	InteractableType GetInteractableType() const;
	bool GetActive() const;
	int GetId() const;
};