#include "Ground.h"



Ground::Ground()
{
	m_groundTexture.loadFromFile("ASSETS/SPRITES/groundSprite.png");
}

Ground::~Ground()
{
}

void Ground::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_ground);
}

void Ground::createBox(b2World & t_world)
{

	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	m_groundDef.position = b2Vec2(-1000 / SCALE, 730 / SCALE); //sets the position 
	m_groundDef.type = b2_staticBody; //creates the body
	m_groundBody = t_world.CreateBody(&m_groundDef); // sets the bodies data 

	m_groundShape.SetAsBox((11000 / 2) / SCALE, (5.f / 2) / SCALE); //sets the shape 
	m_groundFixtureDef.density = 1.0f; // set density
	m_groundFixtureDef.friction = 4.0f;//set friction
	m_groundFixtureDef.shape = &m_groundShape; // sets shape
	m_groundBody->CreateFixture(&m_groundFixtureDef);
	m_groundBody->SetUserData(&m_groundNum);

	m_ground.setTexture(m_groundTexture);

	m_ground.setPosition(m_groundBody->GetPosition().x*SCALE - 100, m_groundBody->GetPosition().y*SCALE - 710);
	m_ground.scale(3.2, 1);
}

