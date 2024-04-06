#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Constants.h"
#include "Interactable.h"

//Types in which the Pickups come in
enum PushType
{
	LOCATION_PUSH,
	RANDOM_PUSH
};

//A parent Pickup interactable that is the base of all Pickups which go to the virtual 
class PushInteractable : public Interactable
{
public:
	//Virtual Functions to pass along to child classes
	void Update(const float& dtAsSeconds, Player& player) override;
	bool CanInteract(Player& player) override;

	//Getters
	PushType GetPushType() const;
	sf::FloatRect GetCollisionBox() const;

	void Unload() override;

	//Destructor to reset sound
	~PushInteractable() override;

	//Sound interaction
	void PlayPushSound();
	void StopPushSound();
	void PlaySoundOfNotPlaying();
	sf::SoundSource::Status GetPushSoundStatus() const;
	void PlayAlternativeSound();

	static PushType GetPushTypeFromString(const std::string& pushType);
protected:
	//The type of which the child class is
	PushType m_PushType = RANDOM_PUSH;

	//The file this item is located in
	std::string m_OriginFile;

	//The side the player is on compared to the box
	Side m_SidePlayerIsOn = LEFT;

	//Load file, save new location to file on unload
	void SaveNewLocationToFile() const;

	sf::FloatRect m_CollisionBox;
	//The place the interactable is allowed to move in
	sf::FloatRect m_BoundsBox;

	bool b_Movable = true;
	bool b_Interacting = false;
	float m_Speed = Constant::PLAYER_WALK_SPEED;

	//Push Interactable specific Values for Graphical and Sound Gameplay
	sf::SoundBuffer m_SoundBuffer;
	sf::SoundBuffer m_PushSoundBuffer;
	sf::Sound m_Sound;
	sf::Sound m_PushSound;
	std::string m_SoundLocation;
	std::string m_PushSoundLocation;

	//Push check
	bool b_BeingPushed = false;
	bool b_WasBeingPushed = false;
private:
	static float CheckForDistance(const sf::Vector2f& playerCenter, const sf::Vector2f& comparisonPosition);
	static Side CheckSideWithPositions(const float& topLeft, const float& bottomLeft, const float& topRight, const float& bottomRight);
	static float CheckForLeastDistance(std::vector<float> distances);
};
