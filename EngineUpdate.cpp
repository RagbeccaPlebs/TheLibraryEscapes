#include "Engine.h"

using namespace sf;

void Engine::Update(const float dtAsSeconds)
{
	if (b_Playing) {
		m_GameEngine.Update(dtAsSeconds, &m_GameView, &m_HudView, m_Window);
	}
	else
	{
		m_StartMenuEngine.Update(dtAsSeconds, m_Window);

		m_MainView.setCenter(m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f);
	}
}