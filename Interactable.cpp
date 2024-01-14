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

FloatRect Interactable::GetCollisionBox() const
{
	return m_CollisionBox;
}

Texture Interactable::GetTexture()
{
	return m_Texture;
}

InteractableType Interactable::GetInteractableType() const
{
	return m_InteractableType;
}

bool Interactable::CanInteract(Player& player)
{
	return m_CollisionBox.intersects(player.GetInteractableBox());
}

int Interactable::GetId() const
{
	return m_Id;
}