#include "PendulumConnection.h"



PendulumConnection::PendulumConnection()
{
	m_texture.loadFromFile("ASSETS/SPRITES/pendulumFrame.png");
}


PendulumConnection::~PendulumConnection()
{
}

void PendulumConnection::createBoxConnection(sf::Vector2f t_pos, b2World & t_world)
{
	m_Def.position = { (t_pos.x + 60) / SCALE, (t_pos.y - 120) / SCALE }; // sets the position 
	m_Def.type = b2_staticBody; // makes it a static body 
	m_Body = t_world.CreateBody(&m_Def); // sets the def to the body 

	m_Shape.SetAsBox((40 / 1.5) / SCALE, (50.f / 2) / SCALE); //sets the shape 
	m_FixtureDef.density = 1.0f;// sets the density 
	m_FixtureDef.friction = 1.0f; //sets the friction 
	m_FixtureDef.shape = &m_Shape; // sets this data to the shape 
	m_Body->CreateFixture(&m_FixtureDef);
	m_Body->SetUserData(&m_ConNum);


	m_con.setPosition(m_Body->GetPosition().x * SCALE + 117.5, m_Body->GetPosition().y * SCALE + 210);// sets the sprites position in relation to the bodies position 
	m_con.setOrigin(m_con.getLocalBounds().width, m_con.getLocalBounds().height); // sets the origin of the sprite 
	m_con.setScale(sf::Vector2f(2, 2)); // scales it 
	m_con.setTexture(m_texture); // applies texture 
}

void PendulumConnection::createBoxConnectionForHelp(sf::Vector2f t_pos, b2World & t_world)
{
	m_Def.position = { (t_pos.x - 200) / SCALE, (t_pos.y - 620) / SCALE };
	m_Def.type = b2_staticBody;
	m_Body = t_world.CreateBody(&m_Def);

	m_Shape.SetAsBox((40 / 1.5) / SCALE, (50.f / 2) / SCALE);
	m_FixtureDef.density = 1.0f;
	m_FixtureDef.friction = 1.0f;
	m_FixtureDef.shape = &m_Shape;
	m_Body->CreateFixture(&m_FixtureDef);
	m_Body->SetUserData(&m_ConNum);


	m_con.setPosition(m_Body->GetPosition().x * SCALE - 247.5, m_Body->GetPosition().y * SCALE - 210);
	m_con.setOrigin(m_con.getLocalBounds().width, m_con.getLocalBounds().height);
	m_con.setScale(sf::Vector2f(4, 4));
	m_con.setTexture(m_texture);
}

void PendulumConnection::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_con);

}
