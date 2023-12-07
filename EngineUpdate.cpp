#include "Engine.h"

using namespace sf;

void Engine::update(const float dtAsSeconds)
{
	if (m_Playing) {
		m_GameEngine.update(dtAsSeconds);

		m_GameEngine.setCenter(m_MainView);
	}
	else
	{
		m_StartMenuEngine.update(dtAsSeconds, m_Window);

		m_MainView.setCenter(m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f);

		printf("Window X: %f, Window Y: %f\n", m_Window.getSize().x, m_Window.getSize().y);
		printf("View X: %f, View Y: %f\n", m_MainView.getCenter().x, m_MainView.getCenter().y);
	}
}