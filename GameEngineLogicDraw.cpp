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
	for (int i = 0; i < amountOfMapLayers; i++)
	{
		for (TiledMapLoader::MapLayer& mapLayer : m_Map->GetMapLayers())
		{
			if (mapLayer.id == i + 1 && mapLayer.name != "Collision")
			{
				mainWindow.draw(mapLayer.rVa, &m_Map->GetTextureTiles());
			}
		}
	}

	DrawInteractable(mainWindow);

	for (const Sprite* sprite : m_Player.GetSprites())
	{
		if (sprite->getTexture() != nullptr) {
			mainWindow.draw(*sprite);
		}
	}

	mainWindow.setView(m_OverlayView);
	if (b_EOverlayActive)
	{
		PressEToInteractOverlay(mainWindow);
	}
}

void GameEngineLogic::DrawInteractable(RenderWindow& mainWindow)
{
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		doorInteractable->Draw(mainWindow);
	}
	for (SimpleBookInteractable* simpleBookInteractable : m_GameMapObjects.simpleBookInteractables)
	{
		if (simpleBookInteractable->GetActive())
		{
			simpleBookInteractable->Draw(mainWindow);
		}

	}
}

void GameEngineLogic::PressEToInteractOverlay(RenderWindow& mainWindow)
{
	RectangleShape shape;
	Text text;
	text.setString("Press E To Interact!");

	Font font;
	font.loadFromFile("assets/fonts/PixelifySans-Regular.ttf");

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(40);
	Vector2f dimension(text.getGlobalBounds().width * 1.25f, text.getGlobalBounds().height * 1.5f);
	Vector2f position(mainWindow.getView().getCenter().x - (dimension.x / 2.f), mainWindow.getView().getCenter().y + (mainWindow.getView().getSize().y / 4.f));
	shape.setSize(dimension);
	shape.setPosition(position);
	const float positionX = ((position.x + (dimension.x / 2.0f)) - (text.getGlobalBounds().width / 2.0f));
	const float positionY = ((position.y + (dimension.y / 2.0f)) - (text.getGlobalBounds().height));
	text.setPosition(positionX, positionY);

	const Color darkerColor(0, 0, 0, 127);
	shape.setFillColor(darkerColor);
	mainWindow.draw(shape);
	mainWindow.draw(text);
}
