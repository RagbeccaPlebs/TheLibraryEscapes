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

FloatRect Interactable::GetInteractionBox() const
{
	return m_InteractionBox;
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
	if (!b_Active) return false;
	return m_InteractionBox.intersects(player.GetInteractableBox());
}

int Interactable::GetId() const
{
	return m_Id;
}

bool Interactable::GetActive() const
{
	return b_Active;
}