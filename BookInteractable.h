#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.h"

enum BookInteractableType
{
	SIMPLE
};

class BookInteractable : public Interactable
{
protected:
	BookInteractableType m_BookInteractableType;
public:
	virtual void Update(float dtAsSeconds) = 0;
	std::pair<InteractableType, int> Interact() override;
	bool CanInteract(Player& player) override;
	virtual ~BookInteractable() {};

	BookInteractableType GetBookInteractableType();
};
