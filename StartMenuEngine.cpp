#include "StartMenuEngine.h"

#include "Constants.h"

using namespace sf;
using namespace std;

StartMenuEngine::StartMenuEngine()
{
	m_StartMenuView.setSize(static_cast<float>(VideoMode::getDesktopMode().width), static_cast<float>(VideoMode::getDesktopMode().height));

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f sizeButtons(300.f, 100.f);
	const float middleWidth = (static_cast<float>(VideoMode::getDesktopMode().width) / 2.0f);
	const float middleHeight = (static_cast<float>(VideoMode::getDesktopMode().height) / 2.0f);
	const Vector2f startButtonLocation((middleWidth - (sizeButtons.x / 2.f)), middleHeight - 150.f);
	const Vector2f exitButtonLocation((middleWidth - (sizeButtons.x / 2.f)), middleHeight + 50.f);
	m_StartButton = Button(startButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::START_MESSAGE, 40, idleColor, hoverColor, activeColor);
	m_ExitButton = Button(exitButtonLocation, sizeButtons, Files::FONT_FILE,
		Message::EXIT_MESSAGE, 40, idleColor, hoverColor, activeColor);
}


