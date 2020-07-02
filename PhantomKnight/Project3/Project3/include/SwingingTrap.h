#ifndef SWINGINGTRAP
#define SWINGINGTRAP

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "Global.h"
#include "PendulumConnection.h"
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>
#include <iostream>
class SwingingTrap
{
public:
	SwingingTrap();
	~SwingingTrap();


	//Creates and Updates Sprite
	void createBoxPendulum(sf::Vector2f t_pos, b2World &t_world);
	void createBoxPendulumForHelp(sf::Vector2f t_pos, b2World &t_world);


	//Update
	void updateSprite(b2Body * body);

	void render(sf::RenderWindow &t_window);

	void destroy(b2World & t_world);

	void reset();

	b2Body* m_pendBody;
	b2BodyDef m_pendDef;
	b2PolygonShape m_pendShape;
	b2FixtureDef m_pendFixtureDef;

	sf::Vertex line[2];
	
	PendulumConnection m_connection;

	b2DistanceJointDef djd;
	float len = 120;

	float lenTwo = 300;

	sf::Vector2f angVector;
	float rotAngle = 0;




private:
	int m_pendNum = 4;
	int m_angle = 0;
	const b2Vec2 MAX_SPEED = { 50,0 };
	b2Vec2 m_speed = { 12,0 };
	sf::Sprite m_pend;
	sf::Texture m_pendTexture;

	bool m_rotRight = true;
	bool m_rotLeft = false;
};

#endif // !SWINGINGTRAP

