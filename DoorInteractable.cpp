#include "DoorInteractable.h"

#include "TextureHolder.h"
#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

#include "Constants.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

DoorInteractable::DoorInteractable(int id, Vector2f position, const string& mapToMoveTo, Vector2f mapPositionToMoveTo,
	const string& textureFileLocation, const string& inactiveTextureFileLocation, int keyId, const string& soundFileLocation, const string& inactiveSoundFileLocation)
{
	m_Id = id;
	m_InteractableType = DOOR;
	m_DoorInteractableType = SIMPLE_DOOR;
	b_IsOpen = CheckIfDoorIsActive(id);
	b_Active = true;

	const Texture& texture = TextureHolder::GetTexture(b_IsOpen ? textureFileLocation : inactiveTextureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);

	m_Position = position;
	m_Sprite.setPosition(m_Position);
	m_MapToMoveToName = mapToMoveTo;
	m_MapToMoveToPosition = mapPositionToMoveTo;
	m_SoundBuffer.loadFromFile(b_IsOpen ? soundFileLocation : inactiveSoundFileLocation);
	m_Sound.setBuffer(m_SoundBuffer);
	m_KeyId = keyId;

	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 2.f), position.y - (Constant::STANDARD_TILE_SIZE / 2.f),
		textureWidth + (Constant::STANDARD_TILE_SIZE), textureHeight + (Constant::STANDARD_TILE_SIZE));

	m_TextureLocation = textureFileLocation;
	m_InactiveTextureLocation = inactiveTextureFileLocation;
	m_SoundLocation = soundFileLocation;
	m_InactiveSoundLocation = inactiveSoundFileLocation;
}

void DoorInteractable::Update(float dtAsSeconds)
{
	//No animation/update yet
}

bool DoorInteractable::CheckIfDoorIsActive(const int id) const
{
	const string itemToLoad = Files::GAME_DATA_FILE;
	ifstream file(itemToLoad);
	nlohmann::json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(Keywords::DOOR_KEYWORD))
	{
		if (idContainer.at(Keywords::ID_KEYWORD) == id)
		{
			isSame = true;
		}
	}
	return isSame;
}
