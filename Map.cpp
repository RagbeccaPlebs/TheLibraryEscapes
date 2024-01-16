#include "Map.h"
#include "TiledMapLoader.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Map::Map(const string& name)
{
	const TiledMapLoader::MapValues mapValues = m_TiledMapLoader.MapLoader(name);
	m_ArrayCollisionLevel = mapValues.collisionsMap;
	m_MapSize = mapValues.mapSize;
	m_MapLayers = mapValues.mapLayers;
	m_MapName = mapValues.mapName;
	m_TextureTiles = mapValues.texture;
	m_TextureTiles.setSmooth(false);
	m_Interactables = mapValues.interactables;
}

Map::Map(Map& m) {
	m_ArrayCollisionLevel = m.m_ArrayCollisionLevel;
	m_Interactables = m.m_Interactables;
}

Map::~Map()
{
	this->m_ArrayCollisionLevel = nullptr;
	for (auto pointer : m_Interactables)
	{
		delete pointer;
	}
	m_Interactables.clear();
}

Map& Map::operator=(const Map& other)
{
	if (this != &other) {
		this->m_ArrayCollisionLevel = other.m_ArrayCollisionLevel;
		this->m_MapLayers = other.m_MapLayers;
		this->m_MapName = other.m_MapName;
		this->m_TextureTiles = other.m_TextureTiles;
		this->m_MapSize = other.m_MapSize;
		this->m_Interactables = other.m_Interactables;
	}
	return *this;
}

//Getters
Vector2i Map::GetMapSize()
{
	return m_MapSize;
}

int** Map::GetArrayCollisionLevel()
{
	return m_ArrayCollisionLevel;
}

string Map::GetMapName()
{
	return m_MapName;
}

vector<TiledMapLoader::MapLayer> Map::GetMapLayers()
{
	return m_MapLayers;
}

Texture& Map::GetTextureTiles()
{
	return m_TextureTiles;
}

std::vector<Interactable*> Map::GetInteractables()
{
	return m_Interactables;
}
