#include "TiledMapLoader.h"
#include "nlohmann/json.hpp"
#include "TextureHolder.h"
#include <fstream>

#include "Constants.h"
#include "RandomPushInteractable.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

VertexArray TiledMapLoader::GetVertexArrayFromData(const vector<int>& data, const Vector2i mapSize, const int tileSize) const
{
	VertexArray rVa;
	// What type of primitive are we using?
	rVa.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVa.resize(static_cast<size_t>(mapSize.x) * mapSize.y * Constant::VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < mapSize.y; x++)
	{
		for (int y = 0; y < mapSize.x; y++)
		{
			const int dataIndex = (mapSize.x * x) + y;
			//Adjust with -1 otherwise it will grab the data 1 too far, but only if bigger than 0
			const int correctData = data[dataIndex] > 0 ? data[dataIndex] - 1 : 0;

			// Which tile from the sprite sheet should we use
			const int horizontalOffset = static_cast<int>((correctData * tileSize) % m_Texture.getSize().x);
			const int verticalOffset = static_cast<int>((correctData * tileSize) / m_Texture.getSize().x);

			if (horizontalOffset == 0 && verticalOffset == 0)
			{
				continue;
			}

			// Position each vertex in the current quad
			rVa[static_cast<size_t>(currentVertex)].position =
				Vector2f(static_cast<float>(y * tileSize),
					static_cast<float>(x * tileSize));

			rVa[(currentVertex + 1)].position =
				Vector2f(static_cast<float>((y * tileSize) + tileSize),
					static_cast<float>(x * tileSize));

			rVa[(currentVertex + 2)].position =
				Vector2f(static_cast<float>((y * tileSize) + tileSize),
					static_cast<float>((x * tileSize) + tileSize));

			rVa[(currentVertex)+3].position =
				Vector2f(static_cast<float>((y * tileSize)),
					static_cast<float>((x * tileSize) + tileSize));

			rVa[currentVertex].texCoords =
				Vector2f(static_cast<float>(horizontalOffset), static_cast<float>(tileSize * verticalOffset));

			rVa[static_cast<size_t>(currentVertex) + 1].texCoords =
				Vector2f(static_cast<float>(tileSize + horizontalOffset), static_cast<float>(tileSize * verticalOffset));

			rVa[static_cast<size_t>(currentVertex) + 2].texCoords =
				Vector2f(static_cast<float>(tileSize + horizontalOffset), static_cast<float>((tileSize * verticalOffset) + tileSize));

			rVa[static_cast<size_t>(currentVertex) + 3].texCoords =
				Vector2f(static_cast<float>(horizontalOffset), static_cast<float>((tileSize * verticalOffset) + tileSize));

			// Position ready for the next four vertices
			currentVertex += Constant::VERTS_IN_QUAD;
		}
	}
	if (currentVertex > 0)
	{
		rVa.resize(currentVertex);
	}
	return rVa;
}

TiledMapLoader::MapLayer TiledMapLoader::GetMapLayerFromData(const vector<int>& data, const int id, const Vector2i mapSize, const int tileSize, const string& name) const
{
	MapLayer mapLayer;
	mapLayer.id = id;
	mapLayer.name = name;
	mapLayer.rVa = GetVertexArrayFromData(data, mapSize, tileSize);
	return mapLayer;
}

TiledMapLoader::MapValues TiledMapLoader::MapLoader(const std::string& name)
{
	// Load the appropriate level from a text file
	string itemToLoad = Files::MAP_FOLDER;

	itemToLoad += name + Files::DOT_JSON_EXTENSION;

	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	int amountOfLayers = static_cast<int>(data.at(Keywords::LAYERS_KEYWORD).size());
	vector<MapLayer> mapLayers;
	auto** collisionsMap = new int* [1];
	MapValues mapValues;

	m_Texture = TextureHolder::GetTexture(Files::MAP_GRAPHICS_FOLDER + name + Files::DOT_PNG_EXTENSION);

	int tileSize = data.at(Keywords::TILEWIDTH_KEYWORD);

	for (int layer = 0; layer < amountOfLayers; layer++)
	{
		string layerName = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::NAME_KEYWORD);
		int mapSizeX = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::WIDTH_KEYWORD);
		int mapSizeY = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::HEIGHT_KEYWORD);
		if (layerName.find(Constant::MAP_COLLISION_LEVEL_NAME) != string::npos)
		{
			vector<int> tempData = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::DATA_KEYWORD);
			collisionsMap = new int* [mapSizeY];
			for (int i = 0; i < mapSizeY; ++i)
			{
				collisionsMap[i] = new int[mapSizeX];
			}
			int index = 0;
			for (int y = 0; y < mapSizeY; y++)
			{
				for (int x = 0; x < mapSizeX; x++) {
					collisionsMap[y][x] = tempData.at(index);
					index++;
				}
			}
			mapValues.mapSize = Vector2i(mapSizeX, mapSizeY);
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::ID_KEYWORD),
				mapValues.mapSize, tileSize, layerName));
		}
		else
		{
			vector<int> tempData = data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::DATA_KEYWORD);
			auto mapSize = Vector2i(mapSizeX, mapSizeY);
			mapLayers.push_back(GetMapLayerFromData(tempData, data.at(Keywords::LAYERS_KEYWORD).at(layer).at(Keywords::ID_KEYWORD),
				mapSize, tileSize, layerName));
		}
	}

	mapValues.collisionsMap = collisionsMap;
	mapValues.mapName = name;
	ranges::sort(mapLayers.begin(), mapLayers.end(), greater<>());
	mapValues.mapLayers = mapLayers;
	mapValues.texture = m_Texture;
	mapValues.tileSize = tileSize;

	mapValues.interactables = LoadAllInteractables(name);
	mapValues.mapConditions = LoadAllMapConditions(mapValues.interactables, name);

	return mapValues;
}

