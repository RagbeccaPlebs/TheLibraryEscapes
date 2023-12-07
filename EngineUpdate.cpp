#include "Engine.h"

using namespace sf;

void Engine::update(const float dtAsSeconds)
{
	if (m_Playing) {
		m_GameEngine.update(dtAsSeconds, &m_GameView);
	}
	else
	{
		m_StartMenuEngine.update(dtAsSeconds, m_Window);

		m_MainView.setCenter(m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f);
	}
}