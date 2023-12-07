#include "GameEngine.h"

void GameEngine::update(float dtAsSeconds, sf::View* mainView)
{
	m_Player.update(dtAsSeconds);

	//Detect collisions
	detectCollisions(m_Player);

	mainView->setCenter(m_Player.getCenter());
}

