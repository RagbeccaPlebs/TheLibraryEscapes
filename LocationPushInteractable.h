#pragma once
#include "PushInteractable.h"

//A key interactable that can be picked up and is stored in the virtual inventory
class LocationPushInteractable final : public PushInteractable
{
	bool CheckIfDistanceIsSmallEnough() const;
protected:
	sf::FloatRect m_FinalPosition;
	sf::Texture m_TextureFinalLocation;
	sf::Sprite m_SpriteFinalLocation;
public:
	//Constructor
	LocationPushInteractable(int id, const std::string& textureFileLocation, const std::string& textureLocationFileLocation, sf::Vector2f position, sf::Vector2f finalPosition, const std::string& fileOfOrigin,
		float speed, sf::Vector2f minBounds, sf::Vector2f maxBounds, const std::string& soundLocation, const std::string& pushSoundLocation, bool isActive);

	void Draw(sf::RenderWindow& mainWindow) override;

	//Interaction with interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Message to be displayed when interacted with
	std::string Message() override;
};