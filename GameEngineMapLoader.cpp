#include "GameEngineLogic.h"

using namespace std;

void GameEngineLogic::LoadMap(const string& mapName)
{
	m_Map = Map(mapName);
	m_PlayerSpawnLocation = m_Map.GetPlayerSpawnLocation("south");
}
