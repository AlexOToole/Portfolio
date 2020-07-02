#ifndef GROUND
#define GROUND

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Global.h"
#include <iostream>

class Ground
{
public:
	Ground();
	~Ground();
	void createBox(b2World &t_world);
	void render(sf::RenderWindow &t_window);



private:
	int m_groundNum = 0;

	//Sprites
	sf::Sprite m_ground;
	sf::Texture m_groundTexture;

	//Ground
	b2BodyDef m_groundDef;
	b2Body* m_groundBody;
	b2PolygonShape m_groundShape;
	b2FixtureDef m_groundFixtureDef;



};

#endif // !GROUND
