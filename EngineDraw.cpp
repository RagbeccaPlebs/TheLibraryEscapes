#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear();

	m_Window.setView(m_MainView);

	if (m_Playing)
	{
		m_GameEngine.draw(m_Window);
	}

	m_Window.display();
}