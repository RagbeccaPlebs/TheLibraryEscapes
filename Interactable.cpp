#include "Interactable.h"

using namespace sf;

void Interactable::Draw(RenderWindow& mainWindow)
{
	mainWindow.draw(m_Sprite);
}

Sprite Interactable::GetSprite()
{
	return m_Sprite;
}

FloatRect Interactable::GetCollisionBox()
{
	return m_CollisionBox;
}

Texture Interactable::GetTexture()
{
	return m_Texture;
}

InteractableType Interactable::GetInteractableType()
{
	return m_InteractableType;
}


int Interactable::GetId() const
{
	return m_Id;
}