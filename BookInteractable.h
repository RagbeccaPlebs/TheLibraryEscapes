#pragma once

#include "PickupInventoryInteractable.h"

//A parent Book interactable that is the base of all Books
class BookInteractable : public PickupInventoryInteractable
{
protected:
	//Virtual Functions to pass along to child classes
	void SavePickupToFile() override = 0;
public:
	//Interaction with Interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Message to be displayed when interacted with
	std::string Message() override;

	void Unload() override;
};