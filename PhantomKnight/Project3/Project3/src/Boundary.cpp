#include "Boundary.h"



Boundary::Boundary()
{
}


Boundary::~Boundary()
{
}

void Boundary::setup(sf::Vector2f t_pos, sf::Vector2f t_posTwo, b2World & t_world)
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	m_boundaryDef[0].position = { t_pos.x / SCALE , t_pos.y / SCALE }; // position the boundary 
	m_boundaryDef[0].type = b2_staticBody; // creates it as a staic body so external forces will not change it 
	m_boundaryBody[0] = t_world.CreateBody(&m_boundaryDef[0]); // applies the def to the body

	m_boundaryDef[1].position = { t_posTwo.x / SCALE , t_posTwo.y / SCALE };  // position the boundary 
	m_boundaryDef[1].type = b2_staticBody;// creates it as a staic body so external forces will not change it 
	m_boundaryBody[1] = t_world.CreateBody(&m_boundaryDef[1]); // applies the def to the body


	m_boundaryShape.SetAsBox((48.f / 2) / SCALE, (1000.000000181f / 2) / SCALE); // sets up the shape of the bounding box
	m_boundaryFixtureDef.density = 1.0f; 
	m_boundaryFixtureDef.friction = 1.0f;
	m_boundaryFixtureDef.shape = &m_boundaryShape; //applies the shape to the fixture 
	m_boundaryBody[0]->CreateFixture(&m_boundaryFixtureDef); //creates the body in the shape of the fixture
	m_boundaryBody[0]->SetUserData(&m_boundaryNum); //sets the user data for the collisions 

	m_boundaryBody[1]->CreateFixture(&m_boundaryFixtureDef); //creates the body in the shape of the fixture
	m_boundaryBody[1]->SetUserData(&m_boundaryNum);//sets the user data for the collisions 

}


