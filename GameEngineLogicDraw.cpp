#include "GameEngineLogic.h"

using namespace sf;

void GameEngineLogic::Draw(RenderWindow& mainWindow)
{

	if (b_PlayerCustomizationSelectorEnabled)
	{
		m_PlayerCustomization.Draw(mainWindow);
		return;
	}

	mainWindow.setView(m_GameView);

	const int amountOfMapLayers = static_cast<int>(m_Map->GetMapLayers().size());
	for (int i = 0; i < amountOfMapLayers; i++) {
		for (TiledMapLoader::MapLayer& mapLayer : m_Map->GetMapLayers())
		{
			if (mapLayer.id == i + 1 && mapLayer.name != "Collision")
			{
				mainWindow.draw(mapLayer.rVa, &m_Map->GetTextureTiles());
			}
		}
	}

	for (const Sprite* sprite : m_Player.GetSprites()) {
		if (sprite->getTexture() != nullptr) {
			mainWindow.draw(*sprite);
		}
	}

}

