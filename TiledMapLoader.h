#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "DoorInteractable.h"
#include "Interactable.h"
#include "KeyInteractable.h"
#include "LocationPushInteractable.h"
#include "RandomPushInteractable.h"
#include "SimpleBookInteractable.h"
#include "nlohmann/json.hpp"

class TiledMapLoader
{
public:
	enum Action
	{
		SHOW,
	};
	//A struct for a single condition
	struct Operation
	{
		Interactable* interactable;
		Action action;
	};
	//A struct for conditions that do something on the map
	struct MapCondition
	{
		int id;
		std::vector<Interactable*> conditions;
		std::vector<Operation> operations;
		bool activated;

		MapCondition(int idValue, std::vector<Interactable*> conditionsValue, std::vector<Operation> operationsValue, bool activatedValue);
	};

	//A struct for a layer of the map
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

	//The Map Values coming from a Map
	struct MapValues {
		int** collisionsMap;
		sf::Vector2i mapSize;
		std::map<std::string, sf::Vector2f> playerSpawnLocations;
		std::string mapName;
		std::vector<MapLayer> mapLayers;
		sf::Texture texture;
		std::vector<Interactable*> interactables;
		std::vector<MapCondition*> mapConditions;
	};

	//Get Map
	MapValues MapLoader(const std::string& name);
private:
	//Load interactables from map file
	std::vector<Interactable*> LoadAllInteractables(const std::string& nameOfFile);
	//Load conditions from map file
	std::vector<MapCondition*> LoadAllMapConditions(std::vector<Interactable*> interactables, const std::string& nameOfFile);
	//Get the Vertex Array from int vector data
	sf::VertexArray GetVertexArrayFromData(std::vector<int>& data, sf::Vector2i mapSize, int TILE_SIZE) const;
	//Get the Map Layers
	MapLayer GetMapLayerFromData(std::vector<int>& data, int id, sf::Vector2i mapSize, int TILE_SIZE, const std::string& name);

	//The texture of the Map
	sf::Texture m_Texture;

	//Creation
	KeyInteractable* CreateKeyInteractableFromData(nlohmann::json data, const bool& isFound);
	DoorInteractable* CreateDoorInteractableFromData(nlohmann::json data);
	SimpleBookInteractable* CreateSimpleBookInteractableFromData(nlohmann::json data);

	LocationPushInteractable* CreateLocationPushInteractableFromData(nlohmann::json data, const std::string& fileName);
	RandomPushInteractable* CreateRandomPushInteractableFromData(nlohmann::json data, const std::string& fileName);

	//Checks if objects are found to not load them
	bool CheckIfSimpleBookIsFound(int id) const;
	bool CheckIfKeyIsFound(int id) const;

	Interactable& GetInteractableFromJsonDataAndVector(nlohmann::basic_json<> jsonData, std::vector<Interactable*> interactables);

	static Action GetActionFromString(const std::string& action);
};
