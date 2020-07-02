#ifndef VERTICALWALLS
#define VERTICALWALLS

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Box2D/Box2D.h"
#include "Global.h"

class VerticalWalls
{
public:
	VerticalWalls();
	~VerticalWalls();

	void setup(sf::Vector2f t_pos, b2World &t_world);
	void render(sf::RenderWindow &t_window);

private:
	int m_wallNum = 5;

	sf::Sprite m_base;
	sf::Texture m_baseTexture;

	//Ground
	b2BodyDef m_wallDef;
	b2Body* m_wallBody;
	b2PolygonShape m_wallShape;
	b2FixtureDef m_wallFixtureDef;
};

#endif // !VERTICALWALLS

