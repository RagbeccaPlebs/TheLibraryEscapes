#include "DoorInteractableTemplate.h"

using namespace sf;
using namespace std;

pair<string, Vector2f> DoorInteractableTemplate::Interact()
{
	PlaySound();
	while(m_Sound.getStatus() == SoundSource::Playing)
	{
		sleep(microseconds(1));
	}
	return pair<string, Vector2f>{m_MapToMoveToName, m_MapToMoveToPosition};
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

bool DoorInteractableTemplate::GetOpen() const
{
	return b_IsOpen;
}

DoorInteractableType DoorInteractableTemplate::GetDoorInteractableType() const
{
	return m_DoorInteractableType;
}
