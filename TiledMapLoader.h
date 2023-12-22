#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Interactable.h"

class TiledMapLoader
{
public:
	struct MapLayer
	{
		sf::VertexArray rVa;
		int id;
		std::string name;

		bool operator > (const MapLayer& mapLayer) const
		{
			return (id > mapLayer.id);
		}
	};
	struct MapValues {
		int** collisionsMap;
		sf::Vector2i mapSize;
		std::map<std::string, sf::Vector2f> playerSpawnLocations;
		std::string mapName;
		std::vector<MapLayer> mapLayers;
		sf::Texture texture;
		std::vector<Interactable*> interactables;
	};

	static constexpr int STANDARD_TILE_SIZE = 16;

	//Functions
	//Get Map
	MapValues MapLoader(const std::string& name);
private:
	const std::string FILE_PATH = "assets/map/";

	sf::VertexArray GetVertexArrayFromData(std::vector<int>& data, sf::Vector2i mapSize, int TILE_SIZE);

	MapLayer GetMapLayerFromData(std::vector<int>& data, int id, sf::Vector2i mapSize, int TILE_SIZE, const std::string& name);

	static constexpr int VERTS_IN_QUAD = 4;

	sf::Texture m_Texture;
};
