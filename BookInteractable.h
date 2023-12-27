#pragma once

#include <SFML/Graphics.hpp>
#include "Interactable.h"

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

class BookInteractable : public Interactable
{
protected:
	BookInteractableType m_BookInteractableType;
	EmotionType m_Emotion;
	bool m_Active;
public:
	virtual void Update(float dtAsSeconds) = 0;
	std::pair<InteractableType, int> Interact() override;
	bool CanInteract(Player& player) override;
	virtual ~BookInteractable() {}

	BookInteractableType GetBookInteractableType();
	EmotionType GetEmotion();
	bool GetActive();

	static EmotionType GetEmotionFromString(const std::string& emotion);
};
