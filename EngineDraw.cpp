#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::Draw()
{
	// Clear the last frame
	m_Window.clear();

	//If playing use the Game Engine draw, if not see it asif the start menu is open
	if (b_Playing)
	{
		m_GameEngine->Draw(m_Window);
	}
	else
	{
		m_StartMenuEngine.Draw(m_Window);
	}

	m_Window.display();
}