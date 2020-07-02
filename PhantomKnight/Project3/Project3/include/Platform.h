#ifndef PLATFORM
#define PLATFORM


#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Box2D/Box2D.h"
#include "Global.h"

class Platform
{
public:
	Platform();
	~Platform();

	void setup(sf::Vector2f t_pos, b2World &t_world);
	void render(sf::RenderWindow &t_window);
	void setAsIce();
	void setAsGrass();
	void destroy(b2World & t_world);


	//Ground
	b2BodyDef m_platformDef;
	b2Body* m_platformBody;
	b2PolygonShape m_platformShape;
	b2FixtureDef m_platformFixtureDef;


private:
	int m_platNum = 2;

	sf::Sprite m_base;
	sf::Texture m_baseTexture;
	sf::Texture m_iceBaseTexture;



};

#endif // !PLATFORM