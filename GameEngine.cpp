#include "GameEngine.h"

GameEngine::GameEngine(const sf::RenderWindow& mainWindow) : m_GameEngineLogic(GameEngineLogic(mainWindow)), m_GamePausedMenu(GamePauseMenu(mainWindow))
{
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine)
{
	if (this == &gameEngine)
	{
		return *this;
	}
	this->m_GamePausedMenu = gameEngine.m_GamePausedMenu;
	this->m_GameEngineLogic = gameEngine.m_GameEngineLogic;
	return *this;
}

GameEngine::GameEngine(GameEngine& gameEngine) : m_GameEngineLogic(gameEngine.m_GameEngineLogic)
{
	m_GamePausedMenu = gameEngine.m_GamePausedMenu;
}

void GameEngine::ClearEverything()
{
	m_GameEngineLogic.ClearSounds();
	m_GamePausedMenu.ClearSounds();
}
