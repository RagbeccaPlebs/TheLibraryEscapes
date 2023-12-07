#include "GameEngine.h"

using namespace sf;

void GameEngine::draw(RenderWindow& mainWindow)
{
	if (m_Map.getArrayCollisionLevel() != nullptr) {
		mainWindow.draw(m_Map.getVaBackgroundLevelUnder(), &m_Map.getTextureTiles());
		mainWindow.draw(m_Map.getVaCollisionLevel(), &m_Map.getTextureTiles());
		mainWindow.draw(m_Map.getVaInteractableLevel(), &m_Map.getTextureTiles());
	}

	for (const Sprite& sprite : m_Player.getSprites()) {
		if (sprite.getTexture() != nullptr) {
			mainWindow.draw(sprite);
		}
	}

	//Temp
	RectangleShape rs1;
	RectangleShape rs2;
	RectangleShape rs3;
	RectangleShape rs4;

	rs1.setFillColor(Color::Red);
	rs1.setPosition(Vector2f(m_Player.getHead().left, m_Player.getHead().top));
	rs1.setSize(Vector2f(m_Player.getHead().width, m_Player.getHead().height));

	rs2.setFillColor(Color::Blue);
	rs2.setPosition(Vector2f(m_Player.getFeet().left, m_Player.getFeet().top));
	rs2.setSize(Vector2f(m_Player.getFeet().width, m_Player.getFeet().height));

	rs3.setFillColor(Color::Green);
	rs3.setPosition(Vector2f(m_Player.getLeft().left, m_Player.getLeft().top));
	rs3.setSize(Vector2f(m_Player.getLeft().width, m_Player.getLeft().height));

	rs4.setFillColor(Color::Yellow);
	rs4.setPosition(Vector2f(m_Player.getRight().left, m_Player.getRight().top));
	rs4.setSize(Vector2f(m_Player.getRight().width, m_Player.getRight().height));

	mainWindow.draw(rs1);
	mainWindow.draw(rs2);
	mainWindow.draw(rs3);
	mainWindow.draw(rs4);
}
