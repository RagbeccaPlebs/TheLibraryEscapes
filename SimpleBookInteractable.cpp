#include "SimpleBookInteractable.h"

#include "Constants.h"
#include "TextureHolder.h"
#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace std;
using namespace sf;
using json = nlohmann::json;

void SimpleBookInteractable::SavePickupToFile()
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	json jsonData;
	jsonData[Keywords::ID_KEYWORD] = m_Id;
	jsonData[Keywords::EMOTION_KEYWORD] = GetStringFromEmotion(m_Emotion);
	data.at(Keywords::BOOK_KEYWORD).push_back(jsonData);

	ofstream fileOut(Files::GAME_DATA_FILE);
	fileOut << data;
	fileOut.flush();
}

SimpleBookInteractable::SimpleBookInteractable(const int id, const string& textureFileLocation, Vector2f position, EmotionType emotion)
{
	m_Id = id;
	b_Active = true;
	m_InteractableType = PICKUP;
	m_PickupType = BOOK;
	m_BookInteractableType = SIMPLE;
	m_Emotion = emotion;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_InteractionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 4.0f), position.y - (Constant::STANDARD_TILE_SIZE / 4.0f),
		textureWidth + (Constant::STANDARD_TILE_SIZE / 2.f), textureHeight + (Constant::STANDARD_TILE_SIZE / 2.f));
}

void SimpleBookInteractable::Update(float dtAsSeconds, Player& player)
{
	//No update atm needed
}

