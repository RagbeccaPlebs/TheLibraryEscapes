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
	m_Window.setVerticalSyncEnabled(true);

	//Check if all files are there, otherwise add them
	CheckIfFilesArePresent();

	m_Font.loadFromFile(Files::FONT_FILE);

	m_StartMenuEngine = StartMenuEngine(m_Font);

	delete m_GameEngine;
	m_GameEngine = new GameEngine(m_Window, m_Font);
}

void Engine::ClearEverything() const
{
	m_GameEngine->ClearEverything();
}

void Engine::SaveAll() const
{
	m_GameEngine->SaveAll();
}


void Engine::Run() {

	//Timing
	Clock clock;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		// Make a decimal fraction from the delta time
		const float dtAsSeconds = dt.asSeconds();

		if (b_ResetEverything) {
			ResetGameEngine();
			b_ResetEverything = false;
		}

		Input();
		Update(dtAsSeconds);
		Draw();
	}

	SaveAll();
	ClearEverything();
}

void Engine::CheckIfFilesArePresent()
{
	//Folder creation
	filesystem::create_directory(filesystem::path("./" + Files::ASSETS_FOLDER));
	filesystem::create_directory(filesystem::path("./" + Files::ASSETS_DATA_FOLDER));
	//Game Data
	ifstream gameDataFile(Files::GAME_DATA_FILE);
	if (gameDataFile.is_open())
	{
		nlohmann::json data = json::parse(gameDataFile);
		gameDataFile.close();
		//Reset whole file
		if (!data.contains(Keywords::BOOK_KEYWORD) || !data.contains(Keywords::DOOR_KEYWORD)
			|| !data.contains(Keywords::KEY_KEYWORD) || !data.contains(Keywords::PLAYER_KEYWORD)
			|| !data.contains(Keywords::TIME_LEFT_KEYWORD))
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

			jsonData[Keywords::TIME_LEFT_KEYWORD] = Constant::INITIAL_TIMER;

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

		jsonData[Keywords::TIME_LEFT_KEYWORD] = Constant::INITIAL_TIMER;

		ofstream fileOfStream(Files::GAME_DATA_FILE);
		fileOfStream << jsonData;
		fileOfStream.flush();
	}

	//Copy the initial map files to the real folder
	const string pathIntialFolder = Files::MAP_DETAILS_INITIAL_FOLDER;
	const string pathMapFolder = Files::MAP_DETAILS_FOLDER;
	vector<string> entriesInMapFolder;
	for (const auto& entry : filesystem::directory_iterator(pathMapFolder))
	{
		if (entry.path().extension() == Files::JSON_EXTENSION)
		{
			entriesInMapFolder.push_back(entry.path().filename().string());
		}
	}
	for (const auto& entry : filesystem::directory_iterator(pathIntialFolder))
	{
		if (std::find(entriesInMapFolder.begin(), entriesInMapFolder.end(), entry.path().filename().string()) == entriesInMapFolder.end())
		{
			ifstream file(entry.path());
			json data = json::parse(file);
			file.close();
			ofstream fileToMapDetails(Files::MAP_DETAILS_FOLDER + entry.path().filename().string());
			fileToMapDetails << data;
			fileToMapDetails.flush();
		}
	}
}

void Engine::ResetGameEngine()
{
	delete m_GameEngine;
	m_GameEngine = new GameEngine(m_Window, m_Font);
}

//DRAWING
void Engine::Draw()
{
	// Clear the last frame
	m_Window.clear();

	//If playing use the Game Engine draw, if not see it asif the start menu is open
	if (m_GameState == DOING)
	{
		m_GameEngine->Draw(m_Window, m_Font);
	}
	else
	{
		m_StartMenuEngine.Draw(m_Window, m_Font);
	}

	m_Window.display();
}

//INPUT
void Engine::Input() {

	if (m_GameState == DOING)
	{
		m_GameEngine->Input(m_Window, m_GameState, b_EscapePressed);
	}
	else
	{
		m_StartMenuEngine.Input(m_Window, m_GameState, b_EscapePressed, b_ResetEverything);
	}

	if (b_LeftClicked)
	{
		b_LeftClicked = false;
	}

	if (b_EscapePressed)
	{
		b_EscapePressed = false;
	}

	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				b_LeftClicked = true;
			}
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				b_EscapePressed = true;
			}
		}
	}
}

//UPDATE
void Engine::Update(const float dtAsSeconds)
{
	if (m_GameState == CHANGED)
	{
		m_GameState = STOPPED;
		m_GameEngine->ClearEverything();
		sleep(milliseconds(2));
		m_GameEngine = new GameEngine(m_Window, m_Font);
	}

	if (m_GameState == DOING)
	{
		m_GameEngine->Update(dtAsSeconds, m_Window, b_LeftClicked);
	}
	else
	{
		m_StartMenuEngine.Update(dtAsSeconds, m_Window, b_LeftClicked);
	}
}