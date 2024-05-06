#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "Interactable.h"

//A parent Door Template for Door Interactables
class DoorInteractableTemplate : public Interactable
{
protected:
	//Door specific locked Values
	bool b_IsOpen;
	int m_KeyId;

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

	//Check for Open Door
	static bool CheckIfDoorIsActive(const int& id);
public:
	virtual void Update(const float& dtAsSeconds, Player& player) override = 0;
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Play sound
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

	void Unload() override;
};