#ifndef BOUNDARY
#define BOUNDARY

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Box2D/Box2D.h"
#include "Global.h"


class Boundary
{
public:
	Boundary();
	~Boundary();

	void setup(sf::Vector2f t_pos,sf::Vector2f t_posTwo, b2World &t_world); // creates an invisible barrier that makes sure the player cannot jump out of the map 


	int m_boundaryNum = 6; // nmber that is passed as user data for collisions


	//Ground
	b2BodyDef m_boundaryDef[2]; // array of boundary defs taht set up the properties of each barrier
	b2Body* m_boundaryBody[2]; // Array fo boundarty bodies that the def is applied too
	b2PolygonShape m_boundaryShape;
	b2FixtureDef m_boundaryFixtureDef;
};

#endif // !BOUNDARY

