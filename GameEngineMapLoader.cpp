#include "GameEngineLogic.h"

using namespace std;

void GameEngineLogic::LoadMap(const string& mapName)
{
	m_Map = Map(mapName);
	m_Player.Spawn(m_Map.GetPlayerSpawnLocation("south"));
}
