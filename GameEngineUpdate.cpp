#include "GameEngine.h"

void GameEngine::Update(float dtAsSeconds, sf::View* mainView)
{
	m_Player.Update(dtAsSeconds);

	//Detect collisions
	DetectCollisions(m_Player);

	mainView->setCenter(m_Player.GetCenter());
}

