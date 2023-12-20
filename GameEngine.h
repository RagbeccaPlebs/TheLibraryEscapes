#pragma once
#include <SFML/Graphics.hpp>

#include "GameEngineLogic.h"
#include "GamePauseMenu.h"

class GameEngine
{
	//Game state
	bool b_Paused = false;

	//Game Logics
	GameEngineLogic m_GameEngineLogic;
	GamePauseMenu m_GamePausedMenu;
public:
	GameEngine(const sf::RenderWindow& mainWindow);
	GameEngine& operator=(const GameEngine& gameEngine);
	~GameEngine() = default;
	GameEngine(GameEngine& gameEngine);

	void Draw(sf::RenderWindow& mainWindow);
	void Update(float dtAsSeconds, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWindow, bool& isPlaying);
};