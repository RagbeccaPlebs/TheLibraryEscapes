#pragma once
#include <SFML/Graphics.hpp>

#include "Interactable.h"
#include "TiledMapLoader.h"

class Map
{
	//The loader for maps
	TiledMapLoader m_TiledMapLoader;
	//Map specific variables
	int** m_ArrayCollisionLevel = nullptr;
	std::string m_MapName;
	std::vector<TiledMapLoader::MapLayer> m_MapLayers;
	sf::Vector2i m_MapSize;
	sf::Texture m_TextureTiles;
	std::vector<Interactable*> m_Interactables;
public:
	//Constructors, destructors and copy assignment operators
	Map() = default;
	Map(const std::string& name);
	Map(Map& m);
	~Map();
	Map& operator=(const Map& other);

	//Getters
	sf::Vector2i GetMapSize();
	int** GetArrayCollisionLevel();
	std::string GetMapName();
	std::vector<TiledMapLoader::MapLayer> GetMapLayers();
	sf::Texture& GetTextureTiles();
	std::vector<Interactable*> GetInteractables();
};
