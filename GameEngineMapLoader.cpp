#include "GameEngine.h"

void GameEngine::loadMap()
{
	m_Map = Map("bridge");
	m_Player.spawn(m_Map.getPlayerSpawnLocation("north"));
}
