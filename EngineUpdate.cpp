#include "Engine.h"

using namespace sf;

void Engine::update(const float dtAsSeconds)
{
	if (m_Playing) {
		m_GameEngine.update(dtAsSeconds);

		m_GameEngine.setCenter(m_MainView);
	} // End if playing
}