#include "DoorInteractableTemplate.h"

using namespace  sf;

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

DoorInteractableTemplate::~DoorInteractableTemplate()
{
    m_Sound.resetBuffer();
}

bool DoorInteractableTemplate::GetOpen()
{
    return b_IsOpen;
}

DoorInteractableType DoorInteractableTemplate::GetDoorInteractableType()
{
    return m_DoorInteractableType;
}
