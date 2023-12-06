#pragma once
#include <SFML/Graphics.hpp>
#include "MapManager.h"

class Map {
private:
	MapManager m_MM;

	sf::VertexArray m_VABackgroundLevelUnder;
	sf::VertexArray m_VABackgroundLevelUpper;

	int** m_ArrayCollisionLevel = NULL;
	sf::VertexArray m_VACollisionLevel;

	int** m_ArrayInteractableLevel = NULL;
	sf::VertexArray m_VAInteractableLevel;

	sf::Vector2i m_MapSize;

	sf::Texture m_TexureTiles;
public:
	Map() = default;
	Map(std::string name);
	Map(Map& m);

	Map& operator=(const Map& other);

	sf::Vector2i getMapSize();
	sf::VertexArray getVABackgroundLevelUnder();
	sf::VertexArray getVABackgroundLevelUpper();
	int** getArrayCollisionLevel();
	sf::VertexArray getVACollisionLevel();
	int** getArrayInteractableLevel();
	sf::VertexArray getVAInteractableLevel();
	sf::Texture& getTextureTiles();
};