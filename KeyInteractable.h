#pragma once
#include "PickupInventoryInteractable.h"

class KeyInteractable : public PickupInventoryInteractable
{
protected:
	void SavePickupToFile() override;
public:
	KeyInteractable(const int id, const std::string& textureFileLocation, sf::Vector2f position);

	void Update(float dtAsSeconds) override;
	std::pair<std::string, sf::Vector2f> Interact() override;
	std::string Message() override;
};
