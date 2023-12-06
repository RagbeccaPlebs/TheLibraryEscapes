#include "Map.h"
#include "MapManager.h"
#include "TextureHolder.h"

using namespace sf;
using namespace std;

Map::Map(string name)
{
    m_TexureTiles = TextureHolder::GetTexture("assets/graphics/map/" + name + ".png");
    MapManager::MapValues mapValues = m_MM.mapLoader(m_VACollisionLevel, m_VABackgroundLevelUnder, m_VAInteractableLevel, name);
    m_ArrayCollisionLevel = mapValues.collisionsMap;
    m_ArrayInteractableLevel = mapValues.interactablesMap;
    m_MapSize = mapValues.mapSize;
}

Map::Map(Map& m) {
    m_ArrayCollisionLevel = m.m_ArrayCollisionLevel;
    m_ArrayInteractableLevel = m.m_ArrayInteractableLevel;
}

Map& Map::operator=(const Map& other)
{
    if (this != &other) {
        this->m_ArrayCollisionLevel = other.m_ArrayCollisionLevel;
        this->m_ArrayInteractableLevel = other.m_ArrayInteractableLevel;
        this->m_VABackgroundLevelUnder = other.m_VABackgroundLevelUnder;
        this->m_VABackgroundLevelUpper = other.m_VABackgroundLevelUpper;
        this->m_VACollisionLevel = other.m_VACollisionLevel;
        this->m_VAInteractableLevel = other.m_VAInteractableLevel;
        this->m_TexureTiles = other.m_TexureTiles;
        this->m_MapSize = other.m_MapSize;
    }
    return *this;
}

//Getters
Vector2i Map::getMapSize()
{
    return m_MapSize;
}

VertexArray Map::getVABackgroundLevelUnder()
{
    return m_VABackgroundLevelUnder;
}

VertexArray Map::getVABackgroundLevelUpper()
{
    return m_VABackgroundLevelUpper;
}

int** Map::getArrayCollisionLevel()
{
    return m_ArrayCollisionLevel;
}

VertexArray Map::getVACollisionLevel()
{
    return m_VACollisionLevel;
}

int** Map::getArrayInteractableLevel()
{
    return m_ArrayInteractableLevel;
}

sf::VertexArray Map::getVAInteractableLevel()
{
    return m_VAInteractableLevel;
}

sf::Texture& Map::getTextureTiles()
{
    return m_TexureTiles;
}
