#pragma once
#include <SFML/Graphics.hpp>
#include "TiledMapLoader.h"

class Map
{
	TiledMapLoader m_TiledMapLoader;

	int** m_ArrayCollisionLevel = nullptr;

	std::string m_MapName;
	std::vector<TiledMapLoader::MapLayer> m_MapLayers;

	sf::Vector2i m_MapSize;

	sf::Texture m_TextureTiles;
	std::map<std::string, sf::Vector2f> m_PlayerSpawnLocations;
public:
	Map() = default;
	Map(const std::string& name);
	Map(Map& m);
	~Map();

	Map& operator=(const Map& other);

	sf::Vector2i GetMapSize();
	int** GetArrayCollisionLevel();
	std::string GetMapName();
	std::vector<TiledMapLoader::MapLayer> GetMapLayers();
	sf::Texture& GetTextureTiles();
	sf::Vector2f GetPlayerSpawnLocation(std::string direction);
};
