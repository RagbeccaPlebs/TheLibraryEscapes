#include "GamePauseMenu.h"

#include "Constants.h"
#include "Engine.h"

using namespace sf;
using namespace std;

//CONSTRUCTORS
GamePauseMenu::GamePauseMenu(const RenderWindow& mainWindow, const Font& font)
{
	const float screenWidth = static_cast<float>(mainWindow.getSize().x);
	const float screenHeight = static_cast<float>(mainWindow.getSize().y);

	m_GamePauseView.setSize(Vector2f(screenWidth, screenHeight));
	m_GamePauseView.setCenter(screenWidth / 2.f, screenHeight / 2.f);

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f paddingButtons(70.f, 70.f);
	const Vector2f continueButtonLocation((screenWidth / 2.f), screenHeight - (screenHeight / 6.f * 4.f));
	const Vector2f backToMenuButtonLocation((screenWidth / 2.f), screenHeight - (screenHeight / 6.f * 2.5f));
	m_ContinueButton = Button(continueButtonLocation, paddingButtons, font,
		Message::CONTINUE_MESSAGE, 80, idleColor, hoverColor, activeColor, true);
	m_BackToMenuButton = Button(backToMenuButtonLocation, paddingButtons, font,
		Message::EXIT_TO_MENU_MESSAGE, 80, idleColor, hoverColor, activeColor, true);
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

//DESTRUCTORS
void GamePauseMenu::ClearSounds()
{
	//NO SOUNDS YET
}

//DRAW
void GamePauseMenu::Draw(RenderWindow& mainWindow)
{
	RectangleShape screenDarkener;
	const Color darkerColor(0, 0, 0, 127);
	screenDarkener.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	screenDarkener.setFillColor(darkerColor);
	mainWindow.setView(m_GamePauseView);
	mainWindow.draw(screenDarkener);
	m_BackToMenuButton.Draw(mainWindow);
	m_ContinueButton.Draw(mainWindow);
}

//INPUT
void GamePauseMenu::Input(RenderWindow& mainWindow, GameState& gameState, bool& isPausedState, const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		isPausedState = false;
	}

	if (m_ContinueButton.IsPressed())
	{
		isPausedState = false;
	}

	if (m_BackToMenuButton.IsPressed())
	{
		gameState = CHANGED;
	}
}

//UPDATE
void GamePauseMenu::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));
	m_ContinueButton.Update(m_MousePosView, mainWindow);
	m_BackToMenuButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_ContinueButton.Press(m_MousePosView);
		m_BackToMenuButton.Press(m_MousePosView);
	}
}

