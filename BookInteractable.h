#pragma once

#include <SFML/Graphics.hpp>
#include "PickupInventoryInteractable.h"

//Types in which the Books come in
enum BookInteractableType
{
	SIMPLE
};

//Emotions with their designated colors
enum EmotionType
{
	SHY = 0x4B0082,
	SAD = 0x0047AB,
	MAD = 0x880808,
	SURPRISED = 0xFFB6C1,
	SECRECY = 0x696969
};

//A parent Book interactable that is the base of all Books
class BookInteractable : public PickupInventoryInteractable
{
protected:
	//Set default values
	BookInteractableType m_BookInteractableType = SIMPLE;
	EmotionType m_Emotion = SHY;

	//Virtual Functions to pass along to child classes
	virtual void SavePickupToFile() override = 0;
public:
	//Virtual Functions to pass along to child classes
	virtual void Update(float dtAsSeconds, Player& player) override = 0;

	//Interaction with Interactable
	std::pair<std::string, sf::Vector2f> Interact() override;

	//Getters
	BookInteractableType GetBookInteractableType() const;
	EmotionType GetEmotion() const;

	//Message to be displayed when interacted with
	std::string Message() override;

	//Getters from Emotion to String or other way around
	static EmotionType GetEmotionFromString(const std::string& emotion);
	static std::string GetStringFromEmotion(const EmotionType& emotion);
	static std::string GetStringCamelCaseFromEmotion(const EmotionType& emotion);

	void Unload() override;
};
