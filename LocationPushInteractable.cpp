#include "LocationPushInteractable.h"

#include "Constants.h"
#include "TextureHolder.h"

using namespace std;
using namespace sf;

LocationPushInteractable::LocationPushInteractable(const int id, const string& textureFileLocation, const std::string& textureLocationFileLocation,
	const Vector2f position, const Vector2f finalPosition, const string& fileOfOrigin, const float speed,
	const Vector2f minBounds, const Vector2f maxBounds)
{
	m_Id = id;
	b_Active = true;
	m_InteractableType = OBJECT;
	m_PushType = LOCATION_PUSH;
	m_OriginFile = fileOfOrigin;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	const Texture& textureLocation = TextureHolder::GetTexture(textureLocationFileLocation);
	m_TextureFinalLocation = textureLocation;
	m_SpriteFinalLocation = Sprite(m_TextureFinalLocation);
	m_FinalPosition = FloatRect(finalPosition, Vector2f(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height));
	m_Position = position;
	b_Movable = position != finalPosition;
	m_Speed = speed;
	m_Sprite.setPosition(m_Position);
	m_SpriteFinalLocation.setPosition(finalPosition);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_BoundsBox = FloatRect(minBounds, Vector2f(maxBounds.x - minBounds.x, maxBounds.y - minBounds.y));
	m_InteractionBox = FloatRect(position.x - 1.f, position.y - 1.f,
		textureWidth + 2.f, textureHeight + 2.f);
	m_CollisionBox = FloatRect(position.x, position.y, textureWidth, textureHeight);
}

std::pair<std::string, sf::Vector2f> LocationPushInteractable::Interact()
{
	const auto boxPosition = FloatRect(m_Position, Vector2f(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height));
	if (boxPosition == m_FinalPosition)
	{
		if (b_Movable) b_Movable = false;
		return std::pair<std::string, sf::Vector2f>();
	}
	if (CheckIfDistanceIsSmallEnough())
	{
		b_Movable = false;
		m_Position = m_FinalPosition.getPosition();
		m_Sprite.setPosition(m_Position);
		m_CollisionBox = FloatRect(m_Position.x, m_Position.y, m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);;
		return std::pair<std::string, sf::Vector2f>();
	}
	b_Interacting = true;
	return std::pair<std::string, sf::Vector2f>();
}

std::string LocationPushInteractable::Message()
{
	return Constant::EMPTY_STRING;
}

bool LocationPushInteractable::CheckIfDistanceIsSmallEnough() const
{
	const float differenceTop = abs(m_Position.x - m_FinalPosition.left) + abs(m_Position.y - m_FinalPosition.top);
	if (differenceTop > Constant::MAX_DISTANCE_FROM_FINAL_POSITION)
	{
		return false;
	}
	const float differenceBottom = abs(m_Position.x - m_FinalPosition.left) +
		abs((m_Position.y + m_Sprite.getGlobalBounds().height) - (m_FinalPosition.top + m_FinalPosition.height));
	if (differenceBottom > Constant::MAX_DISTANCE_FROM_FINAL_POSITION)
	{
		return false;
	}
	return true;
}

void LocationPushInteractable::Draw(RenderWindow& mainWindow)
{
	mainWindow.draw(m_SpriteFinalLocation);
	mainWindow.draw(m_Sprite);
}
