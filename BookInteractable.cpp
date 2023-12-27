#include "BookInteractable.h"

#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace std;
using namespace sf;
using json = nlohmann::json;

pair<InteractableType, int> BookInteractable::Interact()
{
	m_Active = false;

	const string itemToLoad = TiledMapLoader::FOUND_BOOKS_FILE;

	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	if (m_BookInteractableType == SIMPLE)
	{
		json jsonData;
		jsonData["id"] = m_Id;
		data.at(TiledMapLoader::SIMPLE_BOOK_KEYWORD).push_back(jsonData);
	}

	ofstream fileOut(itemToLoad);
	fileOut << data;
	fileOut.flush();

	pair<InteractableType, int> pair(BOOK, m_Id);
	return pair;
}

bool BookInteractable::CanInteract(Player& player)
{
	if (!m_Active) return false;
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
	return m_Active;
}

EmotionType BookInteractable::GetEmotionFromString(const std::string& emotion)
{
	std::unordered_map<std::string, EmotionType> const table =
	{ {"SHY", SHY}, {"SAD", SAD}, {"MAD", MAD}, {"SURPRISED", SURPRISED}, {"SECRECY", SECRECY} };
	auto it = table.find(emotion);
	if (it != table.end()) {
		return it->second;
	}
	return SHY;
}
