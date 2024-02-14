#include "GameEngine.h"
#include "StartMenuEngine.h"
#include <fstream>

#include "Constants.h"
#include "nlohmann/json.hpp"

using namespace sf;
using namespace std;
using json = nlohmann::json;

void StartMenuEngine::Input(sf::RenderWindow& mainWindow, bool& isPlayingState, const bool& isEscapePressed, bool& resetEverything)
{
	if (isEscapePressed)
	{
		mainWindow.close();
	}

	if (m_StartButton.IsPressed())
	{
		isPlayingState = true;
	}

	if (m_ExitButton.IsPressed())
	{
		mainWindow.close();
	}

	if (m_ResetGameButton.IsPressed())
	{
		ResetGame(resetEverything);
	}
}

void StartMenuEngine::ResetGame(bool& resetEverything)
{
	json jsonData;
	jsonData[Keywords::BOOK_KEYWORD] = json::array();
	jsonData[Keywords::KEY_KEYWORD] = json::array();
	jsonData[Keywords::DOOR_KEYWORD] = json::array();

	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_BASE_KEYWORD] = Constant::INITIAL_BASE_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_LOWER_LAYER_KEYWORD] = Constant::INITIAL_LOWER_LAYER_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_CLOAK_KEYWORD] = Constant::INITIAL_CLOAK_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_FACE_ITEM_KEYWORD] = Constant::EMPTY_STRING;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAIR_KEYWORD] = Constant::EMPTY_STRING;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAT_KEYWORD] = Constant::INITIAL_HAT_LAYER;

	ofstream fileOfStream(Files::GAME_DATA_FILE);
	fileOfStream << jsonData;
	fileOfStream.flush();

	//Copy the initial map files to the real folder
	const string path = Files::MAP_DETAILS_INITIAL_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(path))
	{
		ifstream file(entry.path());
		json data = json::parse(file);
		file.close();
		ofstream fileToMapDetails(Files::MAP_DETAILS_FOLDER + entry.path().filename().string());
		fileToMapDetails << data;
		fileToMapDetails.flush();
	}
	resetEverything = true;
}