vector<Interactable*> TiledMapLoader::LoadAllInteractables(const string& nameOfFile)
{
	vector<Interactable*> interactables;

	string itemToLoad = Files::MAP_DETAILS_FOLDER;
	itemToLoad += nameOfFile + Files::DOT_JSON_EXTENSION;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();


	if (data.contains(Keywords::BOOK_KEYWORD)) {
		ifstream booksFile(Files::BOOKS_DATA_FILE);
		json booksFileValues = json::parse(booksFile);
		booksFile.close();
		for (const auto& dataValue : data.at(Keywords::BOOK_KEYWORD))
		{
			if (CheckIfThingIsFoundById(dataValue.at(Keywords::ID_KEYWORD), Keywords::BOOK_KEYWORD))
			{
				interactables.push_back(CreateSimpleBookInteractableFromData(dataValue, true, booksFileValues));
			}
			else
			{
				interactables.push_back(CreateSimpleBookInteractableFromData(dataValue, false, booksFileValues));
			}

		}
	}
	if (data.contains(Keywords::DOOR_KEYWORD)) {
		for (const auto& dataValue : data.at(Keywords::DOOR_KEYWORD))
		{
			interactables.push_back(CreateDoorInteractableFromData(dataValue));
		}
	}
	if (data.contains(Keywords::PICKUP_KEYWORD)) {
		for (const auto& dataValue : data.at(Keywords::PICKUP_KEYWORD))
		{
			switch (PickupInventoryInteractable::GetPickupTypeFromString(dataValue.at(Keywords::TYPE_KEYWORD)))
			{
			case KEY:
				if (CheckIfThingIsFoundById(dataValue.at(Keywords::ID_KEYWORD), Keywords::KEY_KEYWORD))
				{
					interactables.push_back(CreateKeyInteractableFromData(dataValue, true));
				}
				else
				{
					interactables.push_back(CreateKeyInteractableFromData(dataValue, false));
				}
				break;
			case BOOK:
				//Shouldn't be here;
				break;
			}
		}
	}
	if (data.contains(Keywords::PUSHABLE_OBJECT_KEYWORD))
	{
		for (const auto& dataValue : data.at(Keywords::PUSHABLE_OBJECT_KEYWORD))
		{
			switch (PushInteractable::GetPushTypeFromString(dataValue.at(Keywords::TYPE_KEYWORD)))
			{
			case RANDOM_PUSH:
				interactables.push_back(CreateRandomPushInteractableFromData(dataValue, itemToLoad));
				break;
			case LOCATION_PUSH:
				interactables.push_back(CreateLocationPushInteractableFromData(dataValue, itemToLoad));
				break;
			}
		}
	}

	return interactables;
}

bool TiledMapLoader::CheckIfThingIsFoundById(const int& id, const string& keyword)
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	bool isSame = false;

	for (auto& idContainer : data.at(keyword))
	{
		if (idContainer.at(Keywords::ID_KEYWORD) == id)
		{
			isSame = true;
		}
	}
	return isSame;
}

KeyInteractable* TiledMapLoader::CreateKeyInteractableFromData(const json& data, const bool& isFound)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	bool active = true;
	if (data.contains(Keywords::ACTIVATED_KEYWORD))
	{
		active = data.at(Keywords::ACTIVATED_KEYWORD);
	}
	if (isFound)
	{
		active = false;
	}
	return new KeyInteractable(id, textureLocation, Vector2f(x, y), active);
}

