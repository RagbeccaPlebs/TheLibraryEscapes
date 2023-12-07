#include "StartMenuEngine.h"

using namespace sf;
using namespace std;

StartMenuEngine::StartMenuEngine()
{
	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	if (!m_Font.loadFromFile("assets/fonts/Roboto-Bold.ttf")) {
		throw "Could not load font!";
	}
	m_StartButton = Button(Vector2f(100.f, 100.f), Vector2f(150.f, 50.f), &m_Font,
		"Start", idleColor, hoverColor, activeColor);
	m_ExitButton = Button(Vector2f(200.f, 200.f), Vector2f(150.f, 50.f), &m_Font,
		"Exit", idleColor, hoverColor, activeColor);
}


