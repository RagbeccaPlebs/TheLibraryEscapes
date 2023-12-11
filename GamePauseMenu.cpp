#include "GamePauseMenu.h"

using namespace sf;
using namespace std;

GamePauseMenu::GamePauseMenu()
{
	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f sizeButtons(300.f, 100.f);
	const float middleWidth = (VideoMode::getDesktopMode().width / 2.0f);
	const float middleHeight = (VideoMode::getDesktopMode().height / 2.0f);
	const Vector2f continueButtonLocation((middleWidth - (sizeButtons.x / 2.f)), middleHeight - 100.f);
	const Vector2f backToMenuButtonLocation((middleWidth - (sizeButtons.x / 2.f)), middleHeight + 100.f);
	m_ContinueButton = Button(continueButtonLocation, sizeButtons, "assets/fonts/Roboto-Bold.ttf",
		"Continue", idleColor, hoverColor, activeColor);
	m_BackToMenuButton = Button(backToMenuButtonLocation, sizeButtons, "assets/fonts/Roboto-Bold.ttf",
		"Exit To Menu", idleColor, hoverColor, activeColor);
}


