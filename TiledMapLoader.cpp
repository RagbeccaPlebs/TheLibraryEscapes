#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include "TextureHolder.h"
#include <fstream>
#include <map>

#include "SimpleBookInteractable.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

VertexArray TiledMapLoader::GetVertexArrayFromData(vector<int>& data, Vector2i mapSize, const int TILE_SIZE)
{
	VertexArray rVa;
	// What type of primitive are we using?
	rVa.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVa.resize(static_cast<size_t>(mapSize.x) * mapSize.y * VERTS_IN_QUAD);

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
			currentVertex += VERTS_IN_QUAD;
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
	string itemToLoad = FILE_PATH;

	itemToLoad += name + ".json";

	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	int amountOfLayers = data.at("layers").size();
	vector<MapLayer> mapLayers;
	auto** collisionsMap = new int* [1];
	MapValues mapValues;

	m_Texture = TextureHolder::GetTexture("assets/graphics/map/" + name + ".png");

	int tileSize = static_cast<int>(data.at("tilewidth"));

	for (int layer = 0; layer < amountOfLayers; layer++)
	{
		string layerName = data.at("layers").at(layer).at("name");
		int mapSizeX = data.at("layers").at(layer).at("width");
		int mapSizeY = data.at("layers").at(layer).at("height");
		if (layerName.find("Collision") != string::npos)
		{
			vector<int> tempData = data.at("layers").at(layer).at("data");
			collisionsMap = new int* [mapSizeY];
			for (int i = 0; i < mapSizeY; ++i)
			{
				// Add a new array into each array element
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
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at("layers").at(layer).at("id"), mapValues.mapSize, tileSize, layerName));
		}
		else
		{
			vector<int> tempData = data.at("layers").at(layer).at("data");
			auto mapSize = Vector2i(mapSizeX, mapSizeY);
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at("layers").at(layer).at("id"), mapSize, tileSize, layerName));
		}
	}

	mapValues.collisionsMap = collisionsMap;
	mapValues.mapName = name;
	// TODO Fix starting pos
	map<string, Vector2f> playerSpawnLocations;
	playerSpawnLocations.insert({ "south", Vector2f(784.f, 920.f) });
	mapValues.playerSpawnLocations = playerSpawnLocations;
	ranges::sort(mapLayers.begin(), mapLayers.end(), greater<>());
	mapValues.mapLayers = mapLayers;
	mapValues.texture = m_Texture;

	mapValues.interactables = LoadAllInteractables(name);

	return mapValues;
}

vector<Interactable*> TiledMapLoader::LoadAllInteractables(const string& nameOfFile)
{
	vector<Interactable*> interactables;

	string itemToLoad = FILE_PATH_DETAILS;
	itemToLoad += nameOfFile + ".json";
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	for (auto dataValue : data.at(SIMPLE_BOOK_KEYWORD))
	{
		const int id = dataValue.at("id");
		if (!CheckIfSimpleBookIsFound(id))
		{
			string textureLocation = dataValue.at("texture");
			const float x = dataValue.at("x");
			const float y = dataValue.at("y");
			interactables.push_back(new SimpleBookInteractable(id, textureLocation, Vector2f(x, y)));
		}

	}

	return interactables;
}

bool TiledMapLoader::CheckIfSimpleBookIsFound(const int id) const
{
	const string itemToLoad = FOUND_BOOKS_FILE;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(SIMPLE_BOOK_KEYWORD))
	{
		if (idContainer.at("id") == id)
		{
			isSame = true;
		}
	}
	return isSame;
}