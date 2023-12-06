#include "MapManager.h"
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;

vector<int> MapManager::getAllValuesFromFileRow(string str) {
	vector<int> values;
	string value;

	istringstream iss(str);

	while (getline(iss, value, ' ')) {
		values.push_back(stoi(value.c_str()));
	}
	return values;
}

Vector2i MapManager::getMapSize()
{
	return m_MapSize;
}

MapManager::MapValues MapManager::mapLoader(VertexArray& rVaCollisions, VertexArray& rVaBackground, VertexArray& rVaInteractables, string name) {
	int** arrayLevelCollisions = singleMapType(rVaCollisions, COLLISIONS, name);
	singleMapType(rVaBackground, BACKGROUND, name); //Ignore values since not interactable
	int** arrayLevelInteractables = singleMapType(rVaInteractables, INTERACTABLES, name);
	MapValues mapValues{};
	mapValues.collisionsMap = arrayLevelCollisions;
	mapValues.interactablesMap = arrayLevelInteractables;
	mapValues.mapSize = m_MapSize;
	return mapValues;
}

int** MapManager::singleMapType(VertexArray& rVA, mapType type, string name) {

	// Load the appropriate level from a text file
	string levelToLoad = "assets/map/";

	switch (type) {
	case COLLISIONS:
		levelToLoad += name + ".txt";
		break;
	case BACKGROUND:
		levelToLoad += name + "-background.txt";
		break;
	case INTERACTABLES:
		levelToLoad += name + "-interactables.txt";
		break;
	}

	ifstream inputFile(levelToLoad);
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
		m_MapSize.x = getAllValuesFromFileRow(s).size();

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
		rowValues = getAllValuesFromFileRow(row);
		for (int x = 0; x < m_MapSize.x; x++) {
			arrayLevel[y][x] = rowValues[x];
		}

		y++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(m_MapSize.x * m_MapSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_MapSize.x; x++)
	{
		for (int y = 0; y < m_MapSize.y; y++)
		{
			// Position each vertex in the current quad
			rVA[static_cast<size_t>(currentVertex) + 0].position =
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVA[static_cast<size_t>(currentVertex) + 1].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVA[static_cast<size_t>(currentVertex) + 2].position =
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVA[static_cast<size_t>(currentVertex) + 3].position =
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVA[static_cast<size_t>(currentVertex) + 0].texCoords =
				Vector2f(0, 0 + verticalOffset);

			rVA[static_cast<size_t>(currentVertex) + 1].texCoords =
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVA[static_cast<size_t>(currentVertex) + 2].texCoords =
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVA[static_cast<size_t>(currentVertex) + 3].texCoords =
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
}