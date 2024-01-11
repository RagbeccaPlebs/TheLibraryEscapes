#include "Engine.h"

using namespace sf;

void Engine::Input() {

	if (b_Playing)
	{
		m_GameEngine->Input(m_Window, b_Playing, b_EscapePressed);
	}
	else
	{
		m_StartMenuEngine.Input(m_Window, b_Playing, b_EscapePressed);
	}

	if (b_LeftClicked)
	{
		b_LeftClicked = false;
	}

	if (b_EscapePressed)
	{
		b_EscapePressed = false;
	}

	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				b_LeftClicked = true;
			}
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				b_EscapePressed = true;
			}
		}
	}
}
