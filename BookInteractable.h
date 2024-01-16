#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.h"
#include "PickupInventoryInteractable.h"

enum BookInteractableType
{
	SIMPLE
};

enum EmotionType
{
	SHY = 0x4B0082,
	SAD = 0x0047AB,
	MAD = 0x880808,
	SURPRISED = 0xFFB6C1,
	SECRECY = 0x696969
};

class BookInteractable : public PickupInventoryInteractable
{
protected:
	//Set default values
	BookInteractableType m_BookInteractableType = SIMPLE;
	EmotionType m_Emotion = SHY;
	virtual void SavePickupToFile() override = 0;
public:
	virtual void Update(float dtAsSeconds) override = 0;
	std::pair<std::string, sf::Vector2f> Interact() override;

	BookInteractableType GetBookInteractableType() const;
	EmotionType GetEmotion() const;

	std::string Message() override;

	static EmotionType GetEmotionFromString(const std::string& emotion);
	static std::string GetStringFromEmotion(const EmotionType& emotion);
	static std::string GetStringCamelCaseFromEmotion(const EmotionType& emotion);
};
