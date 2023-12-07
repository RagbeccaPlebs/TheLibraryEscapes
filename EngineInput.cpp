#include "Engine.h"

using namespace sf;

void Engine::input() {

	if (m_Playing)
	{
		m_GameEngine.input(m_Window);
	}
	else
	{
		m_StartMenuEngine.input(m_Window);
	}
}
