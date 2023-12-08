#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MapLoader
{
private:
	enum MapType {
		COLLISIONS,
		BACKGROUND,
		INTERACTABLES
	};
	struct MapTypeValues {
		int** collisionsMap;
		int** interactablesMap;
	};

	sf::Vector2i m_MapSize;
	sf::Vector2f m_StartPosition;
	sf::Vector2i m_CurrentLevel;

	int** SingleMapTypeLoader(sf::VertexArray& rVertexArray, MapLoader::MapType type, const std::string& name);

	std::vector<int> GetAllValuesFromFileRow(std::string& str);
public:
	struct MapValues {
		int** collisionsMap;
		int** interactablesMap;
		sf::Vector2i mapSize;
	};
	static constexpr int TILE_SIZE = 16;
	static constexpr int VERTS_IN_QUAD = 4;

	//Map working 
	sf::Vector2i GetMapSize();

	//Next map 
	MapValues MapTypeLoader(sf::VertexArray& rVaCollisions, sf::VertexArray& rVaBackground, sf::VertexArray& rVaInteractables, const std::string& name);
};