#ifndef PENDULUMCONNECTION
#define PENDULUMCONNECTION

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "Global.h"
#include <iostream>
class PendulumConnection
{
public:
	PendulumConnection();
	~PendulumConnection();

	void createBoxConnection(sf::Vector2f t_pos, b2World &t_world); // creates the connector to the pendulum in the game 
	void createBoxConnectionForHelp(sf::Vector2f t_pos, b2World &t_world);// creates the connector to the pendulum in the Help Screen 

	void render(sf::RenderWindow &t_window);

	b2Body* m_Body;
	b2BodyDef m_Def;
	b2PolygonShape m_Shape;
	b2FixtureDef m_FixtureDef;

	sf::Sprite m_con;
	sf::Texture m_texture;


	int m_ConNum = 4; // user data used for the collisions

};

#endif // !PENDULUMCONNECTION


