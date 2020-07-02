#ifndef MAINMENU
#define MAINMENU

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "LevelLoader.h"
#include "UiLibrary.h"
#include "EndGoalParticle.h"


class MainMenu
{
public:
	MainMenu(GameData & t_level);
	~MainMenu();

	void update(sf::Vector2f t_mousePos, bool &t_click);
	void render(sf::RenderWindow & t_window);

	bool m_play = false;
	bool m_options = false;
	bool m_highscores = false;
	bool m_exit = false;
	bool m_help = false;
private:
	GameData m_level;
	sf::RectangleShape m_base;
	static const int M_MAX_BUTTONS = 5;
	Button m_buttons[M_MAX_BUTTONS];
	std::string m_labelText[M_MAX_BUTTONS] = { "Play", "Options", "Help", "Highscores", "Exit" };
	sf::Vector2f m_position = { 1920, 440 };
	sf::Vector2f m_size = { 600, 120 };
	sf::Texture m_logoTexture;
	sf::Sprite m_logo;
	bool m_fall = true;
	sf::Vector2f m_logoPosition = { 1920,100 };


	EndGoalParticle particlesTest;

};

#endif // !MAINMENU