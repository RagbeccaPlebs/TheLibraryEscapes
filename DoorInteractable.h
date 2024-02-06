#pragma once

#include <SFML/Graphics.hpp>
#include "DoorInteractableTemplate.h"

//A Door interactable that can be locked, opened and 'closed but open'
class DoorInteractable final : public DoorInteractableTemplate
{
public:
	//Constructor
	DoorInteractable(int id, sf::Vector2f position, const std::string& mapToMoveTo,
		sf::Vector2f mapPositionToMoveTo, const std::string& textureFileLocation, const std::string& inactiveTextureFileLocation,
		int keyId, const std::string& soundFileLocation, const std::string& inactiveSoundFileLocation, bool isActive);

	void Update(const float& dtAsSeconds, Player& player) override;
private:
	//Check for Open Door
	static bool CheckIfDoorIsActive(const int& id);
};
