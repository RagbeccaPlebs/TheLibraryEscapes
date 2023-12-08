#include "GameEngine.h"

void GameEngine::LoadMap()
{
	m_Map = Map("bridge");
	m_Player.Spawn(m_Map.GetPlayerSpawnLocation("north"));
}
