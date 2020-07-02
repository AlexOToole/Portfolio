#include "LevelSelectScreen.h"



LevelSelectScreen::LevelSelectScreen()
{
	m_exitButton.setUp(sf::Vector2f(3840 / 2, 2020), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_exitButton.setString("Exit");
	m_levelButtons[0].setUp(sf::Vector2f(800, 2160 / 2), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_levelButtons[1].setUp(sf::Vector2f(3840 / 2, 2160 / 2), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_levelButtons[2].setUp(sf::Vector2f(3040, 2160 / 2), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_levelButtons[0].setString("Tutorial");
	m_levelButtons[1].setString("Level 1");
	m_levelButtons[2].setString("Level 2");
	m_levelSelectText.setPosition(sf::Vector2f(3840 / 2, 200));
	m_levelSelectText.setString("Level Select");
}


LevelSelectScreen::~LevelSelectScreen()
{
}

void LevelSelectScreen::update(sf::Vector2f t_mousePos, bool & t_clicked)
{
	if (m_exitButton.isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_mainMenu = true;
		}
	}
	if (m_levelButtons[0].isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_tutorial = true;
		}
	}
	if (m_levelButtons[1].isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_level1 = true;
		}
	}
	if (m_levelButtons[2].isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_level2 = true;
		}
	}
}

void LevelSelectScreen::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(114, 148, 138));
	m_exitButton.render(t_window);
	m_levelSelectText.render(t_window);
	for (int i = 0; i < 3; i++)
	{
		m_levelButtons[i].render(t_window);
	}
}
