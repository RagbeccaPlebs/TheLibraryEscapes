#pragma once
#include "PushInteractable.h"

//A key interactable that can be picked up and is stored in the virtual inventory
class LocationPushInteractable final : public PushInteractable
{
protected:
	sf::RectangleShape m_FinalPosition;
public:
	//Constructor
	LocationPushInteractable(const int id, const std::string& textureFileLocation, sf::Vector2f position, sf::Vector2f finalPosition, const std::string& fileOfOrigin);

	//Interaction with interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Message to be displayed when interacted with
	std::string Message() override;
};