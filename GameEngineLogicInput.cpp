#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Input(RenderWindow& mainWindow)
{
	m_Player.HandleInput();
}

