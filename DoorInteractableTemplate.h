#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Interactable.h"

enum DoorInteractableType
{
	SIMPLE_DOOR,
	TRAPDOOR
};

class DoorInteractableTemplate : public Interactable
{
protected:
	DoorInteractableType m_DoorInteractableType;
	bool b_IsOpen;
	std::string m_MapToMoveToName;
	sf::Vector2f m_MapToMoveToPosition;
	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_Sound;
public:
	virtual void Update(float dtAsSeconds) = 0;
	std::pair<InteractableType, int> Interact() override;
	bool CanInteract(Player& player) override;
	void PlaySound();

	bool GetOpen();
	DoorInteractableType GetDoorInteractableType();
};
