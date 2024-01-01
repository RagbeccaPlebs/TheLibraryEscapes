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

	//Engines
	GameEngine* m_GameEngine;
	StartMenuEngine m_StartMenuEngine;

	//Game state
	bool b_Playing = false;

	void Input();
	void Update(const float dtAsSeconds);
	void Draw();
	void ClearEverything();
public:
	Engine();

	//To run the game, will call private functions inside here
	void Run();
};