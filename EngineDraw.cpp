#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::Draw()
{
	// Rub out the last frame
	m_Window.clear();

	if (b_Playing)
	{
		m_GameEngine->Draw(m_Window);
	} else
	{
		m_StartMenuEngine.Draw(m_Window);
	}

	m_Window.display();
}