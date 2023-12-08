#include "Engine.h"

using namespace sf;

void Engine::Input() {

	if (b_Playing)
	{
		m_GameEngine.Input(m_Window);
	}
	else
	{
		m_StartMenuEngine.Input(m_Window, b_Playing);
	}
}
