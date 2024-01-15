#include "SimpleBookInteractable.h"

#include "Constants.h"
#include "TextureHolder.h"
#include "TiledMapLoader.h"

using namespace std;
using namespace sf;

SimpleBookInteractable::SimpleBookInteractable(const int id, const string& textureFileLocation, Vector2f position, EmotionType emotion)
{
	m_Id = id;
	m_InteractableType = BOOK;
	m_BookInteractableType = SIMPLE;
	m_Emotion = emotion;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - (Constant::STANDARD_TILE_SIZE / 4.0f), position.y - (Constant::STANDARD_TILE_SIZE / 4.0f),
		textureWidth + (Constant::STANDARD_TILE_SIZE/2.f), textureHeight + (Constant::STANDARD_TILE_SIZE / 2.f));
}

void SimpleBookInteractable::Update(float dtAsSeconds)
{
	//No update atm needed
}


