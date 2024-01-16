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
	//Locked
	bool b_IsOpen;
	int m_KeyId;

	//Interaction Types
	DoorInteractableType m_DoorInteractableType;
	std::string m_MapToMoveToName;
	sf::Vector2f m_MapToMoveToPosition;

	//Door specific items
	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_Sound;
	std::string m_SoundLocation;
	std::string m_InactiveSoundLocation;
	std::string m_InactiveTextureLocation;
	std::string m_TextureLocation;

	bool CheckIfKeyIsFound() const;
	void AddDoorToActiveDoors() const;
public:
	void Update(float dtAsSeconds) override = 0;
	std::pair<std::string, sf::Vector2f> Interact() override;
	void PlaySound();
	bool TryUnlocking();

	std::string Message() override;

	~DoorInteractableTemplate() override;

	bool GetOpen() const;
	int GetKeyId() const;
	DoorInteractableType GetDoorInteractableType() const;
};
