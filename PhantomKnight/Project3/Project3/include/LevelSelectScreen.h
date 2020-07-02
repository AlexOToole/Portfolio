#ifndef LEVELSELECTSCREEN
#define LEVELSELECTSCREEN

#include <SFML/Graphics.hpp>
#include "UiLibrary.h"

class LevelSelectScreen
{
public:
	LevelSelectScreen();
	~LevelSelectScreen();

	void update(sf::Vector2f t_mousePos, bool &t_clicked);
	void render(sf::RenderWindow & t_window);
	bool m_mainMenu = false;
	bool m_tutorial = false;
	bool m_level1 = false;
	bool m_level2 = false;
private:
	Button m_exitButton;
	Button m_levelButtons[3];
	Label m_levelSelectText;
};

#endif // !LEVELSELECTSCREEN