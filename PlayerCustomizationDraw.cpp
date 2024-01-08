#include "PlayerCustomization.h"

using namespace sf;

void PlayerCustomization::Draw(RenderWindow& mainWindow)
{
	mainWindow.setView(m_ClothesView);

	m_TurnLeftButton.Draw(mainWindow);
	m_TurnRightButton.Draw(mainWindow);
	m_BackToMenuButton.Draw(mainWindow);
	m_ContinueButton.Draw(mainWindow);

	mainWindow.setView(m_PlayerView);

	RectangleShape r(Vector2f(20.f, 20.f));

	r.setPosition(0, 0);
	r.setFillColor(Color::Red);

	mainWindow.draw(r);
	for (const Sprite* sprite : m_Player->GetSprites()) {
		if (sprite->getTexture() != nullptr) {
			mainWindow.draw(*sprite);
		}
	}

	mainWindow.setView(m_ClothesView);
	m_BaseLayerButton.Draw(mainWindow);
	m_LowerLayerButton.Draw(mainWindow);
	m_CloakLayerButton.Draw(mainWindow);
	m_FaceItemLayerButton.Draw(mainWindow);
	m_HairLayerButton.Draw(mainWindow);
	m_HatLayerButton.Draw(mainWindow);
}