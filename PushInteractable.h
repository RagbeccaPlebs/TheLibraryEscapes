#pragma once

#include <SFML/Graphics.hpp>
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
	float CheckForDistance(const sf::Vector2f& playerCenter, const sf::Vector2f& comparisonPosition);
	Side CheckSideWithPositions(const float& topLeft, const float& bottomLeft, const float& topRight, const float& bottomRight);
	float CheckForLeastDistance(std::vector<float> distances);
protected:
	//The type of which the child class is
	PushType m_PushType = RANDOM_PUSH;

	//The file this item is located in
	std::string m_OriginFile;

	//The side the player is on compared to the box
	Side m_SidePlayerIsOn = LEFT;

	//Load file, save new location to file on unload
	void SaveNewLocationToFile();

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
public:
	//Virtual Functions to pass along to child classes
	void Update(float dtAsSeconds, Player& player) override;
	bool CanInteract(Player& player) override;

	//Getters
	PushType GetPushType() const;
	sf::FloatRect GetCollisionBox() const;

	void Unload() override;

	//Destructor to reset sound
	~PushInteractable() override;

	//Play sound
	void PlayPushSound();
	void PlayAlternativeSound();

	static PushType GetPushTypeFromString(const std::string& pushType);
};
