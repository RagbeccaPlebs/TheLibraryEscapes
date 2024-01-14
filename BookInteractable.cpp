#include "BookInteractable.h"

#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

#include "Keywords.h"

using namespace std;
using namespace sf;
using json = nlohmann::json;

pair<string, Vector2f> BookInteractable::Interact()
{
	b_Active = false;

	ifstream file(Keywords::FOUND_BOOKS_FILE);
	json data = json::parse(file);
	file.close();

	if (m_BookInteractableType == SIMPLE)
	{
		json jsonData;
		jsonData["id"] = m_Id;
		jsonData["emotion"] = GetStringFromEmotion(m_Emotion);
		data.at(Keywords::SIMPLE_BOOK_KEYWORD).push_back(jsonData);
	}

	ofstream fileOut(Keywords::FOUND_BOOKS_FILE);
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
	{ {"SHY", SHY}, {"SAD", SAD}, {"MAD", MAD}, {"SURPRISED", SURPRISED}, {"SECRECY", SECRECY} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return SHY;
}

string BookInteractable::GetStringFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table = 
	{ {SHY, "SHY"}, {SAD, "SAD"},{MAD, "MAD"}, {SURPRISED, "SURPRISED"}, {SECRECY, "SECRECY"} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return "SHY";
}

string BookInteractable::GetStringCamelCaseFromEmotion(const EmotionType& emotion)
{
	std::unordered_map<EmotionType, string> const table =
	{ {SHY, "Shy"}, {SAD, "Sad"},{MAD, "Mad"}, {SURPRISED, "Surprised"}, {SECRECY, "Secrecy"} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return "Shy";
}

