#include "Engine.h"

using namespace sf;

void Engine::loadMap()
{
	m_Map = Map("bridge");
	m_Player.spawn(Vector2f(104.0f, 48.0f));

	m_IsNewMapNeeded = false;
}