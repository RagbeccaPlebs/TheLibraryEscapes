#include "BookInteractable.h"

#include <unordered_map>

#include "TiledMapLoader.h"

#include "Constants.h"

using namespace std;
using namespace sf;

pair<string, Vector2f> BookInteractable::Interact()
{
	b_Active = false;

	SavePickupToFile();

	return pair<string, Vector2f>{Constant::EMPTY_STRING, Vector2f(0, 0)};
}

BookInteractableType BookInteractable::GetBookInteractableType() const
{
	return m_BookInteractableType;
}

EmotionType BookInteractable::GetEmotion() const
{
	return m_Emotion;
}

string BookInteractable::Message()
{
	string message;
	message.append(Message::FOUND_BOOK_MESSAGE_1).append(GetStringCamelCaseFromEmotion(m_Emotion)).append(Message::FOUND_BOOK_MESSAGE_2);
	return message;
}


EmotionType BookInteractable::GetEmotionFromString(const string& emotion)
{
	unordered_map<string, EmotionType> const table =
	{ {Constant::SHY_UPPERCASE, SHY}, {Constant::SAD_UPPERCASE, SAD} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return SHY;
}

string BookInteractable::GetStringFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table =
	{ {SHY, Constant::SHY_UPPERCASE}, {SAD, Constant::SAD_UPPERCASE} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return Constant::SHY_UPPERCASE;
}

string BookInteractable::GetStringCamelCaseFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table =
	{ {SHY, Constant::SHY_CAMELCASE}, {SAD, Constant::SAD_CAMELCASE} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return Constant::SHY_CAMELCASE;
}

void BookInteractable::Unload()
{
	//Nothing to unload like sounds
}

