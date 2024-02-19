#pragma once

#include "BookInteractable.h"

//A Simple book interactable that can be picked up and is stored in the virtual inventory
//Simple book meaning, no movement or changes
class SimpleBookInteractable final : public BookInteractable
{
protected:
	//Save the Pickup to the GameFile
	void SavePickupToFile() override;
public:
	//Constructor
	SimpleBookInteractable(int id, const std::string& textureFileLocation, sf::Vector2f position, EmotionType emotion, bool isActive);

	void Update(const float& dtAsSeconds, Player& player) override;
};
