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
	bool b_Lost = false;

	//Game Logics
	GameEngineLogic m_GameEngineLogic;
	GamePauseMenu m_GamePausedMenu;
	EndMenu m_EndWonMenu;
	EndMenu m_EndLostMenu;
public:
	//Constructors, destructors and copy assignment operators
	explicit GameEngine(const sf::RenderWindow& mainWindow, const sf::Font& font);
	GameEngine& operator=(const GameEngine& gameEngine);
	~GameEngine();
	GameEngine(GameEngine& gameEngine);

	//Game Logic Runners
	void Draw(sf::RenderWindow& mainWindow, const sf::Font& font);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow, const bool& isLeftClicked);
	void Input(sf::RenderWindow& mainWindow, GameState& gameState, const bool& isEscapePressed);

	//Destructor
	void ClearEverything();

	//Save game
	void SaveAll();

	static int GetAmountOfBooksTotal();
	static int GetAmountOfFoundBooks();
};