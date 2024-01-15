#include "BookInteractable.h"

#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

#include "Constants.h"

using namespace std;
using namespace sf;
using json = nlohmann::json;

pair<string, Vector2f> BookInteractable::Interact()
{
	b_Active = false;

	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	if (m_BookInteractableType == SIMPLE)
	{
		json jsonData;
		jsonData[Keywords::ID_KEYWORD] = m_Id;
		jsonData[Keywords::EMOTION_KEYWORD] = GetStringFromEmotion(m_Emotion);
		data.at(Keywords::BOOK_KEYWORD).push_back(jsonData);
	}

	ofstream fileOut(Files::GAME_DATA_FILE);
	fileOut << data;
	fileOut.flush();

	return pair<string, Vector2f>{GetStringCamelCaseFromEmotion(m_Emotion), Vector2f(0, 0)};
}

BookInteractableType BookInteractable::GetBookInteractableType() const
{
	return m_BookInteractableType;
}

EmotionType BookInteractable::GetEmotion() const
{
	return m_Emotion;
}

bool BookInteractable::GetActive() const
{
	return b_Active;
}

EmotionType BookInteractable::GetEmotionFromString(const string& emotion)
{
	unordered_map<string, EmotionType> const table =
	{ {Constant::SHY_UPPERCASE, SHY}, {Constant::SAD_UPPERCASE, SAD}, {Constant::MAD_UPPERCASE, MAD},
		{Constant::SURPRISED_UPPERCASE, SURPRISED}, {Constant::SECRECY_UPPERCASE, SECRECY} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return SHY;
}

string BookInteractable::GetStringFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table =
	{ {SHY, Constant::SHY_UPPERCASE}, {SAD, Constant::SAD_UPPERCASE},{MAD, Constant::MAD_UPPERCASE},
		{SURPRISED, Constant::SURPRISED_UPPERCASE}, {SECRECY, Constant::SECRECY_UPPERCASE} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return Constant::SHY_UPPERCASE;
}

string BookInteractable::GetStringCamelCaseFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table =
	{ {SHY, Constant::SHY_CAMELCASE}, {SAD, Constant::SAD_CAMELCASE},{MAD, Constant::MAD_CAMELCASE},
		{SURPRISED, Constant::SURPRISED_CAMELCASE}, {SECRECY, Constant::SECRECY_CAMELCASE} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return Constant::SHY_CAMELCASE;
}

