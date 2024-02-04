#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "StartMenuEngine.h"
#include "TextureHolder.h"

class Engine {
private:
	//The TextureHolder creation to have less frequent file loading
	TextureHolder m_TextureHolder;

	//The game window
	sf::RenderWindow m_Window;

	//Engines
	GameEngine* m_GameEngine;
	StartMenuEngine m_StartMenuEngine;

	//Game states
	bool b_Playing = false;
	bool b_WasPlaying = false;

	//Input states
	bool b_LeftClicked = false;
	bool b_EscapePressed = false;

	//Game specific functions
	void Input();
	void Update(const float dtAsSeconds);
	void Draw();

	//Delete function
	void ClearEverything() const;

	//Save game
	void SaveAll();

	//Checks and Initializers
	void CheckIfFilesArePresent();
public:
	Engine();

	//To run the game, will call private functions inside here
	void Run();
};