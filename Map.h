#pragma once
#include <SFML/Graphics.hpp>
#include "MapLoader.h"

class Map {
private:
	MapLoader m_MapLoader;

	sf::VertexArray m_VaBackgroundLevelUnder;
	sf::VertexArray m_VaBackgroundLevelUpper;

	int** m_ArrayCollisionLevel = nullptr;
	sf::VertexArray m_VaCollisionLevel;

	int** m_ArrayInteractableLevel = nullptr;
	sf::VertexArray m_VaInteractableLevel;

	sf::Vector2i m_MapSize;

	sf::Texture m_TextureTiles;
	std::map<std::string, sf::Vector2f> m_PlayerSpawnLocations;
public:
	Map() = default;
	Map(std::string name);
	Map(Map& m);
	~Map();

	Map& operator=(const Map& other);

	sf::Vector2i getMapSize();
	sf::VertexArray getVaBackgroundLevelUnder();
	sf::VertexArray getVaBackgroundLevelUpper();
	int** getArrayCollisionLevel();
	sf::VertexArray getVaCollisionLevel();
	int** getArrayInteractableLevel();
	sf::VertexArray getVaInteractableLevel();
	sf::Texture& getTextureTiles();
	sf::Vector2f getPlayerSpawnLocation(std::string direction);
};