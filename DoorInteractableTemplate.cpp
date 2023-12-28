#include "DoorInteractableTemplate.h"

std::pair<InteractableType, int> DoorInteractableTemplate::Interact()
{
    PlaySound();
    //FIX ME
    return std::pair<InteractableType, int>();
}

bool DoorInteractableTemplate::CanInteract(Player& player)
{
    return m_CollisionBox.intersects(player.GetInteractableBox());
}

void DoorInteractableTemplate::PlaySound()
{
    m_Sound.play();
}

bool DoorInteractableTemplate::GetOpen()
{
    return b_IsOpen;
}

DoorInteractableType DoorInteractableTemplate::GetDoorInteractableType()
{
    return m_DoorInteractableType;
}
