#include "LocationPushInteractable.h"

#include "Constants.h"
#include "TextureHolder.h"

using namespace std;
using namespace sf;

LocationPushInteractable::LocationPushInteractable(const int id, const string& textureFileLocation, Vector2f position, Vector2f finalPosition, const string& fileOfOrigin)
{
	m_Id = id;
	b_Active = true;
	m_InteractableType = PICKUP;
	m_PushType = LOCATION_PUSH;
	m_OriginFile = fileOfOrigin;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_FinalPosition = RectangleShape(Vector2f(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)));
	m_FinalPosition.setPosition(finalPosition);
	m_Position = position;
	b_Movable = position == finalPosition;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 4.0f), position.y - (Constant::STANDARD_TILE_SIZE / 4.0f),
		textureWidth + (Constant::STANDARD_TILE_SIZE / 2.f), textureHeight + (Constant::STANDARD_TILE_SIZE / 2.f));
}

std::pair<std::string, sf::Vector2f> LocationPushInteractable::Interact()
{
	return std::pair<std::string, sf::Vector2f>();
}

std::string LocationPushInteractable::Message()
{
	return Constant::EMPTY_STRING;
}
