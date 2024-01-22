#pragma once

#include <SFML/Graphics.hpp>

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
	sf::Vector2f CheckForLeastDistance(sf::FloatRect playerLocation, const sf::Vector2f& comparisonPosition);
	Side CheckSideWithPositions(const sf::Vector2f& topLeft, const sf::Vector2f& bottomLeft, const sf::Vector2f& topRight, const sf::Vector2f& bottomRight);
	sf::Vector2f CheckForLeastDistanceWithSideInMind(std::vector<sf::Vector2f> distances);
protected:
	//The type of which the child class is
	PushType m_PushType = RANDOM_PUSH;

	//The file this item is located in
	std::string m_OriginFile;

	//The side the player is on compared to the box
	Side m_SidePlayerIsOn = LEFT;

	//Load file, save new location to file on unload
	void SaveNewLocationToFile();

	bool b_Movable = true;
public:
	//Virtual Functions to pass along to child classes
	void Update(float dtAsSeconds, Player& player) override;
	virtual std::pair<std::string, sf::Vector2f> Interact() override = 0;
	bool CanInteract(Player& player) override;

	//Getters
	PushType GetPushType() const;

	void Unload() override;

	static PushType GetPushTypeFromString(const std::string& pushType);
};
