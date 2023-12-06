#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "Map.h"

class Engine {
private:
	//TextureHolder
	TextureHolder m_th;

	//PlayerMovement
	PlayerMovement m_PM;

	//Player
	Player m_Player;

	//Map
	Map m_Map;

	sf::RenderWindow m_Window;

	sf::View m_MainView;
	sf::View m_HudView;

	//Game states
	bool m_Playing;
	bool m_Inventory;
	bool m_IsNewMapNeeded;

	void loadMap();

	void detectCollisions(Player& player);

	void input();
	void update(float dtAsSeconds);
	void draw();
public:
	Engine();

	//To run the game, will call private functions inside here
	void run();
};