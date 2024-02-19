#pragma once

#include "EndMenu.h"
#include "GameEngineLogic.h"
#include "GamePauseMenu.h"

//The Game specific engine
class GameEngine
{
	//Game state
	bool b_Paused = false;
	bool b_Won = false;

	//Game Logics
	GameEngineLogic m_GameEngineLogic;
	GamePauseMenu m_GamePausedMenu;
	EndMenu m_EndMenu;
public:
	//Constructors, destructors and copy assignment operators
	explicit GameEngine(const sf::RenderWindow& mainWindow);
	GameEngine& operator=(const GameEngine& gameEngine);
	~GameEngine();
	GameEngine(GameEngine& gameEngine);

	//Game Logic Runners
	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, bool& isPlaying, bool& wasPlaying, const bool& isEscapePressed);

	//Destructor
	void ClearEverything();

	//Save game
	void SaveAll();
};