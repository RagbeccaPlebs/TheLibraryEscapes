﻿#include "SimpleBookInteractable.h"

#include "Constants.h"
#include "TextureHolder.h"
#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace std;
using namespace sf;
using json = nlohmann::json;

SimpleBookInteractable::SimpleBookInteractable(const int id, const string& textureFileLocation, Vector2f position, bool isActive)
{
	m_Id = id;
	b_Active = isActive;
	m_InteractableType = PICKUP;
	m_PickupType = BOOK;
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

void SimpleBookInteractable::SavePickupToFile()
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	bool isBookNotFound = true;

	for (auto jsonData : data.at(Keywords::BOOK_KEYWORD))
	{
		if (jsonData.at(Keywords::ID_KEYWORD) == m_Id)  isBookNotFound = false;
	}

	if (!isBookNotFound)
	{
		return;
	}

	json jsonData;
	jsonData[Keywords::ID_KEYWORD] = m_Id;
	data.at(Keywords::BOOK_KEYWORD).push_back(jsonData);

	ofstream fileOut(Files::GAME_DATA_FILE);
	fileOut << data;
	fileOut.flush();
}

void SimpleBookInteractable::Update(const float& dtAsSeconds, Player& player)
{
	//No update atm needed
}

