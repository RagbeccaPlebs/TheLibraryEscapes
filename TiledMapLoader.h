#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TiledMapLoader
{
	struct MapLayer
	{
		sf::VertexArray rVa;
		int id;
	};
	const std::string FILE_PATH = "assets/map/";

	sf::VertexArray GetVertexArrayFromData(std::vector<int> data);

	MapLayer GetMapLayerFromData(std::vector<int> data, int id);
	
public:

	struct MapValues {
		int** collisionsMap;
		sf::Vector2i mapSize;
		sf::Vector2f startPosition;
		std::string levelName;
		std::vector<MapLayer> mapLayers;
	};

	//Functions
	//Get Map
	MapValues MapLoader(const std::string& name);
};