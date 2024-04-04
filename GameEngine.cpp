#include "GameEngine.h"
#include "EndMenu.h"

#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;
using namespace sf;

//CONSTRUCTORS
GameEngine::GameEngine(const RenderWindow& mainWindow, const Font& font) : m_GameEngineLogic(GameEngineLogic(mainWindow, font)),
                                                         m_GamePausedMenu(GamePauseMenu(mainWindow, font)),
                                                         m_EndWonMenu(EndMenu(mainWindow, false, font)),
                                                         m_EndLostMenu(EndMenu(mainWindow, true, font))
{
	b_Won = GameEngineLogic::CheckForFinishingCondition();
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine)
{
	if (this == &gameEngine)
	{
		return *this;
	}
	this->m_GamePausedMenu = gameEngine.m_GamePausedMenu;
	this->m_GameEngineLogic = gameEngine.m_GameEngineLogic;
	this->m_EndWonMenu = gameEngine.m_EndWonMenu;
	return *this;
}

GameEngine::GameEngine(GameEngine& gameEngine) : m_GameEngineLogic(gameEngine.m_GameEngineLogic)
{
	m_GamePausedMenu = gameEngine.m_GamePausedMenu;
	m_EndWonMenu = gameEngine.m_EndWonMenu;
}

//DESTRUCTORS
GameEngine::~GameEngine()
{
	ClearEverything();
}

void GameEngine::ClearEverything()
{
	m_GameEngineLogic.SaveAll();
	m_GameEngineLogic.ClearSounds();
	m_GamePausedMenu.ClearSounds();
}

//SAVING
void GameEngine::SaveAll()
{
	m_GameEngineLogic.SaveAll();
}

//DRAW
void GameEngine::Draw(RenderWindow& mainWindow, const Font& font)
{
	m_GameEngineLogic.Draw(mainWindow, font);
	if (b_Lost)
	{
		m_EndLostMenu.Draw(mainWindow);
	}
	else if (b_Won)
	{
		m_EndWonMenu.Draw(mainWindow);
	}
	else if (b_Paused)
	{
		m_GamePausedMenu.Draw(mainWindow);
	}
}

//INPUT
void GameEngine::Input(RenderWindow& mainWindow, bool& isPlaying, bool& wasPlaying, const bool& isEscapePressed)
{
	if (b_Lost)
	{
		m_EndLostMenu.Input(isPlaying, wasPlaying, isEscapePressed);
	}
	else if (b_Won)
	{
		m_EndWonMenu.Input(isPlaying, wasPlaying, isEscapePressed);
	}
	else if (b_Paused)
	{
		m_GamePausedMenu.Input(mainWindow, isPlaying, b_Paused, wasPlaying, isEscapePressed);
	}
	else
	{
		m_GameEngineLogic.Input(mainWindow, isPlaying, b_Paused, isEscapePressed, b_Won);
	}
}

//UPDATE
void GameEngine::Update(const float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	if (b_Lost)
	{
		m_EndLostMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else if (b_Won)
	{
		m_EndWonMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else if (b_Paused)
	{
		m_GamePausedMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else
	{
		m_GameEngineLogic.Update(dtAsSeconds, mainWindow, isLeftClicked, b_Lost);
	}
}

//Getter
int GameEngine::GetAmountOfBooksTotal()
{
	ifstream file(Files::BOOKS_DATA_FILE);
	json data = json::parse(file);
	file.close();

	return static_cast<int>(data.at(Keywords::BOOK_KEYWORD).size());
}

int GameEngine::GetAmountOfFoundBooks()
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	return static_cast<int>(data.at(Keywords::BOOK_KEYWORD).size());
}
