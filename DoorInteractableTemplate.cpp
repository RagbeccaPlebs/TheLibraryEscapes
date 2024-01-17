#include "DoorInteractableTemplate.h"

#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

#include "Constants.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

pair<string, Vector2f> DoorInteractableTemplate::Interact()
{
	PlaySound();
	while (m_Sound.getStatus() == SoundSource::Playing)
	{
		sleep(microseconds(1));
	}
	return pair<string, Vector2f>{m_MapToMoveToName, m_MapToMoveToPosition};
}

void DoorInteractableTemplate::PlaySound()
{
	m_Sound.play();
}

bool DoorInteractableTemplate::TryUnlocking()
{
	if (!CheckIfKeyIsFound())
	{
		return false;
	}
	b_IsOpen = true;
	const Texture& texture = TextureHolder::GetTexture(m_TextureLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Sprite.setPosition(m_Position);

	m_SoundBuffer.loadFromFile(m_SoundLocation);
	m_Sound.setBuffer(m_SoundBuffer);

	AddDoorToActiveDoors();
	return true;
}

string DoorInteractableTemplate::Message()
{
	string message;
	message.append(Message::DOOR_LOCKED_MESSAGE_1).append(std::to_string(GetKeyId())).append(Message::DOOR_LOCKED_MESSAGE_2);
	return message;
}

DoorInteractableTemplate::~DoorInteractableTemplate()
{
	m_Sound.resetBuffer();
}

bool DoorInteractableTemplate::GetOpen() const
{
	return b_IsOpen;
}

int DoorInteractableTemplate::GetKeyId() const
{
	return m_KeyId;
}

DoorInteractableType DoorInteractableTemplate::GetDoorInteractableType() const
{
	return m_DoorInteractableType;
}

void DoorInteractableTemplate::AddDoorToActiveDoors() const
{
	const string itemToLoad = Files::GAME_DATA_FILE;
	ifstream file(itemToLoad);
	nlohmann::json data = json::parse(file);
	file.close();

	json jsonData;
	jsonData[Keywords::ID_KEYWORD] = m_Id;
	data.at(Keywords::DOOR_KEYWORD).push_back(jsonData);
	ofstream fileOfStream(itemToLoad);
	fileOfStream << data;
	fileOfStream.flush();
}

bool DoorInteractableTemplate::CheckIfKeyIsFound() const
{
	//If smaller than 0, it should be open, since any minus number means it ís keyless and should be open
	if (m_KeyId == -1)
	{
		return true;
	}
	const string itemToLoad = Files::GAME_DATA_FILE;
	ifstream file(itemToLoad);
	nlohmann::json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(Keywords::KEY_KEYWORD))
	{
		if (idContainer.at(Keywords::ID_KEYWORD) == m_KeyId)
		{
			isSame = true;
		}
	}
	return isSame;
}
