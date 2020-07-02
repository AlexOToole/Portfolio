#include "TutorialManager.h"



TutorialManager::TutorialManager()
{
	if (!m_signTexture.loadFromFile("ASSETS/SPRITES/sign.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	if (!m_interPopText.loadFromFile("ASSETS/SPRITES/popups/enter.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	if (!m_popTexture[0].loadFromFile("ASSETS/SPRITES/popups/move.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	if (!m_popTexture[1].loadFromFile("ASSETS/SPRITES/popups/jump.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	if (!m_popTexture[2].loadFromFile("ASSETS/SPRITES/popups/dash.png"))
	{
		std::cout << " No File Found " << std::endl;
	}
}


TutorialManager::~TutorialManager()
{
}

void TutorialManager::setup()
{

	//setting up the first sign
	m_signs[0].setTexture(m_signTexture);
	m_signs[0].setPosition(-650, 685);
	m_signs[0].setOrigin(m_signs[0].getLocalBounds().width / 2, m_signs[0].getLocalBounds().height / 2);
	m_signs[0].scale(0.25, 0.25);

	m_interPopUp[0].setTexture(m_interPopText);
	m_interPopUp[0].setPosition(m_signs[0].getPosition().x + 40, m_signs[0].getPosition().y - 100);
	m_interPopUp[0].setOrigin(m_interPopUp[0].getLocalBounds().width / 2, m_interPopUp[0].getLocalBounds().height / 2);
	m_interPopUp[0].scale(0.5, 0.5);

	//setting up the Second sign
	m_signs[1].setTexture(m_signTexture);
	m_signs[1].setPosition(-100, 685);
	m_signs[1].setOrigin(m_signs[1].getLocalBounds().width / 2, m_signs[1].getLocalBounds().height / 2);
	m_signs[1].scale(0.25, 0.25);

	m_interPopUp[1].setTexture(m_interPopText);
	m_interPopUp[1].setPosition(m_signs[1].getPosition().x + 40, m_signs[1].getPosition().y - 100);
	m_interPopUp[1].setOrigin(m_interPopUp[1].getLocalBounds().width / 2, m_interPopUp[1].getLocalBounds().height / 2);
	m_interPopUp[1].scale(0.5, 0.5);

	//setting up the Third sign
	m_signs[2].setTexture(m_signTexture);
	m_signs[2].setPosition(2200, -70);
	m_signs[2].setOrigin(m_signs[2].getLocalBounds().width / 2, m_signs[2].getLocalBounds().height / 2);
	m_signs[2].scale(0.25, 0.25);

	m_interPopUp[2].setTexture(m_interPopText);
	m_interPopUp[2].setPosition(m_signs[2].getPosition().x + 40, m_signs[2].getPosition().y - 100);
	m_interPopUp[2].setOrigin(m_interPopUp[2].getLocalBounds().width / 2, m_interPopUp[2].getLocalBounds().height / 2);
	m_interPopUp[2].scale(0.5, 0.5);
}

void TutorialManager::update(b2Body *playerPos)
{
//First Sign
	if (playerPos->GetPosition().x * SCALE  >  m_signs[0].getPosition().x - 100 && playerPos->GetPosition().x * SCALE < m_signs[0].getPosition().x + 100)
	{
		m_showIntPopMove = true;
		m_showTutPopOne = true;
	}
	else
	{
		m_showIntPopMove = false;
		m_showTutPopOne = false;
		m_interPopUp[0].setTexture(m_interPopText);

	}

	if (m_showTutPopOne == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_interPopUp[0].setTexture(m_popTexture[0]);
		}
	}

//SECOND SIGN
	if (playerPos->GetPosition().x * SCALE > m_signs[1].getPosition().x - 100 && playerPos->GetPosition().x * SCALE < m_signs[1].getPosition().x + 100)
	{
		m_showIntPopJump = true;
		m_showTutPopTwo = true;
	}
	else
	{
		m_showIntPopJump = false;
		m_showTutPopTwo = false;
		m_interPopUp[1].setTexture(m_interPopText);

	}

	if (m_showTutPopTwo == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_interPopUp[1].setTexture(m_popTexture[1]);
		}
	}

//Third Sign
	if (playerPos->GetPosition().x * SCALE > m_signs[2].getPosition().x - 100 && playerPos->GetPosition().x * SCALE < m_signs[2].getPosition().x + 100)
	{
		m_showIntPopDash = true;
		m_showTutPopOne = true;
	}
	else
	{
		m_showIntPopDash = false;
		m_showTutPopOne = false;
		m_interPopUp[2].setTexture(m_interPopText);

	}

	if (m_showTutPopOne == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_interPopUp[2].setTexture(m_popTexture[2]);
		}
	}

}

void TutorialManager::render(sf::RenderWindow &t_window)
{
	if (m_showIntPopJump == true)
	{
		t_window.draw(m_interPopUp[1]);
	}

	if (m_showIntPopMove == true)
	{
		t_window.draw(m_interPopUp[0]);
	}

	if (m_showIntPopDash == true)
	{
		t_window.draw(m_interPopUp[2]);

	}

	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_signs[i]);
	}
}
