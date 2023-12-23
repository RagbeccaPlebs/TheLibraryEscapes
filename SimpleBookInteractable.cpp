#include "SimpleBookInteractable.h"

#include "TextureHolder.h"

using namespace std;
using namespace sf;

SimpleBookInteractable::SimpleBookInteractable(const int id, const string& textureFileLocation, Vector2f position)
{
	m_Id = id;
	m_InteractableType = BOOK;
	m_BookInteractableType = SIMPLE;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_CollisionBox = FloatRect(position.x - (textureWidth / 4.f), position.y - (textureHeight / 4.f), textureWidth * 1.5f, textureHeight * 1.5f);
}

void SimpleBookInteractable::Update(float dtAsSeconds)
{
	//Simple so no update
}


