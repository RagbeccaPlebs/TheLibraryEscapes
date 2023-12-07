#include "Map.h"
#include "MapLoader.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Map::Map(string name)
{
    m_TextureTiles = TextureHolder::GetTexture("assets/graphics/map/" + name + ".png");
    const MapLoader::MapValues mapValues = m_MapLoader.mapLoader(m_VaCollisionLevel, m_VaBackgroundLevelUnder, m_VaInteractableLevel, name);
    m_ArrayCollisionLevel = mapValues.collisionsMap;
    m_ArrayInteractableLevel = mapValues.interactablesMap;
    m_MapSize = mapValues.mapSize;
}

Map::Map(Map& m) {
    m_ArrayCollisionLevel = m.m_ArrayCollisionLevel;
    m_ArrayInteractableLevel = m.m_ArrayInteractableLevel;
}

Map::~Map()
{
    this->m_ArrayCollisionLevel = nullptr;
    this->m_ArrayInteractableLevel = nullptr;
}

Map& Map::operator=(const Map& other)
{
    if (this != &other) {
        this->m_ArrayCollisionLevel = other.m_ArrayCollisionLevel;
        this->m_ArrayInteractableLevel = other.m_ArrayInteractableLevel;
        this->m_VaBackgroundLevelUnder = other.m_VaBackgroundLevelUnder;
        this->m_VaBackgroundLevelUpper = other.m_VaBackgroundLevelUpper;
        this->m_VaCollisionLevel = other.m_VaCollisionLevel;
        this->m_VaInteractableLevel = other.m_VaInteractableLevel;
        this->m_TextureTiles = other.m_TextureTiles;
        this->m_MapSize = other.m_MapSize;
    }
    return *this;
}

//Getters
Vector2i Map::getMapSize()
{
    return m_MapSize;
}

VertexArray Map::getVaBackgroundLevelUnder()
{
    return m_VaBackgroundLevelUnder;
}

VertexArray Map::getVaBackgroundLevelUpper()
{
    return m_VaBackgroundLevelUpper;
}

int** Map::getArrayCollisionLevel()
{
    return m_ArrayCollisionLevel;
}

VertexArray Map::getVaCollisionLevel()
{
    return m_VaCollisionLevel;
}

int** Map::getArrayInteractableLevel()
{
    return m_ArrayInteractableLevel;
}

VertexArray Map::getVaInteractableLevel()
{
    return m_VaInteractableLevel;
}

Texture& Map::getTextureTiles()
{
    return m_TextureTiles;
}

Vector2f Map::getPlayerSpawnLocation(string direction)
{
    //TODO Make sure direction is used
    const Vector2f spawnLocation(104.f, 48.f);
    return spawnLocation;
}
