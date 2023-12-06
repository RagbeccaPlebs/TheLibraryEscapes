#include "Engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_IsNewMapNeeded) {
		loadMap();
	}

	//TODO SET TO IF TRUE
	if (!m_Playing) {
		m_Player.update(dtAsSeconds);

		m_MainView.setCenter(m_Player.getCenter());

		//Detect collisions
		detectCollisions(m_Player);
	} // End if playing
}