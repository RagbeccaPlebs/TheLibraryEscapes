#include "Engine.h"

using namespace sf;

void Engine::Update(const float dtAsSeconds)
{
	if (b_Playing)
	{
		m_GameEngine->Update(dtAsSeconds, m_Window, b_LeftClicked);

	}
	else
	{
		m_StartMenuEngine.Update(dtAsSeconds, m_Window, b_LeftClicked);
	}
}