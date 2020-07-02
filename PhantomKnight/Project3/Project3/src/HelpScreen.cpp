#include "HelpScreen.h"



HelpScreen::HelpScreen()
{
	SwingingTrap();
	m_spikeTexture.loadFromFile("ASSETS/SPRITES/newSpike.png");
	m_image.loadFromFile("ASSETS/SPRITES/pickupSheetTwo.png");

	m_image.createMaskFromColor(sf::Color::White);

	// Create texture based on sf::Image
	if (!m_pickUpTexture.loadFromImage(m_image))
	{
		std::cout << " No Image Found " << std::endl;
	}

	addFrames(m_hover, 0, 0, 0, 18, 1.0f);

	//Adds the animation with their corresponding durations
	m_animator.addAnimation("hover", m_hover, sf::seconds(1.f));
	m_exitButton.setUp(sf::Vector2f(3840 / 2, 2020), sf::Vector2f(600, 120), sf::Color::Black, sf::Color(190, 90, 54));
	m_exitButton.setString("Exit");
	m_pickUpSprite.setTexture(m_pickUpTexture);
	m_pickUpSprite.setScale(sf::Vector2f(m_pickUpSprite.getScale().x * 2, m_pickUpSprite.getScale().y * 2));
	m_pickUpSprite.setOrigin(24.8f, 40.0f);
	m_pickUpSprite.setPosition(sf::Vector2f(800, 300));

	m_pickUpInstruct.setString("This is the dash pickup, It can be found around the map \n              collect it to earn an extra dash move");
	m_pickUpInstruct.setPosition(sf::Vector2f(800, 370));

	m_spike.setTexture(m_spikeTexture);
	m_spike.setScale(0.5, 0.5);
	m_spike.setOrigin(m_spike.getLocalBounds().width / 2, m_spike.getLocalBounds().height / 2);
	m_spike.setPosition(sf::Vector2f(800, 1500));

	m_spikeInstruct.setString("This is the spike trap, If you fall on this \n                           you die!");
	m_spikeInstruct.setPosition(sf::Vector2f(800, 1760));

	m_swing.createBoxPendulumForHelp(sf::Vector2f(3200, 1700), world);
	m_swingInstruct.setString("This is the pendulum trap, The goal is to run under it \n                            if it hits you, you die!");
	m_swingInstruct.setPosition(sf::Vector2f(3000, 1760));
	Particle.menuEffect();
	m_helpText.setCharacterSize(64);
	m_helpText.setColor(sf::Color(190, 90, 54));
	m_helpText.setString("Help");
	m_helpText.setPosition(sf::Vector2f((3840 / 2), 200));
}


HelpScreen::~HelpScreen()
{
}

void HelpScreen::update(sf::Vector2f t_mousePos, bool t_clicked)
{
	world.Step(timeStep, velocityIterations, positionIterations);

	Particle.update(sf::Vector2f(1920, 0));
	if (m_exitButton.isHighlighted(t_mousePos))
	{
		if (t_clicked)
		{
			m_mainMenu = true;
		}
	}
	if (!m_animator.isPlayingAnimation())
	{
		m_animator.playAnimation("hover");

	}
	// Update animator and apply current animation state to the sprite
	m_animator.update(m_frameClock.restart());
	m_animator.animate(m_pickUpSprite);
	m_swing.updateSprite(m_swing.m_pendBody);
}

void HelpScreen::render(sf::RenderWindow & t_window)
{
	t_window.clear(sf::Color(114, 148, 138));
	m_helpText.render(t_window);
	Particle.render(t_window);
	t_window.draw(m_pickUpSprite);
	m_pickUpInstruct.render(t_window);
	t_window.draw(m_spike);
	m_spikeInstruct.render(t_window);
	m_swing.render(t_window);
	m_swingInstruct.render(t_window);
	m_exitButton.render(t_window);
}

void HelpScreen::addFrames(thor::FrameAnimation & animation, int x, int y, int yFirst, int yLast, float duration)
{
	for (int i = 1; i < yLast; i++)
	{
		animation.addFrame(duration, sf::IntRect(16 * i, 0, 16, 45));
	}
}
