#include "Engine.h"

using namespace sf;

void Engine::Update(const float dtAsSeconds)
{
	if (b_WasPlaying && !b_Playing)
	{
		b_WasPlaying = false;
		m_GameEngine->ClearEverything();
		sleep(milliseconds(2));
		m_GameEngine = new GameEngine(m_Window);
	}

	if (b_Playing)
	{
		m_GameEngine->Update(dtAsSeconds, m_Window, b_LeftClicked);
	}
	else
	{
		m_StartMenuEngine.Update(dtAsSeconds, m_Window, b_LeftClicked);
	}
}