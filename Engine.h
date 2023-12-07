#pragma once
#include <SFML/Graphics.hpp>
#include "GameEngine.h"

class Engine {
private:
	sf::RenderWindow m_Window;

	sf::View m_MainView;
	sf::View m_HudView;

	GameEngine m_GameEngine;

	//Game state
	bool m_Playing;

	void input();
	void update(const float dtAsSeconds);
	void draw();
public:
	Engine();

	//To run the game, will call private functions inside here
	void run();
};