DoorInteractable* TiledMapLoader::CreateDoorInteractableFromData(const json& data)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const int templateId = data.at(Keywords::TEMPLATE_ID_KEYWORD);
	ifstream file(Files::DOORS_DATA_FILE);
	json doorsFileData = json::parse(file);
	file.close();
	const int keyId = data.at(Keywords::KEY_ID_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	const string mapToMoveTo = data.at(Keywords::MAP_KEYWORD);
	const float mapX = data.at(Keywords::MAP_X_KEYWORD);
	const float mapY = data.at(Keywords::MAP_Y_KEYWORD);
	bool active = true;
	if (data.contains(Keywords::ACTIVATED_KEYWORD))
	{
		active = data.at(Keywords::ACTIVATED_KEYWORD);
	}
	for (auto& doorTemplate : doorsFileData.at(Keywords::DOOR_KEYWORD))
	{
		if (doorTemplate.at(Keywords::ID_KEYWORD) == templateId)
		{
			const string textureLocation = doorTemplate.at(Keywords::TEXTURE_KEYWORD);
			const string inactiveTextureLocation = doorTemplate.at(Keywords::INACTIVE_TEXTURE_KEYWORD);
			const string soundLocation = doorTemplate.at(Keywords::SOUND_KEYWORD);
			const string inactiveSoundLocation = doorTemplate.at(Keywords::INACTIVE_SOUND_KEYWORD);
			return new DoorInteractable(id, Vector2f(x, y), mapToMoveTo, Vector2f(mapX, mapY),
				textureLocation, inactiveTextureLocation, keyId,
				soundLocation, inactiveSoundLocation, active);
		}
	}
	const string exceptionMessage = "You used the templateId: " + std::to_string(templateId) + " which isn't implemented!";
	throw exception(exceptionMessage.c_str());
}

SimpleBookInteractable* TiledMapLoader::CreateSimpleBookInteractableFromData(const json& data, const bool& isFound, const json& booksFile)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	bool active = true;
	if (data.contains(Keywords::ACTIVATED_KEYWORD))
	{
		active = data.at(Keywords::ACTIVATED_KEYWORD);
	}
	if (isFound)
	{
		active = false;
	}

	//Get values from the books file
	for (const json& dataValue : booksFile.at(Keywords::BOOK_KEYWORD))
	{
		if (dataValue.at(Keywords::ID_KEYWORD) == id)
		{
			const string textureLocation = dataValue.at(Keywords::TEXTURE_KEYWORD);
			return new SimpleBookInteractable(id, textureLocation, Vector2f(x, y), active);
		}
	}

	throw exception("For some reason you didn't implement the book correctly!");
}

LocationPushInteractable* TiledMapLoader::CreateLocationPushInteractableFromData(const json& data, const string& fileName)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const string textureLocationForFinalLocation = data.at(Keywords::TEXTURE_LOCATION_KEYWORD);
	const string soundLocation = data.at(Keywords::SOUND_KEYWORD);
	const string pushSoundLocation = data.at(Keywords::PUSH_SOUND_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	const float mapX = data.at(Keywords::MAP_X_KEYWORD);
	const float mapY = data.at(Keywords::MAP_Y_KEYWORD);
	const float speed = data.at(Keywords::MOVABLE_SPEED_KEYWORD);
	const auto minBounds = Vector2f(data.at(Keywords::MIN_X_KEYWORD), data.at(Keywords::MIN_Y_KEYWORD));
	const auto maxBounds = Vector2f(data.at(Keywords::MAX_X_KEYWORD), data.at(Keywords::MAX_Y_KEYWORD));
	bool active = true;
	if (data.contains(Keywords::ACTIVATED_KEYWORD))
	{
		active = data.at(Keywords::ACTIVATED_KEYWORD);
	}
	return new LocationPushInteractable(id, textureLocation, textureLocationForFinalLocation,
		Vector2f(x, y), Vector2f(mapX, mapY), fileName, speed, minBounds, maxBounds, soundLocation, pushSoundLocation, active);
}

RandomPushInteractable* TiledMapLoader::CreateRandomPushInteractableFromData(const json& data, const string& fileName)
{
	const int id = data.at(Keywords::ID_KEYWORD);
	const string textureLocation = data.at(Keywords::TEXTURE_KEYWORD);
	const string soundLocation = data.at(Keywords::SOUND_KEYWORD);
	const string pushSoundLocation = data.at(Keywords::PUSH_SOUND_KEYWORD);
	const float x = data.at(Keywords::X_KEYWORD);
	const float y = data.at(Keywords::Y_KEYWORD);
	const float speed = data.at(Keywords::MOVABLE_SPEED_KEYWORD);
	const auto minBounds = Vector2f(data.at(Keywords::MIN_X_KEYWORD), data.at(Keywords::MIN_Y_KEYWORD));
	const auto maxBounds = Vector2f(data.at(Keywords::MAX_X_KEYWORD), data.at(Keywords::MAX_Y_KEYWORD));
	bool active = true;
	if (data.contains(Keywords::ACTIVATED_KEYWORD))
	{
		active = data.at(Keywords::ACTIVATED_KEYWORD);
	}
	return new RandomPushInteractable(id, textureLocation, Vector2f(x, y), fileName, speed, minBounds,
		maxBounds, soundLocation, pushSoundLocation, active);
}

