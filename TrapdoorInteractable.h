#pragma once

#include <SFML/Graphics.hpp>
#include "DoorInteractableTemplate.h"

class TrapdoorInteractable final : public DoorInteractableTemplate
{
public:
	TrapdoorInteractable(int id, sf::Vector2f position, const std::string& mapToMoveTo,
		sf::Vector2f mapPositionToMoveTo, const std::string& textureFileLocation, bool isOpen, const std::string& soundFileLocation);
	void Update(float dtAsSeconds) override;
};