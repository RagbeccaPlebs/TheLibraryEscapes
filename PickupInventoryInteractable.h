#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.h"

enum PickupType
{
	BOOK,
	KEY
};


class PickupInventoryInteractable : public Interactable
{
protected:
	PickupType m_PickupType = BOOK;
	virtual void SavePickupToFile() = 0;

public:
	virtual void Update(float dtAsSeconds) override = 0;
	virtual std::pair<std::string, sf::Vector2f> Interact() override = 0;
	virtual std::string Message() override = 0;

	PickupType GetPickupType() const;

	static PickupType GetPickupTypeFromString(const std::string& pickupType);
};
