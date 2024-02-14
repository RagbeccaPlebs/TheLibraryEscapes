#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

//Types in which the Interactables come in
enum InteractableType
{
	DOOR,
	PICKUP,
	PUSH_OBJECT
};

//The parent class of all Interactables
class Interactable
{
protected:
	//Variables used for interactable initialization
	int m_Id = -1;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Vector2f m_Position;
	sf::FloatRect m_InteractionBox;
	InteractableType m_InteractableType = PICKUP;
	bool b_Active = false;
	bool b_ConditionMet = false;
public:
	//Virtual Functions to pass along to child classes
	virtual void Update(const float& dtAsSeconds, Player& player) = 0;
	virtual std::pair<std::string, sf::Vector2f> Interact() = 0;
	virtual bool CanInteract(Player& player);
	virtual ~Interactable() = default;
	virtual std::string Message() = 0;

	//Basic Draw function which is virtual but defined
	virtual void Draw(sf::RenderWindow& mainWindow);

	//Getters
	sf::Sprite GetSprite();
	sf::FloatRect GetInteractionBox() const;
	sf::Texture GetTexture();
	InteractableType GetInteractableType() const;
	bool GetActive() const;
	int GetId() const;
	virtual void Unload() = 0;
	bool GetConditionMet() const;
	void Activate();

	static InteractableType GetInteractableTypeFromString(const std::string& interactableType);
};