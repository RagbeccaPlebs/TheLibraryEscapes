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
	static std::vector<MapCondition*> LoadAllMapConditions(const std::vector<Interactable*>& interactables, const std::string& nameOfFile);
	//Get the Vertex Array from int vector data
	sf::VertexArray GetVertexArrayFromData(const std::vector<int>& data, sf::Vector2i mapSize, int tileSize) const;
	//Get the Map Layers
	MapLayer GetMapLayerFromData(const std::vector<int>& data, int id, sf::Vector2i mapSize, int tileSize, const std::string& name) const;

	//The texture of the Map
	sf::Texture m_Texture;

	//Creation
	static KeyInteractable* CreateKeyInteractableFromData(const nlohmann::json& data, const bool& isFound);
	static DoorInteractable* CreateDoorInteractableFromData(const nlohmann::json& data);
	static SimpleBookInteractable* CreateSimpleBookInteractableFromData(const nlohmann::json& data, const bool& isFound);

	static LocationPushInteractable* CreateLocationPushInteractableFromData(const nlohmann::json& data, const std::string& fileName);
	static RandomPushInteractable* CreateRandomPushInteractableFromData(const nlohmann::json& data, const std::string& fileName);

	//Checks if objects are found to not load them
	static bool CheckIfSimpleBookIsFound(const int& id);
	static bool CheckIfKeyIsFound(const int& id);

	static Interactable& GetInteractableFromJsonDataAndVector(nlohmann::basic_json<> jsonData, const std::vector<Interactable*>& interactables);

	static Action GetActionFromString(const std::string& action);
};
