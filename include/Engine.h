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
	GameState m_GameState;

	//Input states
	bool b_LeftClicked = false;
	bool b_EscapePressed = false;

	//Reset state
	bool b_ResetEverything = false;

	//Game specific functions
	void Input();
	void Update(const float dtAsSeconds);
	void Draw();

	//Delete function
	void ClearEverything() const;

	//Save game
	void SaveAll() const;

	//Checks and Initializers
	static void CheckIfFilesArePresent();

	//Reset all the GameEngine
	void ResetGameEngine();

	//Font for text
	sf::Font m_Font;
public:
	Engine();

	//To run the game, will call private functions inside here
	void Run();
};