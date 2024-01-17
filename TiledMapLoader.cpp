#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include "TextureHolder.h"
#include <fstream>

#include "Constants.h"
#include "DoorInteractable.h"
#include "SimpleBookInteractable.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

VertexArray TiledMapLoader::GetVertexArrayFromData(vector<int>& data, Vector2i mapSize, const int TILE_SIZE) const
{
	VertexArray rVa;
	// What type of primitive are we using?
	rVa.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVa.resize(static_cast<size_t>(mapSize.x) * mapSize.y * Constant::VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < mapSize.y; x++)
	{
		for (int y = 0; y < mapSize.x; y++)
		{
			// Position each vertex in the current quad
			rVa[static_cast<size_t>(currentVertex)].position =
				Vector2f(static_cast<float>(y * TILE_SIZE),
					static_cast<float>(x * TILE_SIZE));

			rVa[(currentVertex + 1)].position =
				Vector2f(static_cast<float>((y * TILE_SIZE) + TILE_SIZE),
					static_cast<float>(x * TILE_SIZE));

			rVa[(currentVertex + 2)].position =
				Vector2f(static_cast<float>((y * TILE_SIZE) + TILE_SIZE),
					static_cast<float>((x * TILE_SIZE) + TILE_SIZE));

			rVa[(currentVertex)+3].position =
				Vector2f(static_cast<float>((y * TILE_SIZE)),
					static_cast<float>((x * TILE_SIZE) + TILE_SIZE));

			const int dataIndex = (mapSize.x * x) + y;
			//Adjust with -1 otherwise it will grab the data 1 too far, but only if bigger than 0
			const int correctData = data[dataIndex] > 0 ? data[dataIndex] - 1 : 0;

			// Which tile from the sprite sheet should we use
			const int horizontalOffset = static_cast<int>((correctData * TILE_SIZE) % m_Texture.getSize().x);
			const int verticalOffset = static_cast<int>((correctData * TILE_SIZE) / m_Texture.getSize().x);

			rVa[currentVertex].texCoords =
				Vector2f(static_cast<float>(horizontalOffset), static_cast<float>(TILE_SIZE * verticalOffset));

			rVa[static_cast<size_t>(currentVertex) + 1].texCoords =
				Vector2f(static_cast<float>(TILE_SIZE + horizontalOffset), static_cast<float>(TILE_SIZE * verticalOffset));

			rVa[static_cast<size_t>(currentVertex) + 2].texCoords =
				Vector2f(static_cast<float>(TILE_SIZE + horizontalOffset), static_cast<float>((TILE_SIZE * verticalOffset) + TILE_SIZE));

			rVa[static_cast<size_t>(currentVertex) + 3].texCoords =
				Vector2f(static_cast<float>(horizontalOffset), static_cast<float>((TILE_SIZE * verticalOffset) + TILE_SIZE));

			// Position ready for the next four vertices
			currentVertex += Constant::VERTS_IN_QUAD;
		}
	}
	return rVa;
}

TiledMapLoader::MapLayer TiledMapLoader::GetMapLayerFromData(vector<int>& data, int id, Vector2i mapSize, const int TILE_SIZE, const string& name)
{
	MapLayer mapLayer;
	mapLayer.id = id;
	mapLayer.name = name;
	mapLayer.rVa = GetVertexArrayFromData(data, mapSize, TILE_SIZE);
	return mapLayer;
}

TiledMapLoader::MapValues TiledMapLoader::MapLoader(const std::string& name)
{
	// Load the appropriate level from a text file
	string itemToLoad = Files::MAP_FOLDER;

	itemToLoad += name + Files::JSON_EXTENSION;

	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	int amountOfLayers = data.at(Keywords::LAYERS_KEYWORD).size();
	vector<MapLayer> mapLayers;
	auto** collisionsMap = new int* [1];
	MapValues mapValues;

	m_Texture = TextureHolder::GetTexture(Files::MAP_GRAPHICS_FOLDER + name + Files::PNG_EXTENSION);

	int tileSize = static_cast<int>(data.at(Keywords::TILEWIDTH_KEYWORD));

	for (int layer = 0; layer < amountOfLayers; layer++)
	{
		string layerName = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::NAME_KEYWORD);
		int mapSizeX = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::WIDTH_KEYWORD);
		int mapSizeY = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::HEIGHT_KEYWORD);
		if (layerName.find(Constant::MAP_COLLISION_LEVEL_NAME) != string::npos)
		{
			vector<int> tempData = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::DATA_KEYWORD);
			collisionsMap = new int* [mapSizeY];
			for (int i = 0; i < mapSizeY; ++i)
			{
				collisionsMap[i] = new int[mapSizeX];
			}
			int index = 0;
			for (int y = 0; y < mapSizeY; y++)
			{
				for (int x = 0; x < mapSizeX; x++) {
					collisionsMap[y][x] = tempData.at(index);
					index++;
				}
			}
			mapValues.mapSize = Vector2i(mapSizeX, mapSizeY);
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::ID_KEYWORD),
				mapValues.mapSize, tileSize, layerName));
		}
		else
		{
			vector<int> tempData = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::DATA_KEYWORD);
			auto mapSize = Vector2i(mapSizeX, mapSizeY);
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::ID_KEYWORD),
				mapSize, tileSize, layerName));
		}
	}

	mapValues.collisionsMap = collisionsMap;
	mapValues.mapName = name;
	ranges::sort(mapLayers.begin(), mapLayers.end(), greater<>());
	mapValues.mapLayers = mapLayers;
	mapValues.texture = m_Texture;

	mapValues.interactables = LoadAllInteractables(name);

	return mapValues;
}

