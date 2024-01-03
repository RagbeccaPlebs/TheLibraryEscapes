#include "BookInteractable.h"

#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace std;
using namespace sf;
using json = nlohmann::json;

pair<string, Vector2f> BookInteractable::Interact()
{
	b_Active = false;

	const string itemToLoad = TiledMapLoader::FOUND_BOOKS_FILE;

	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	if (m_BookInteractableType == SIMPLE)
	{
		json jsonData;
		jsonData["id"] = m_Id;
		jsonData["emotion"] = GetStringFromEmotion(m_Emotion);
		data.at(TiledMapLoader::SIMPLE_BOOK_KEYWORD).push_back(jsonData);
	}

	ofstream fileOut(itemToLoad);
	fileOut << data;
	fileOut.flush();
	return pair<string, Vector2f>("null", Vector2f(0,0));
}

bool BookInteractable::CanInteract(Player& player)
{
	if (!b_Active) return false;
	return m_CollisionBox.intersects(player.GetInteractableBox());
}

BookInteractableType BookInteractable::GetBookInteractableType()
{
	return m_BookInteractableType;
}

EmotionType BookInteractable::GetEmotion()
{
	return EmotionType();
}

bool BookInteractable::GetActive()
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

string BookInteractable::GetStringFromEmotion(const EmotionType emotion)
{
	std::unordered_map<EmotionType, string> const table = 
	{ {SHY, "SHY"}, {SAD, "SAD"},{MAD, "MAD"}, {SURPRISED, "SURPRISED"}, {SECRECY, "SECRECY"} };
	const auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return "SHY";
}
