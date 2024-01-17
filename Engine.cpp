#include "Engine.h"

#include <fstream>

#include "Constants.h"
#include "nlohmann/json.hpp"

using namespace sf;
using namespace std;
using json = nlohmann::json;

Engine::Engine()
{
	m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), Constant::GAME_TITLE, Style::Fullscreen);

	//Check if all files are there, otherwise add them
	CheckIfFilesArePresent();

	delete m_GameEngine;
	m_GameEngine = new GameEngine(m_Window);
}

void Engine::ClearEverything() const
{
	m_GameEngine->ClearEverything();
}


void Engine::Run() {

	//Timing
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		const float dtAsSeconds = dt.asSeconds();

		Input();
		Update(dtAsSeconds);
		Draw();
	}

	ClearEverything();
}

void Engine::CheckIfFilesArePresent()
{
	//Game Data
	ifstream gameDataFile(Files::GAME_DATA_FILE);
	if (gameDataFile.is_open())
	{
		nlohmann::json data = json::parse(gameDataFile);
		gameDataFile.close();
		//Reset whole file
		if (!data.contains(Keywords::BOOK_KEYWORD) || !data.contains(Keywords::DOOR_KEYWORD)
			|| !data.contains(Keywords::KEY_KEYWORD) || !data.contains(Keywords::PLAYER_KEYWORD))
		{
			json jsonData;
			jsonData[Keywords::BOOK_KEYWORD] = json::array();
			jsonData[Keywords::KEY_KEYWORD] = json::array();
			jsonData[Keywords::DOOR_KEYWORD] = json::array();

			json playerLayers;
			playerLayers[Keywords::PLAYER_BASE_KEYWORD] = Constant::INITIAL_BASE_LAYER;
			playerLayers[Keywords::PLAYER_LOWER_LAYER_KEYWORD] = Constant::INITIAL_LOWER_LAYER_LAYER;
			playerLayers[Keywords::PLAYER_CLOAK_KEYWORD] = Constant::INITIAL_CLOAK_LAYER;
			playerLayers[Keywords::PLAYER_FACE_ITEM_KEYWORD] = Constant::EMPTY_STRING;
			playerLayers[Keywords::PLAYER_HAIR_KEYWORD] = Constant::EMPTY_STRING;
			playerLayers[Keywords::PLAYER_HAT_KEYWORD] = Constant::INITIAL_HAT_LAYER;

			jsonData[Keywords::PLAYER_KEYWORD].push_back(playerLayers);
			ofstream fileOfStream(Files::GAME_DATA_FILE);
			fileOfStream << jsonData;
			fileOfStream.flush();
		}
	}
	else
	{
		gameDataFile.close();
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
	}
}
