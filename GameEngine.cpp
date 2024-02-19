#include "GameEngine.h"
#include "EndMenu.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;
using namespace sf;

//CONSTRUCTORS
GameEngine::GameEngine(const sf::RenderWindow& mainWindow) : m_GameEngineLogic(GameEngineLogic(mainWindow)), m_GamePausedMenu(GamePauseMenu(mainWindow)), m_EndMenu(EndMenu(mainWindow))
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
	this->m_EndMenu = gameEngine.m_EndMenu;
	return *this;
}

GameEngine::GameEngine(GameEngine& gameEngine) : m_GameEngineLogic(gameEngine.m_GameEngineLogic)
{
	m_GamePausedMenu = gameEngine.m_GamePausedMenu;
	m_EndMenu = gameEngine.m_EndMenu;
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
void GameEngine::Draw(RenderWindow& mainWindow)
{
	m_GameEngineLogic.Draw(mainWindow);
	if (b_Won)
	{
		m_EndMenu.Draw(mainWindow);
	}
	if (b_Paused)
	{
		m_GamePausedMenu.Draw(mainWindow);
	}
}

//INPUT
void GameEngine::Input(RenderWindow& mainWindow, bool& isPlaying, bool& wasPlaying, const bool& isEscapePressed)
{
	if (b_Won)
	{
		m_EndMenu.Input(isPlaying, wasPlaying, isEscapePressed);
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
	if (b_Won)
	{
		m_EndMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else if (b_Paused)
	{
		m_GamePausedMenu.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
	else
	{
		m_GameEngineLogic.Update(dtAsSeconds, mainWindow, isLeftClicked);
	}
}