vector<Interactable*> TiledMapLoader::LoadAllInteractables(const string& nameOfFile)
{
	vector<Interactable*> interactables;

	string itemToLoad = Files::MAP_DETAILS_FOLDER;
	itemToLoad += nameOfFile + Files::JSON_EXTENSION;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();


	if (data.contains(Keywords::BOOK_KEYWORD)) {
		for (auto dataValue : data.at(Keywords::BOOK_KEYWORD))
		{
			if (!CheckIfSimpleBookIsFound(dataValue.at(Keywords::ID_KEYWORD)))
			{
				interactables.push_back(CreateSimpleBookInteractableFromData(dataValue));
			}

		}
	}
	if (data.contains(Keywords::DOOR_KEYWORD)) {
		for (auto dataValue : data.at(Keywords::DOOR_KEYWORD))
		{
			interactables.push_back(CreateDoorInteractableFromData(dataValue));
		}
	}
	if (data.contains(Keywords::PICKUP_KEYWORD)) {
		for (auto dataValue : data.at(Keywords::PICKUP_KEYWORD))
		{
			switch (PickupInventoryInteractable::GetPickupTypeFromString(dataValue.at(Keywords::TYPE_KEYWORD)))
			{
			case KEY:
				if (CheckIfKeyIsFound(dataValue.at(Keywords::ID_KEYWORD)))
				{
					break;
				}
				interactables.push_back(CreateKeyInteractableFromData(dataValue));
				break;
			case BOOK:
				//Shouldn't be here;
				break;
			}
		}
	}

	return interactables;
}

bool TiledMapLoader::CheckIfSimpleBookIsFound(const int id) const
{
	const string itemToLoad = Files::GAME_DATA_FILE;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(Keywords::BOOK_KEYWORD))
	{
		if (idContainer.at(Keywords::ID_KEYWORD) == id)
		{
			isSame = true;
		}
	}
	return isSame;
}

bool TiledMapLoader::CheckIfKeyIsFound(int id) const
{
	const string itemToLoad = Files::GAME_DATA_FILE;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(Keywords::KEY_KEYWORD))
	{
		if (idContainer.at(Keywords::ID_KEYWORD) == id)
		{
			isSame = true;
		}
	}
	return isSame;
}

KeyInteractable* TiledMapLoader::CreateKeyInteractableFromData(json data)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	return new KeyInteractable(id, textureLocation, Vector2f(x, y));
}

DoorInteractable* TiledMapLoader::CreateDoorInteractableFromData(json data)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const string inactiveTextureLocation = data.at(Keywords::INACTIVE_TEXTURE_KEYWORD);
	const string soundLocation = data.at(Keywords::SOUND_KEYWORD);
	const string inactiveSoundLocation = data.at(Keywords::INACTIVE_SOUND_KEYWORD);
	const int keyId = data.at(Keywords::KEY_ID_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	const string mapToMoveTo = data.at(Keywords::MAP_KEYWORD);
	const float mapX = data.at(Keywords::MAP_X_KEYWORD);
	const float mapY = data.at(Keywords::MAP_Y_KEYWORD);
	return new DoorInteractable(id, Vector2f(x, y), mapToMoveTo, Vector2f(mapX, mapY),
		textureLocation, inactiveTextureLocation, keyId,
		soundLocation, inactiveSoundLocation);
}

SimpleBookInteractable* TiledMapLoader::CreateSimpleBookInteractableFromData(json data)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const string emotionString = data.at(Keywords::EMOTION_KEYWORD);
	const EmotionType emotion = BookInteractable::GetEmotionFromString(emotionString);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	return new SimpleBookInteractable(id, textureLocation, Vector2f(x, y), emotion);
}
