#include "MainMenu.h"



MainMenu::MainMenu(GameData & t_level) :
	m_level(t_level)
{
	m_logoTexture.loadFromFile("ASSETS/SPRITES/Logo.png");
	m_logo.setTexture(m_logoTexture);
	m_logo.scale(sf::Vector2f(2, 2));
	m_logo.setOrigin(m_logo.getLocalBounds().width / 2, m_logo.getLocalBounds().height / 2);
	m_logo.setPosition(m_logoPosition);
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_buttons[i].setUp(m_position, m_size,sf::Color::Black, sf::Color(190,90,54));
		m_buttons[i].setPosition(sf::Vector2f(m_position.x, m_position.y + i * 240));
		m_buttons[i].setString(m_labelText[i]);
	}

	particlesTest.menuEffect();

}


MainMenu::~MainMenu()
{
}

void MainMenu::update(sf::Vector2f t_mousePos, bool &t_click)
{
	particlesTest.update(sf::Vector2f(1920, 0));

	if (m_buttons[0].isHighlighted(t_mousePos))
	{
		if (t_click)
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_play = true;
		}
	}
	if (m_buttons[1].isHighlighted(t_mousePos))
	{
		if (t_click)
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_options = true;
		}
	}
	if (m_buttons[2].isHighlighted(t_mousePos))
	{
		if (t_click)
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_help = true;
		}
	}
	if (m_buttons[3].isHighlighted(t_mousePos))
	{
		if (t_click)
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_highscores = true;
		}
	}
	if (m_buttons[4].isHighlighted(t_mousePos))
	{
		if (t_click)
		{
			m_exit = true;
		}
	}

	//Animated title text
	if (m_logo.getPosition().y == 200)
	{
		m_fall = false;
	}
	if (m_logo.getPosition().y == 100 && !m_fall)
	{
		m_fall = true;
	}
	if (m_fall)
	{
		m_logoPosition.y += 0.5;
	}
	if (!m_fall)
	{
		m_logoPosition.y -= 0.5;
	}
	m_logo.setPosition(m_logoPosition);
}

void MainMenu::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(114, 148, 138));
	particlesTest.render(t_window);
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_buttons[i].render(t_window);
	}
	t_window.draw(m_logo);
}
