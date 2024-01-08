﻿#pragma once

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
	void Update(float dtAsSeconds) override = 0;
	std::pair<std::string, sf::Vector2f> Interact() override;
	bool CanInteract(Player& player) override;
	void PlaySound();

	~DoorInteractableTemplate() override;

	bool GetOpen() const;
	DoorInteractableType GetDoorInteractableType() const;
};