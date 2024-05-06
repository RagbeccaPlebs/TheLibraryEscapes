#include "StartMenuEngine.h"

#include "Constants.h"
#include <fstream>
#include <iostream>
#include <random>
#include "nlohmann/json.hpp"

using namespace sf;
using namespace std;
using json = nlohmann::json;

//CONSTRUCTOR
StartMenuEngine::StartMenuEngine(const Font& font)
{
	m_StartMenuView.setSize(static_cast<float>(VideoMode::getDesktopMode().width), static_cast<float>(VideoMode::getDesktopMode().height));

	const Color hoverColor(100, 100, 100);
	const Color idleColor(70, 70, 70);
	const Color activeColor(20, 20, 100);
	const Vector2f paddingButtons(100.f, 100.f);
	const float middleWidth = (static_cast<float>(VideoMode::getDesktopMode().width) / 2.0f);
	const float middleHeight = (static_cast<float>(VideoMode::getDesktopMode().height) / 2.0f);
	const Vector2f startButtonLocation((middleWidth), middleHeight - 150.f);
	const Vector2f exitButtonLocation((middleWidth), middleHeight + 50.f);
	const Vector2f resetGameButtonLocation(0, 0);
	m_StartButton = Button(startButtonLocation, paddingButtons, font,
		Message::START_MESSAGE, 80, idleColor, hoverColor, activeColor, true);
	m_ExitButton = Button(exitButtonLocation, paddingButtons, font,
		Message::EXIT_MESSAGE, 80, idleColor, hoverColor, activeColor, true);
	m_ResetGameButton = Button(resetGameButtonLocation, paddingButtons, font,
		Message::RESET_GAME_MESSAGE, 40, idleColor, hoverColor, activeColor, false);
}

//DRAW
void StartMenuEngine::Draw(RenderWindow& mainWindow, const Font& font)
{
	mainWindow.setView(m_StartMenuView);
	m_ExitButton.Draw(mainWindow);
	m_StartButton.Draw(mainWindow);
	m_ResetGameButton.Draw(mainWindow);
	if (b_ShouldShowTip)
	{
		b_ShouldShowTip = false;
		ShowResetTip(mainWindow, font);
	}
}

//INPUT
void StartMenuEngine::Input(RenderWindow& mainWindow, GameState& gameState, const bool& isEscapePressed, bool& resetEverything)
{
	if (isEscapePressed)
	{
		mainWindow.close();
	}

	if (m_StartButton.IsPressed())
	{
		gameState = DOING;
	}

	if (m_ExitButton.IsPressed())
	{
		mainWindow.close();
	}

	if (m_ResetGameButton.IsPressed())
	{
		b_ShouldShowTip = true;
		ResetGame(resetEverything);
	}
}

void StartMenuEngine::ShowResetTip(RenderWindow& mainWindow, const Font& font) const
{
	mainWindow.setView(m_StartMenuView);
	//Make background faded
	RectangleShape screenDarkener;
	const Color darkerColor(0, 0, 0, 100);
	screenDarkener.setSize(Vector2f(static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
	screenDarkener.setFillColor(darkerColor);
	mainWindow.draw(screenDarkener);

	const Color color(0, 0, 0, 50);
	const Color textColor(255, 0, 255, 255);

	vector<string> tips = { Message::TIP_ONE ,Message::TIP_TWO ,Message::TIP_THREE,Message::TIP_FOUR };
	const int index = static_cast<int>(rand() % tips.size());

	//Show text
	const float middleWidth = (static_cast<float>(VideoMode::getDesktopMode().width) / 2.0f);
	const float middleHeight = (static_cast<float>(VideoMode::getDesktopMode().height) / 2.0f);
	const Vector2f paddingButtons(100.f, 100.f);
	const auto text = Button{ Vector2f{ middleWidth,middleHeight }, paddingButtons, font,
		tips[index], 120, color, color, color, textColor, true };
	text.Draw(mainWindow);
}

void StartMenuEngine::ResetGame(bool& resetEverything)
{
	json jsonData;
	jsonData[Keywords::BOOK_KEYWORD] = json::array();
	jsonData[Keywords::KEY_KEYWORD] = json::array();
	jsonData[Keywords::DOOR_KEYWORD] = json::array();

	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_BASE_KEYWORD] = Constant::INITIAL_BASE_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_LOWER_LAYER_KEYWORD] = Constant::INITIAL_LOWER_LAYER_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_CLOAK_KEYWORD] = Constant::INITIAL_CLOAK_LAYER;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_FACE_ITEM_KEYWORD] = Constant::EMPTY_STRING;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAIR_KEYWORD] = Constant::EMPTY_STRING;
	jsonData[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAT_KEYWORD] = Constant::INITIAL_HAT_LAYER;

	jsonData[Keywords::TIME_LEFT_KEYWORD] = Constant::INITIAL_TIMER;

	ofstream fileOfStream(Files::GAME_DATA_FILE);
	fileOfStream << jsonData;
	fileOfStream.flush();

	//Copy the initial map files to the real folder
	const string path = Files::MAP_DETAILS_INITIAL_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(path))
	{
		ifstream file(entry.path());
		json data = json::parse(file);
		file.close();
		ofstream fileToMapDetails(Files::MAP_DETAILS_FOLDER + entry.path().filename().string());
		fileToMapDetails << data;
		fileToMapDetails.flush();
	}
	resetEverything = true;
}

//UPDATE
void StartMenuEngine::Update(float dtAsSeconds, RenderWindow& mainWindow, const bool& isLeftClicked)
{
	mainWindow.setMouseCursorVisible(true);

	m_MousePosView = mainWindow.mapPixelToCoords(Mouse::getPosition(mainWindow));

	m_ExitButton.Update(m_MousePosView, mainWindow);
	m_StartButton.Update(m_MousePosView, mainWindow);
	m_ResetGameButton.Update(m_MousePosView, mainWindow);

	if (isLeftClicked)
	{
		m_ExitButton.Press(m_MousePosView);
		m_StartButton.Press(m_MousePosView);
		m_ResetGameButton.Press(m_MousePosView);
	}

	m_StartMenuView.setCenter(static_cast<float>(mainWindow.getSize().x) / 2.f, static_cast<float>(mainWindow.getSize().y) / 2.f);
}

