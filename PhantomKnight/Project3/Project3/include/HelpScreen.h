#ifndef HELPSCREEN
#define HELPSCREEN

#include <SFML/Graphics.hpp>
#include "UiLibrary.h"
#include "SwingingTrap.h"
#include "EndGoalParticle.h"
class HelpScreen
{
public:
	HelpScreen();
	~HelpScreen();

	void update(sf::Vector2f t_mousePos, bool t_clicked);
	void render(sf::RenderWindow &t_window);

	bool m_mainMenu = false;
private:
	static const int M_MAX_KEYS = 7;
	//ANIMATIONS
	sf::Clock m_frameClock;
	//Animation Frames
	thor::FrameAnimation m_hover;

	thor::Animator<sf::Sprite, std::string> m_animator;
	void addFrames(thor::FrameAnimation& animation, int x, int y, int yFirst, int yLast, float duration);
	sf::Sprite m_pickUpSprite;
	sf::Texture m_pickUpTexture;
	sf::Image m_image;
	Button m_exitButton;
	Label m_pickUpInstruct;
	EndGoalParticle Particle;
	sf::Texture m_spikeTexture;
	sf::Sprite m_spike;
	Label m_spikeInstruct;
	SwingingTrap m_swing;
	b2Vec2 gravity = { 0.0f,13.4f };
	Label m_helpText;

	//For the World of the Helpscreen
	float32 timeStep = 1 / 60.0f;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position
	b2World world{ gravity };
	Label m_swingInstruct;

};

#endif // !HELPSCREEN