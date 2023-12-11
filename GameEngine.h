#pragma once
#include <SFML/Graphics.hpp>

#include "GameEngineLogic.h"
#include "GamePauseMenu.h"

class GameEngine {
private:
	//Game state
	bool b_Paused = false;

	//Game Logics
	GameEngineLogic m_GameEngineLogic;
	GamePauseMenu m_GamePausedMenu;
public:
	void Draw(sf::RenderWindow& mainWindow, sf::View& hudView);
	void Update(float dtAsSeconds, sf::View* mainView, sf::View* hudView, sf::RenderWindow& mainWindow);
	void Input(sf::RenderWindow& mainWindow, bool& isPlaying);
};