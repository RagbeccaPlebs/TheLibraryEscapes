#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::Draw()
{
	// Rub out the last frame
	m_Window.clear();

	if (m_Playing)
	{
		m_Window.setView(m_GameView);
		m_GameEngine.Draw(m_Window);
	} else
	{
		m_Window.setView(m_MainView);
		m_StartMenuEngine.Draw(m_Window);
	}

	m_Window.display();
}