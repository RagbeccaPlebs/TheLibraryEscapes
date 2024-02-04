#pragma once
#include <SFML/Graphics.hpp>

#include "GameEngineLogic.h"
#include "GamePauseMenu.h"

//The Game specific engine
class GameEngine
{
	//Game state
	bool b_Paused = false;

	//Game Logics
	GameEngineLogic m_GameEngineLogic;
	GamePauseMenu m_GamePausedMenu;
public:
	//Constructors, destructors and copy assignment operators
	GameEngine(const sf::RenderWindow& mainWindow);
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