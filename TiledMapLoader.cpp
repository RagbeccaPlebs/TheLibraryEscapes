#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace sf;
using namespace std;
using json = nlohmann::json;

sf::VertexArray TiledMapLoader::GetVertexArrayFromData(vector<int> data)
{
	return sf::VertexArray();
}

TiledMapLoader::MapLayer TiledMapLoader::GetMapLayerFromData(vector<int> data, int id)
{
	return MapLayer();
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
	int** collisionsMap;

	for (int layer = 0; layer < amountOfLayers; layer++) 
	{
		string layerName = data.at("layers").at(layer).at("name");
		if (layerName.find("Collision") != string::npos)
		{
			vector<int> tempData = data.at("layers").at(layer).at("data");
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at("layers").at(layer).at("id")));
		} else
		{
			
		}
	}
	
	return MapValues();

	/*ifstream inputFile(levelToLoad);
	string s;
	vector<int> rowValues;

	if (!inputFile) {
		throw "This file isn't there yet.";
	}

	// Count the number of rows in the file
	if (type == COLLISIONS) {
		while (getline(inputFile, s))
		{
			++m_MapSize.y;
		}

		// Store the length of the rows
		m_MapSize.x = GetAllValuesFromFileRow(s).size();

		//Reset file ifstream
		inputFile.clear();
		inputFile.seekg(0, ios::beg);
	}

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int* [m_MapSize.y];
	for (int i = 0; i < m_MapSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_MapSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (getline(inputFile, row)) {
		rowValues = GetAllValuesFromFileRow(row);
		for (int x = 0; x < m_MapSize.x; x++) {
			arrayLevel[y][x] = rowValues[x];
		}

		y++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVertexArray.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVertexArray.resize(m_MapSize.x * m_MapSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_MapSize.x; x++)
	{
		for (int y = 0; y < m_MapSize.y; y++)
		{
			// Position each vertex in the current quad
			rVertexArray[static_cast<size_t>(currentVertex) + 0].position =
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVertexArray[static_cast<size_t>(currentVertex) + 1].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVertexArray[static_cast<size_t>(currentVertex) + 2].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVertexArray[static_cast<size_t>(currentVertex) + 3].position =
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVertexArray[static_cast<size_t>(currentVertex) + 0].texCoords =
				Vector2f(0, 0 + verticalOffset);

			rVertexArray[static_cast<size_t>(currentVertex) + 1].texCoords =
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVertexArray[static_cast<size_t>(currentVertex) + 2].texCoords =
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVertexArray[static_cast<size_t>(currentVertex) + 3].texCoords =
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;*/
}
