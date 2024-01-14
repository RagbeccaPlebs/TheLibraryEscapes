#pragma once

#include <SFML/Graphics.hpp>
#include "DoorInteractableTemplate.h"

class DoorInteractable final : public DoorInteractableTemplate
{
public:
	DoorInteractable(int id, sf::Vector2f position, const std::string& mapToMoveTo,
		sf::Vector2f mapPositionToMoveTo, const std::string& textureFileLocation, const std::string& inactiveTextureFileLocation,
		int keyId, const std::string& soundFileLocation, const std::string& inactiveSoundFileLocation);
	void Update(float dtAsSeconds) override;

	bool CheckIfDoorIsActive(const int id) const;
};
