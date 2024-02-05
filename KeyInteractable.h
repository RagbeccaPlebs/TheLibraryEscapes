#pragma once
#include "PickupInventoryInteractable.h"

//A key interactable that can be picked up and is stored in the virtual inventory
class KeyInteractable final : public PickupInventoryInteractable
{
protected:
	//Save the Pickup to the GameFile
	void SavePickupToFile() override;
public:
	//Constructor
	KeyInteractable(const int id, const std::string& textureFileLocation, sf::Vector2f position, bool isActive);

	void Update(float dtAsSeconds, Player& player) override;

	//Interaction with interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Message to be displayed when interacted with
	std::string Message() override;

	void Unload() override;
};
