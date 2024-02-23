#include "EndMenu.h"

#include "Constants.h"
#include "Engine.h"

using namespace sf;
using namespace std;

//CONSTRUCTORS
EndMenu::EndMenu(const RenderWindow& mainWindow)
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
	m_BackButton = Button(backButtonLocation, paddingButton, Files::FONT_FILE,
		Message::EXIT_TO_MENU_MESSAGE, 70, idleColor, hoverColor, activeColor, true);
	m_TextBoxButton = Button(textBoxLocation, paddingTextBox, Files::FONT_FILE,
		Message::WON_MESSAGE, 50, idleDarkerColor, idleDarkerColor, idleDarkerColor, true);
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
}

//INPUT
void EndMenu::Input(bool& isPlayingState, bool& wasPlaying, const bool& isEscapePressed)
{
	if (isEscapePressed)
	{
		isPlayingState = false;
		wasPlaying = true;
	}

	if (m_BackButton.IsPressed())
	{
		isPlayingState = false;
		wasPlaying = true;
	}
}

//UPDATE
void EndMenu::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));
	m_BackButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_BackButton.Press(m_MousePosView);
	}
}

