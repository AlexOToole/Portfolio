#include "HighScoreScreen.h"



HighScoreScreen::HighScoreScreen(GameData &t_level):
	m_level(t_level)
{
	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		m_namesString[i] = (m_level.m_scores.at(i).m_name);
		m_names[i].setString(m_namesString[i]);
		m_scoresString[i] = (m_level.m_scores.at(i).m_score);
		m_scores[i].setString(std::to_string(m_scoresString[i]));
		//m_level.m_scores.push_back(m_level.m_scores.at(i));
		m_scores[i].setCharacterSize(72);
		m_names[i].setCharacterSize(72);
		m_names[i].setPosition(sf::Vector2f(3840 / 2 - 200, 400 + (i * 100)));
		m_scores[i].setPosition(sf::Vector2f((3840 / 2) + 100, 400 + (i * 100)));
	}
	m_highScoreText.setCharacterSize(128);
	m_highScoreText.setColor(sf::Color(190, 90, 54));
	m_highScoreText.setString("Highscores");
	m_highScoreText.setPosition(sf::Vector2f((3840 / 2), 200));

	m_exitButton.setUp(sf::Vector2f(3840 / 2, 2020), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_exitButton.setString("Exit");

}


HighScoreScreen::~HighScoreScreen()
{
}

/// <summary>
/// updates the highscore table
/// </summary>
void HighScoreScreen::update()
{
	float temp = 0;
	std::string nameTemp = "";
	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		for (int j = i + 1; j < M_MAX_STORED_SCORES; j++)
		{
			if (m_scoresString[j] > m_scoresString[i])
			{
				temp = m_scoresString[i];
				nameTemp = m_namesString[i];
				m_scoresString[i] = m_scoresString[j];
				m_namesString[i] = m_namesString[j];
				m_scoresString[j] = temp;
				m_namesString[j] = nameTemp;
			}
		}
		m_names[i].setString(m_namesString[i]);
		m_scores[i].setString(std::to_string(m_scoresString[i]));
	}
	LevelLoader::write(m_namesString, m_scoresString);
}

/// <summary>
/// Replaces the lowest score currently in the table
/// </summary>
/// <param name="t_newScore"></param>
/// <param name="t_newName"></param>
void HighScoreScreen::newScore(float t_newScore, std::string t_newName)
{
	int lowest = m_scoresString[0];
	int lowestIndex = 0;
	for (int i = 1; i < M_MAX_STORED_SCORES; i++)
	{
		if (m_scoresString[i] < lowest)
		{
			lowest = m_scoresString[i];
			lowestIndex = i;
		}
	}
	m_scoresString[lowestIndex] = t_newScore;
	m_namesString[lowestIndex] = t_newName;

	update();
}

void HighScoreScreen::keyPressed(sf::Vector2f t_mousePos, bool t_clicked)
{
	if (m_exitButton.isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_mainMenu = true;
		}
	}
}

void HighScoreScreen::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(114, 148, 138));
	m_highScoreText.render(t_window);
	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		m_names[i].render(t_window);
		if (m_scoresString[i] > 0)
		{
			m_scores[i].render(t_window);
		}
		std::cout << "Name" + std::to_string(i) << " " << m_namesString[i] << " " << "Score" + std::to_string(i) << " " << m_scoresString[i] << std::endl;
	}
	m_exitButton.render(t_window);
}
