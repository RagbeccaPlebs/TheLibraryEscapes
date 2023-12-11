#include "GamePauseMenu.h"

using namespace sf;

void GamePauseMenu::Draw(RenderWindow& mainWindow, const View& hudView)
{
	RectangleShape screenDarkener;
	const Color darkerColor(0, 0, 0, 127);
	screenDarkener.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	screenDarkener.setFillColor(darkerColor);
	mainWindow.setView(hudView);
	mainWindow.draw(screenDarkener);
	m_BackToMenuButton.Draw(mainWindow);
	m_ContinueButton.Draw(mainWindow);
}


