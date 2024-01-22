#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.h"

//Types in which the Pickups come in
enum PickupType
{
	BOOK,
	KEY
};

//A parent Pickup interactable that is the base of all Pickups which go to the virtual 
class PickupInventoryInteractable : public Interactable
{
protected:
	//The type of which the child class is
	PickupType m_PickupType = BOOK;

	//Protected virtual Functions to pass along to child classes
	virtual void SavePickupToFile() = 0;
public:
	//Virtual Functions to pass along to child classes
	virtual void Update(float dtAsSeconds, Player& player) override = 0;
	virtual std::pair<std::string, sf::Vector2f> Interact() override = 0;
	virtual std::string Message() override = 0;

	//Getters
	PickupType GetPickupType() const;

	//Getter from String to PickupType
	static PickupType GetPickupTypeFromString(const std::string& pickupType);
};
