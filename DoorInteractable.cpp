#include "DoorInteractable.h"

#include "TextureHolder.h"
#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"

#include "Constants.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

//CONSTRUCTOR
DoorInteractable::DoorInteractable(int id, Vector2f position, const string& mapToMoveTo, Vector2f mapPositionToMoveTo,
	const string& textureFileLocation, const string& inactiveTextureFileLocation, int keyId,
	const string& soundFileLocation, const string& inactiveSoundFileLocation, bool isActive)
{
	m_Id = id;
	m_InteractableType = DOOR;
	m_DoorInteractableType = SIMPLE_DOOR;
	b_IsOpen = CheckIfDoorIsActive(id);
	b_Active = isActive;

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
	m_InteractionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 2.f), position.y - (Constant::STANDARD_TILE_SIZE / 2.f),
		textureWidth + (Constant::STANDARD_TILE_SIZE), textureHeight + (Constant::STANDARD_TILE_SIZE));

	m_TextureLocation = textureFileLocation;
	m_InactiveTextureLocation = inactiveTextureFileLocation;
	m_SoundLocation = soundFileLocation;
	m_InactiveSoundLocation = inactiveSoundFileLocation;
}

void DoorInteractable::Update(const float& dtAsSeconds, Player& player)
{
	//No animation/update yet
}
