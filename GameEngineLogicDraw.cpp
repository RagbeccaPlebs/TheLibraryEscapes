#include "Constants.h"
#include "GameEngineLogic.h"

using namespace sf;
using namespace std;

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
			if (mapLayer.id == i + 1 && mapLayer.name != Constant::MAP_COLLISION_LEVEL_NAME)
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
	if (b_BottomOverlayActive)
	{
		TextOverlay(mainWindow, Message::PRESS_E_TO_INTERACT_MESSAGE, BOTTOM, 40, false);
	}
	if (b_CenterOverlayActive)
	{
		TextOverlay(mainWindow, m_OverlayCenterText, CENTER, 60, true);
	}
}

void GameEngineLogic::DrawInteractable(RenderWindow& mainWindow)
{
	for (DoorInteractable* doorInteractable : m_GameMapObjects.doorInteractables)
	{
		doorInteractable->Draw(mainWindow);
	}
	for (PickupInventoryInteractable* pickupInventoryInteractable : m_GameMapObjects.pickupInventoryInteractables)
	{
		if (pickupInventoryInteractable->GetActive())
		{
			pickupInventoryInteractable->Draw(mainWindow);
		}

	}
}

void GameEngineLogic::TextOverlay(RenderWindow& mainWindow, const string& writtenText, const LOCATION_IN_VIEW locationInView, int fontSize, bool useOpacity)
{
	RectangleShape shape;
	Text text;
	text.setString(writtenText);

	Font font;
	font.loadFromFile(Files::FONT_FILE);

	text.setFont(font);

	if (useOpacity)
	{
		const Color whiteColor(255, 255, 255, m_Opacity);
		const Color darkerColor(0, 0, 0, (m_Opacity/2));
		text.setFillColor(whiteColor);
		shape.setFillColor(darkerColor);
	}
	else
	{
		const Color darkerColor(0, 0, 0, 127);
		text.setFillColor(Color::White);
		shape.setFillColor(darkerColor);
	}

	text.setCharacterSize(fontSize);

	Vector2f dimension;
	Vector2f position;

	switch (locationInView)
	{
	case CENTER:
		dimension = { text.getGlobalBounds().width * 1.25f, text.getGlobalBounds().height * 1.5f };
		position = { mainWindow.getView().getCenter().x - (dimension.x / 2.f), mainWindow.getView().getCenter().y - (dimension.y / 2.f) };
		break;
	case BOTTOM:
		dimension = { text.getGlobalBounds().width * 1.25f, text.getGlobalBounds().height * 1.5f };
		position = { mainWindow.getView().getCenter().x - (dimension.x / 2.f), mainWindow.getView().getCenter().y + (mainWindow.getView().getSize().y / 4.f) };
		break;
	}

	shape.setSize(dimension);
	shape.setPosition(position);
	const float positionX = ((position.x + (dimension.x / 2.0f)) - (text.getGlobalBounds().width / 2.0f));
	const float positionY = ((position.y + (dimension.y / 2.0f)) - (text.getGlobalBounds().height));
	text.setPosition(positionX, positionY);

	mainWindow.draw(shape);
	mainWindow.draw(text);
}
