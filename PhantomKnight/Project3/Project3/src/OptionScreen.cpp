#include "OptionScreen.h"



OptionScreen::OptionScreen()
{
	m_optionText.setCharacterSize(64);
	m_optionText.setColor(sf::Color(190, 90, 54));
	m_optionText.setString("Options");
	m_optionText.setPosition(sf::Vector2f((3840 / 2), 200));

	m_exitButton.setUp(sf::Vector2f(3840 / 2, 2020), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_exitButton.setString("Exit");

	particlesTest.menuEffect();

	m_musicSlider.setPosition(sf::Vector2f(3840 / 2, (2160 / 2) - 100));

	m_sfxSlider.setPosition(sf::Vector2f(3840 / 2, (2160 / 2) + 100));

	m_musicVolLabel.setPosition(sf::Vector2f(3840 / 2, (2160 / 2) - 190));
	m_sfxVolLabel.setPosition(sf::Vector2f(3840 / 2, (2160 / 2)));
	m_musicVolLabel.setString("Music Vol: " + std::to_string(m_musicSlider.getValue()));
	m_sfxVolLabel.setString("SFX Vol: " + std::to_string(m_sfxSlider.getValue()));
}


OptionScreen::~OptionScreen()
{
}

void OptionScreen::processingEvents(sf::Event t_event)
{
	m_musicSlider.processingEvents(t_event);
	m_sfxSlider.processingEvents(t_event);
}

void OptionScreen::update(sf::Vector2f t_mousePos, bool t_clicked)
{

	particlesTest.update(sf::Vector2f(1920, 0));
	if (m_exitButton.isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_mainMenu = true;
		}
	}
	m_musicSlider.update(t_mousePos);
	m_sfxSlider.update(t_mousePos);
	m_musicVolLabel.setString("Music Vol: " + std::to_string(m_musicSlider.getValue()));
	m_sfxVolLabel.setString("SFX Vol: " + std::to_string(m_sfxSlider.getValue()));
	m_musicVolLabel.setPosition(sf::Vector2f(3840 / 2, (2160 / 2) - 190));
	m_sfxVolLabel.setPosition(sf::Vector2f(3840 / 2, (2160 / 2)));
}

void OptionScreen::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(114, 148, 138));
	particlesTest.render(t_window);
	m_optionText.render(t_window);
	m_musicSlider.render(t_window);
	m_musicVolLabel.render(t_window);
	m_sfxSlider.render(t_window);
	m_sfxVolLabel.render(t_window);
	m_exitButton.render(t_window);
}
