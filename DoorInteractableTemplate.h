#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Interactable.h"

//Types in which the Doors come in
enum DoorInteractableType
{
	SIMPLE_DOOR,
	TRAPDOOR
};

//A parent Door Template for Door Interactables
class DoorInteractableTemplate : public Interactable
{
protected:
	//Door specific locked Values
	bool b_IsOpen;
	int m_KeyId;

	//Interaction Values
	DoorInteractableType m_DoorInteractableType;
	std::string m_MapToMoveToName;
	sf::Vector2f m_MapToMoveToPosition;

	//Door specific Values for Graphical and Sound Gameplay
	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_Sound;
	std::string m_SoundLocation;
	std::string m_InactiveSoundLocation;
	std::string m_InactiveTextureLocation;
	std::string m_TextureLocation;

	//Check for the Door their key is found (IF APPLICABLE)
	bool CheckIfKeyIsFound() const;
	void AddDoorToActiveDoors() const;
public:
	virtual void Update(float dtAsSeconds, Player& player) override = 0;
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Play sounds
	void PlaySound();

	//Unlock door if key is found
	bool TryUnlocking();

	//Message to be displayed when interacted with
	std::string Message() override;

	//Destructor to reset sound
	~DoorInteractableTemplate() override;

	//Getters
	bool GetOpen() const;
	int GetKeyId() const;
	DoorInteractableType GetDoorInteractableType() const;

	void Unload() override;
};
