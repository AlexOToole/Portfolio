#ifndef PICKUPS
#define PICKUPS
#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Box2D/Box2D.h"
#include "Global.h"
#include <Thor/Animations.hpp>

class PickUps
{
public:
	PickUps();
	~PickUps();

	void setup(sf::Vector2f t_pos, b2World &t_world);
	void update();
	void render(sf::RenderWindow &t_window);
	void destroy(b2World & t_world);




	//Ground
	b2BodyDef m_pickupDef;
	b2Body* m_pickupBody;
	b2PolygonShape m_pickupShape;
	b2FixtureDef m_pickupFixtureDef;

	//ANIMATIONS
	sf::Clock frameClock;
	//Animation Frames
	thor::FrameAnimation hover;

	thor::Animator<sf::Sprite, std::string> animator;
	void addFrames(thor::FrameAnimation& animation, int x, int y, int yFirst, int yLast, float duration);

	bool draw = true;


private:
	int m_pickupNum = 7; //user data number 

	sf::Sprite m_pickUpSprite;
	sf::Texture m_pickUpTexture;
	sf::Image image;
	
};

#endif // !PICKUPS
