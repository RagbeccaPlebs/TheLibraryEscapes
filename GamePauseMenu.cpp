#include "GamePauseMenu.h"

#include "Engine.h"

using namespace sf;
using namespace std;

GamePauseMenu::GamePauseMenu(const RenderWindow& mainWindow)
{
	const float screenWidth = static_cast<float>(mainWindow.getSize().x);
	const float screenHeight = static_cast<float>(mainWindow.getSize().y);

	m_GamePauseView.setSize(Vector2f(screenWidth, screenHeight));
	m_GamePauseView.setCenter(screenWidth / 2.f, screenHeight / 2.f);

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f sizeButtons(300.f, 100.f);
	const Vector2f continueButtonLocation(((screenWidth/2.f) - (sizeButtons.x / 2.f)), (screenHeight/2.f) - 100.f);
	const Vector2f backToMenuButtonLocation(((screenWidth / 2.f) - (sizeButtons.x / 2.f)), (screenHeight / 2.f) + 100.f);
	m_ContinueButton = Button(continueButtonLocation, sizeButtons, "assets/fonts/PixelifySans-Regular.ttf",
		"Continue", idleColor, hoverColor, activeColor);
	m_BackToMenuButton = Button(backToMenuButtonLocation, sizeButtons, "assets/fonts/PixelifySans-Regular.ttf",
		"Exit To Menu", idleColor, hoverColor, activeColor);
}

GamePauseMenu& GamePauseMenu::operator=(const GamePauseMenu& gamePauseMenu)
{
	if (this == &gamePauseMenu)
	{
		return *this;
	}
	this->m_ContinueButton = gamePauseMenu.m_ContinueButton;
	this->m_BackToMenuButton = gamePauseMenu.m_BackToMenuButton;
	this->m_GamePauseView = gamePauseMenu.m_GamePauseView;
	return *this;
}

void GamePauseMenu::ClearSounds()
{
	//NO SOUNDS YET
}

