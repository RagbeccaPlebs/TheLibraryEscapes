#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MapManager
{
private:
	enum mapType {
		COLLISIONS,
		BACKGROUND,
		INTERACTABLES
	};

	sf::Vector2i m_MapSize;
	sf::Vector2f m_StartPosition;
	sf::Vector2i m_CurrentLevel;

	int** singleMapType(sf::VertexArray& rVA, MapManager::mapType type, std::string name);

	std::vector<int> getAllValuesFromFileRow(std::string str);
public:
	struct MapValues {
		int** collisionsMap;
		int** interactablesMap;
		sf::Vector2i mapSize;
	};
	static const int TILE_SIZE = 16;
	static const int VERTS_IN_QUAD = 4;

	//Map working 
	sf::Vector2i getMapSize();

	//Next map 
	MapValues mapLoader(sf::VertexArray& rVaCollisions, sf::VertexArray& rVaBackground, sf::VertexArray& rVaInteractables, std::string name);
};