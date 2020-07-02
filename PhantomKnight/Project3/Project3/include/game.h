#ifndef GAME
#define GAME

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "b2GLDraw.h"
#include "LevelLoader.h"
#include "Platform.h"
#include "MainMenu.h"
#include "OptionScreen.h"
#include "HighScoreScreen.h"
#include "LevelSelectScreen.h"
#include "HelpScreen.h"
#include "Player.h"
#include "Ground.h"
#include "PitfallTrap.h"
#include "PickUps.h"
#include "myListener.h"
#include "UiLibrary.h"
#include "SwingingTrap.h"
#include "VerticalWalls.h"
#include "Boundary.h"
#include "TutorialManager.h"
#include "EndGoalParticle.h"
#include "Clouds.h"
#include "MusicManager.h"


enum class GameState
{
	AUTHOR,
	SPLASH,
	MENU,
	TUTORIAL,
	SELECTSCREEN,
	OPTIONS,
	HELP,
	HIGHSCORES,
	GAMEOVER
};

enum class LevelState
{
	TUTORIAL,
	LEVEL1,
	LEVEL2
};

class Game
{
public:
	Game(GameData & t_level);
	void run();
private:
	void levelSelect();
	void loadContent();
	void processEvents();
	void update(sf::Time);
	void render();
	void reset();

	bool m_pause = false;
	static const int M_MAX_BUTTONS = 2;
	Button m_pauseButtons[M_MAX_BUTTONS];
	std::string m_labelText[M_MAX_BUTTONS] = { "Continue", "Exit" };
	sf::Vector2f m_position;
	sf::Vector2f m_size = { 400, 60 };
	sf::Vector2i m_previousMousePos;
	sf::Vector2f m_updatedMousePos;
	static GameState m_currentState;
	static LevelState m_currentLevel;
	static const int M_MAX_PLATFORMS = 15;
	static const int M_MAX_L1_SPIKES = 90;
	sf::RenderWindow m_window;


	//font for the text
	sf::Font m_font;
	sf::Vector2f m_platformPoints[M_MAX_PLATFORMS];
	Platform m_platform[M_MAX_PLATFORMS];
	GameData m_level;
	MainMenu m_mainMenu;
	OptionScreen m_optionsScreen;
	HighScoreScreen m_highScoreScreen;
	HelpScreen m_helpScreen;
	LevelSelectScreen m_levelSelectScreen;
	Ground m_ground;
	Player m_player;
	PitfallTrap m_spikeTrap[M_MAX_L1_SPIKES];
	SwingingTrap m_pendulumTrap;
	VerticalWalls m_wall;
	Boundary m_boundary;
	TutorialManager m_tut;
	EndGoalParticle m_endParticle;
	Clouds m_clouds;
	PickUps m_pickUp;
	
	myListener m_listener;
	MusicManager m_effectsManager;

	int num = 6;

	int count = 0;

	//World
	b2Vec2 gravity = { 0.0f,13.4f };
	b2World world{ gravity };
	float32 timeStep = 1 / 60.0f;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position
	b2GLDraw fooDrawInstance;


	//View 
	sf::View m_view;
	sf::View m_currentView;
	

	bool m_mouseDown{ false };
	bool m_zoom = true;
	bool m_zoomGame = false;

	//Tutorial Message Bools and variables
	bool stepOne = false;


	//gameOver
	Label m_winText;
	Label m_winInstructions;
	Keyboard m_keyboard;
	Button m_gameOverButton;
	bool m_win = false;
	std::string m_playerName = "";
	int m_score = 0;

	//Castle
	sf::Sprite m_castle;
	sf::Texture m_castleTexture;

	GuiPanel m_gui;
	int m_dashCount = 3;

	//game timer for score
	sf::Clock m_clock;
	sf::Time m_elapsed;
	sf::Time m_pauseTime;

	int tempMUSIC;
	int tempSFX;
	int temp;

};
#endif // !GAME