//Conditions
vector<TiledMapLoader::MapCondition*> TiledMapLoader::LoadAllMapConditions(const vector<Interactable*>& interactables, const std::string& nameOfFile)
{
	vector<MapCondition*> mapConditions;

	string itemToLoad = Files::MAP_DETAILS_FOLDER;
	itemToLoad += nameOfFile + Files::DOT_JSON_EXTENSION;
	ifstream file(itemToLoad);
	json data = json::parse(file);
	file.close();

	if (data.contains(Keywords::CONDITIONS_KEYWORD))
	{
		for (const auto& condition : data.at(Keywords::CONDITIONS_KEYWORD))
		{
			const int id = condition.at(Keywords::ID_KEYWORD);
			vector<Operation> operationsVector;
			for (const auto& operations : condition.at(Keywords::OPERATIONS_KEYWORD))
			{
				const Action action = GetActionFromString(operations.at(Keywords::OPERATION_KEYWORD));
				Interactable& interactable = GetInteractableFromJsonDataAndVector(operations, interactables);
				Operation operation{ &interactable, action };
				operationsVector.push_back(operation);
			}
			vector<Interactable*> conditionsVector;
			for (const auto& nestedCondition : condition.at(Keywords::CONDITIONS_KEYWORD))
			{
				Interactable& interactable = GetInteractableFromJsonDataAndVector(nestedCondition, interactables);
				conditionsVector.push_back(&interactable);
			}
			MapCondition* mapCondition = new MapCondition(id, conditionsVector, operationsVector, false);
			mapConditions.push_back(mapCondition);
		}
	}

	return mapConditions;
}

Interactable& TiledMapLoader::GetInteractableFromJsonDataAndVector(nlohmann::basic_json<> jsonData, const std::vector<Interactable*>& interactables)
{
	const int id = jsonData.at(Keywords::ID_KEYWORD);
	const InteractableType interactableType = Interactable::GetInteractableTypeFromString(jsonData.at(Keywords::TYPE_KEYWORD));
	for (Interactable* interactable : interactables)
	{
		if (interactable->GetInteractableType() != interactableType)
		{
			continue;
		}
		switch (interactable->GetInteractableType())
		{
		case DOOR: {
			const auto* doorInteractableTemplate = dynamic_cast<DoorInteractableTemplate*>(interactable);
			if (doorInteractableTemplate->GetId() != id)
			{
				break;
			}
			return *interactable;
		}
		case PICKUP: {
			const auto* pickupInventoryInteractable = dynamic_cast<PickupInventoryInteractable*>(interactable);
			if (pickupInventoryInteractable->GetPickupType() != PickupInventoryInteractable::GetPickupTypeFromString(jsonData.at(Keywords::SUB_TYPE_KEYWORD)))
			{
				break;
			}
			if (pickupInventoryInteractable->GetId() != id)
			{
				break;
			}
			return *interactable;
		}
		case PUSH_OBJECT: {
			const auto* pushInteractable = dynamic_cast<PushInteractable*>(interactable);
			if (pushInteractable->GetPushType() != PushInteractable::GetPushTypeFromString(jsonData.at(Keywords::SUB_TYPE_KEYWORD)))
			{
				break;
			}
			if (pushInteractable->GetId() != id)
			{
				break;
			}
			return *interactable;
		}
		}
	}
	throw exception("You added a value which isn't present... Might be smart to change the files!");
}

TiledMapLoader::Action TiledMapLoader::GetActionFromString(const std::string& action)
{
	unordered_map<string, Action> const table =
	{ {Constant::SHOW_UPPERCASE, SHOW} };
	const auto it = table.find(action);
	if (it != table.end()) {
		return it->second;
	}
	return SHOW;
}

TiledMapLoader::MapCondition::MapCondition(const int idValue, std::vector<Interactable*> conditionsValue, std::vector<Operation> operationsValue, bool activatedValue)
{
	id = idValue;
	conditions = std::move(conditionsValue);
	operations = std::move(operationsValue);
	activated = activatedValue;
}
