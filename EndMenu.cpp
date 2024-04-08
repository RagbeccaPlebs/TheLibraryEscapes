#include "EndMenu.h"

#include "Constants.h"
#include "Engine.h"

using namespace sf;
using namespace std;

//CONSTRUCTORS
EndMenu::EndMenu(const RenderWindow& mainWindow, bool isLostMenu, const Font& font)
{
	const float screenWidth = static_cast<float>(mainWindow.getSize().x);
	const float screenHeight = static_cast<float>(mainWindow.getSize().y);

	m_EndView.setSize(Vector2f(screenWidth, screenHeight));
	m_EndView.setCenter(screenWidth / 2.f, screenHeight / 2.f);

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Color idleDarkerColor(0, 0, 0, 50);
	const Vector2f paddingButton(50.f, 50.f);
	const Vector2f paddingTextBox(50.f, 50.f);
	const Vector2f backButtonLocation(((screenWidth / 2.f)), (screenHeight / 2.f) - 50.f);
	const Vector2f textBoxLocation(((screenWidth / 2.f)), (screenHeight / 4.f));
	m_BackButton = Button(backButtonLocation, paddingButton, font,
		Message::EXIT_TO_MENU_MESSAGE, 70, idleColor, hoverColor, activeColor, true);

	if (isLostMenu)
	{
		b_IsLostType = true;
		m_TextBoxButton = Button(textBoxLocation, paddingTextBox, font,
			Message::LOST_MESSAGE, 50, idleDarkerColor, idleDarkerColor, idleDarkerColor, true);
		const Vector2f infoLocation(((screenWidth / 2.f)), (screenHeight / 3.f));
		const string text = "You found " + to_string(0) + " out of " + to_string(GameEngine::GetAmountOfBooksTotal()) + " books";
		m_InfoButton = Button(infoLocation, paddingTextBox, font,
			text, 40, idleDarkerColor, idleDarkerColor, idleDarkerColor, true);
	} else
	{
		m_TextBoxButton = Button(textBoxLocation, paddingTextBox, font,
			Message::WON_MESSAGE, 50, idleDarkerColor, idleDarkerColor, idleDarkerColor, true);

	}
}

EndMenu& EndMenu::operator=(const EndMenu& end)
{
	if (this == &end)
	{
		return *this;
	}
	this->m_BackButton = end.m_BackButton;
	this->m_EndView = end.m_EndView;
	return *this;
}

//DESTRUCTORS
void EndMenu::ClearSounds()
{
	//NO SOUNDS YET
}

//DRAW
void EndMenu::Draw(RenderWindow& mainWindow) const
{
	RectangleShape screenDarkener;
	const Color darkerColor(0, 0, 0, 127);
	screenDarkener.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	screenDarkener.setFillColor(darkerColor);
	mainWindow.setView(m_EndView);
	mainWindow.draw(screenDarkener);
	m_BackButton.Draw(mainWindow);
	m_TextBoxButton.Draw(mainWindow);

	if (b_IsLostType)
	{
		m_InfoButton.Draw(mainWindow);
	}
}

//INPUT
void EndMenu::Input(GameState& gameState, const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		gameState = CHANGED;
	}

	if (m_BackButton.IsPressed())
	{
		gameState = CHANGED;
	}
}

//UPDATE
void EndMenu::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	if (b_IsLostType && b_IsInitialUpdate)
	{
		b_IsInitialUpdate = false;
		m_InfoButton.UpdateText("You found " + to_string(GameEngine::GetAmountOfFoundBooks()) + " out of " + to_string(GameEngine::GetAmountOfBooksTotal()) + " books");
	}

	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));
	m_BackButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_BackButton.Press(m_MousePosView);
	}
}

