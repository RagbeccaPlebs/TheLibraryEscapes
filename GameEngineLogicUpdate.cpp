#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Update(float dtAsSeconds, View* mainView)
{
	m_Player.Update(dtAsSeconds);

	//Detect collisions
	DetectCollisions(m_Player);

	mainView->setCenter(m_Player.GetCenter());
}

