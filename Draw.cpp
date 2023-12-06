#include "Engine.h"
#include "TextureHolder.h"

using namespace sf;

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear();

	m_Window.setView(m_MainView);

	if (m_Map.getArrayCollisionLevel() != NULL) {
		m_Window.draw(m_Map.getVABackgroundLevel(), &m_Map.getTextureTiles());
		m_Window.draw(m_Map.getVACollisionLevel(), &m_Map.getTextureTiles());
		m_Window.draw(m_Map.getVAInteractableLevel(), &m_Map.getTextureTiles());
	}

	for (Sprite sprite : m_Player.getSprites()) {
		if (sprite.getTexture() != nullptr) {
			m_Window.draw(sprite);
		}
	}

	//Temp
	RectangleShape rs1;
	RectangleShape rs2;
	RectangleShape rs3;
	RectangleShape rs4;
	//RectangleShape block;

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

	m_Window.draw(rs1);
	m_Window.draw(rs2);
	m_Window.draw(rs3);
	m_Window.draw(rs4);

	m_Window.display();
}