#include "DoorInteractable.h"

#include "TextureHolder.h"
#include "TiledMapLoader.h"

using namespace sf;
using namespace std;

DoorInteractable::DoorInteractable(int id, Vector2f position, const string& mapToMoveTo, Vector2f mapPositionToMoveTo, const string& textureFileLocation, bool isOpen, const string& soundFileLocation)
{
	m_Id = id;
	m_InteractableType = DOOR;
	m_DoorInteractableType = SIMPLE_DOOR;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Sprite.setPosition(m_Position);
	m_MapToMoveToName = mapToMoveTo;
	m_MapToMoveToPosition = mapPositionToMoveTo;
	b_IsOpen = isOpen;
	m_SoundBuffer.loadFromFile(soundFileLocation);
	m_Sound.setBuffer(m_SoundBuffer);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - TiledMapLoader::STANDARD_TILE_SIZE, position.y - TiledMapLoader::STANDARD_TILE_SIZE,
		textureWidth + (TiledMapLoader::STANDARD_TILE_SIZE * 2.f), textureHeight + (TiledMapLoader::STANDARD_TILE_SIZE * 2.f));
}

void DoorInteractable::Update(float dtAsSeconds)
{
	//No animation/update yet
}
