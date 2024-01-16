#include "KeyInteractable.h"

#include "nlohmann/json.hpp"
#include <fstream>

#include "Constants.h"
#include "TextureHolder.h"

using namespace std;
using namespace sf;
using json = nlohmann::json;

KeyInteractable::KeyInteractable(const int id, const string& textureFileLocation, Vector2f position)
{
	m_Id = id;
	b_Active = true;
	m_InteractableType = PICKUP;
	m_PickupType = KEY;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 4.0f), position.y - (Constant::STANDARD_TILE_SIZE / 4.0f),
		textureWidth + (Constant::STANDARD_TILE_SIZE / 2.f), textureHeight + (Constant::STANDARD_TILE_SIZE / 2.f));
}

void KeyInteractable::SavePickupToFile()
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	json jsonData;
	jsonData[Keywords::ID_KEYWORD] = m_Id;
	data.at(Keywords::KEY_KEYWORD).push_back(jsonData);

	ofstream fileOut(Files::GAME_DATA_FILE);
	fileOut << data;
	fileOut.flush();
}

void KeyInteractable::Update(float dtAsSeconds)
{
	//No update yet
}

std::pair<std::string, sf::Vector2f> KeyInteractable::Interact()
{
	b_Active = false;

	SavePickupToFile();

	return std::pair<std::string, sf::Vector2f>();
}

std::string KeyInteractable::Message()
{
	string message;
	message.append(Message::KEY_FOUND_MESSAGE_1).append(std::to_string(m_Id)).append(Message::EXCLAMATION_MARK);
	return message;
}
