#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear();

	if (m_Playing)
	{
		m_Window.setView(m_GameView);
		m_GameEngine.draw(m_Window);
	} else
	{
		m_Window.setView(m_MainView);
		m_StartMenuEngine.draw(m_Window);
	}

	m_Window.display();
}