#pragma once
#include "PushInteractable.h"

//A key interactable that can be picked up and is stored in the virtual inventory
class RandomPushInteractable final : public PushInteractable
{
public:
	//Constructor
	RandomPushInteractable(int id, const std::string& textureFileLocation, sf::Vector2f position, const std::string& fileOfOrigin,
		float speed, sf::Vector2f minBounds, sf::Vector2f maxBounds, std::string soundLocation, std::string pushSoundLocation);

	void Draw(sf::RenderWindow& mainWindow) override;

	//Interaction with interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Message to be displayed when interacted with
	std::string Message() override;
};