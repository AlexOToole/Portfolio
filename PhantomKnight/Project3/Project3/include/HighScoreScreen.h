#ifndef HIGHSCORESCREEN
#define HIGHSCORESCREEN

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "UiLibrary.h"
class HighScoreScreen
{
public:
	HighScoreScreen(GameData &t_level);
	~HighScoreScreen();

	void update();
	void newScore(float t_newScore, std::string t_newName);
	void keyPressed(sf::Vector2f t_mousePos, bool t_clicked);
	void render(sf::RenderWindow &t_window);

	bool m_mainMenu = false;
private:
	GameData m_level;
	Label m_highScoreText;
	static const int M_MAX_STORED_SCORES = 10;
	Label m_names[M_MAX_STORED_SCORES];
	Label m_scores[M_MAX_STORED_SCORES];
	std::string m_namesString[M_MAX_STORED_SCORES];
	int m_scoresString[M_MAX_STORED_SCORES];
	Button m_exitButton;
};

#endif // !HIGHSCORESCREEN