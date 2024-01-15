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

	//Input states
	bool b_LeftClicked = false;
	bool b_EscapePressed = false;

	void Input();
	void Update(const float dtAsSeconds);
	void Draw();
	void ClearEverything();

	void CheckIfFilesArePresent();
public:
	Engine();

	//To run the game, will call private functions inside here
	void Run();
};