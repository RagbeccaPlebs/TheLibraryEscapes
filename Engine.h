#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "StartMenuEngine.h"
#include "TextureHolder.h"

class Engine {
private:
	//Holders
	TextureHolder m_TextureHolder;

	sf::RenderWindow m_Window;

	sf::View m_GameView;
	sf::View m_MainView;
	sf::View m_HudView;

	//Engines
	GameEngine m_GameEngine;
	StartMenuEngine m_StartMenuEngine;

	//Game state
	bool m_Playing = false;

	void Input();
	void Update(const float dtAsSeconds);
	void Draw();
public:
	Engine();

	//To run the game, will call private functions inside here
	void Run();
};