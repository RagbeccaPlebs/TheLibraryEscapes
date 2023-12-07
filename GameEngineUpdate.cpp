#include "GameEngine.h"

void GameEngine::update(float dtAsSeconds)
{
	m_Player.update(dtAsSeconds);

	//Detect collisions
	detectCollisions(m_Player);
}

void GameEngine::setCenter(sf::View& mainView)
{
	mainView.setCenter(m_Player.getCenter());
}

