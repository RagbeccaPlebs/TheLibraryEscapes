#include "Interactable.h"

#include <unordered_map>

using namespace sf;
using namespace std;

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

bool Interactable::GetConditionMet() const
{
	return b_ConditionMet;
}

void Interactable::Activate()
{
	b_Active = true;
}

InteractableType Interactable::GetInteractableTypeFromString(const string& interactableType)
{
	unordered_map<string, InteractableType> const table =
	{ {Constant::DOOR_UPPERCASE, DOOR}, {Constant::PICKUP_UPPERCASE, PICKUP},{Constant::PUSH_OBJECT_UPPERCASE, PUSH_OBJECT} };
	const auto it = table.find(interactableType);
	if (it != table.end()) {
		return it->second;
	}
	return PICKUP;
}