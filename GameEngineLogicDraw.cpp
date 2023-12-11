#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Draw(RenderWindow& mainWindow)
{
	const int amountOfMapLayers = static_cast<int>(m_Map.GetMapLayers().size());
	for (int i = 0; i < amountOfMapLayers; i++) {
		for (TiledMapLoader::MapLayer& mapLayer : m_Map.GetMapLayers())
		{
			if (mapLayer.id == i + 1 && mapLayer.name != "Collision")
			{
				mainWindow.draw(mapLayer.rVa, &m_Map.GetTextureTiles());
			}
		}
	}

	for (const Sprite& sprite : m_Player.GetSprites()) {
		if (sprite.getTexture() != nullptr) {
			mainWindow.draw(sprite);
		}
	}

	//Temp
	/*RectangleShape rs1;
	RectangleShape rs2;
	RectangleShape rs3;
	RectangleShape rs4;

	rs1.setFillColor(Color::Red);
	rs1.setPosition(Vector2f(m_Player.GetHead().left, m_Player.GetHead().top));
	rs1.setSize(Vector2f(m_Player.GetHead().width, m_Player.GetHead().height));

	rs2.setFillColor(Color::Blue);
	rs2.setPosition(Vector2f(m_Player.GetFeet().left, m_Player.GetFeet().top));
	rs2.setSize(Vector2f(m_Player.GetFeet().width, m_Player.GetFeet().height));

	rs3.setFillColor(Color::Green);
	rs3.setPosition(Vector2f(m_Player.GetLeft().left, m_Player.GetLeft().top));
	rs3.setSize(Vector2f(m_Player.GetLeft().width, m_Player.GetLeft().height));

	rs4.setFillColor(Color::Yellow);
	rs4.setPosition(Vector2f(m_Player.GetRight().left, m_Player.GetRight().top));
	rs4.setSize(Vector2f(m_Player.GetRight().width, m_Player.GetRight().height));

	mainWindow.draw(rs1);
	mainWindow.draw(rs2);
	mainWindow.draw(rs3);
	mainWindow.draw(rs4);*/
}

