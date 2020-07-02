#include "SwingingTrap.h"



SwingingTrap::SwingingTrap()
{
	m_pendTexture.loadFromFile("ASSETS/SPRITES/pendulum2.png");
}


SwingingTrap::~SwingingTrap()
{
}

void SwingingTrap::createBoxPendulum(sf::Vector2f t_pos, b2World & t_world)
{
	m_connection.createBoxConnection(t_pos, t_world);

	m_pendDef.position = { t_pos.x / SCALE, t_pos.y / SCALE };
	m_pendDef.type = b2_dynamicBody;
	m_pendBody = t_world.CreateBody(&m_pendDef);

	m_pendShape.SetAsBox((65 / 1.5) / SCALE, (65/ 2) / SCALE);
	m_pendFixtureDef.density = 1.0f;
	m_pendFixtureDef.friction = 1.0f;
	m_pendFixtureDef.shape = &m_pendShape;
	m_pendBody->CreateFixture(&m_pendFixtureDef);
	m_pendBody->SetUserData(&m_pendNum);

	m_pend.setTexture(m_pendTexture);
	m_pend.setOrigin(112, 102);
	m_pend.setPosition(m_pendBody->GetPosition().x * SCALE, m_pendBody->GetPosition().y * SCALE);
	m_pend.setRotation(0);
	m_pend.setScale(0.4, 0.4);

	//Use polar angle to return a vector converted frmo an angle 
	// use unit vector to normalize it 

	djd.bodyA = m_pendBody;
	djd.bodyB = m_connection.m_Body;

	djd.length = len / SCALE;

	djd.frequencyHz = 5; // controls the spring and oscillation
	djd.dampingRatio = 0.025;

	t_world.CreateJoint(&djd);

	line[0].position = sf::Vector2f(m_pendBody->GetPosition().x * SCALE, m_pendBody->GetPosition().y * SCALE);
	line[1].position = sf::Vector2f(m_connection.m_Body->GetPosition().x * SCALE, m_connection.m_Body->GetPosition().y * SCALE);

	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;


	angVector.x = line[1].position.x - line[0].position.x;
	angVector.y = line[1].position.y - line[0].position.y;

	thor::unitVector(angVector);



}

void SwingingTrap::createBoxPendulumForHelp(sf::Vector2f t_pos, b2World & t_world)
{
	m_connection.createBoxConnectionForHelp(t_pos, t_world);

	m_pendDef.position = { t_pos.x / SCALE, t_pos.y / SCALE };
	m_pendDef.type = b2_dynamicBody;
	m_pendBody = t_world.CreateBody(&m_pendDef);

	m_pendShape.SetAsBox((65 / 1.5) / SCALE, (65 / 2) / SCALE);
	m_pendFixtureDef.density = 1.0f;
	m_pendFixtureDef.friction = 1.0f;
	m_pendFixtureDef.shape = &m_pendShape;
	m_pendBody->CreateFixture(&m_pendFixtureDef);
	m_pendBody->SetUserData(&m_pendNum);

	m_pend.setTexture(m_pendTexture);
	m_pend.setOrigin(112, 102);
	m_pend.setPosition(m_pendBody->GetPosition().x * SCALE, m_pendBody->GetPosition().y * SCALE);
	m_pend.setRotation(0);
	//m_pend.setScale(0.4, 0.4);

	//Use polar angle to return a vector converted frmo an angle 
	// use unit vector to normalize it 

	djd.bodyA = m_pendBody;
	djd.bodyB = m_connection.m_Body;

	djd.length = lenTwo / SCALE;

	djd.frequencyHz = 5; // controls the spring and oscillation
	djd.dampingRatio = 0.025;

	t_world.CreateJoint(&djd);

	line[0].position = sf::Vector2f(m_pendBody->GetPosition().x * SCALE, m_pendBody->GetPosition().y * SCALE);
	line[1].position = sf::Vector2f(m_connection.m_Body->GetPosition().x * SCALE, m_connection.m_Body->GetPosition().y * SCALE);

	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;


	angVector.x = line[1].position.x - line[0].position.x;
	angVector.y = line[1].position.y - line[0].position.y;

	thor::unitVector(angVector);
}


void SwingingTrap::updateSprite(b2Body * body)
{
	m_pend.setPosition(m_pendBody->GetPosition().x * SCALE, (m_pendBody->GetPosition().y)* SCALE);
	line[0].position = sf::Vector2f(m_pendBody->GetPosition().x * SCALE, m_pendBody->GetPosition().y * SCALE);


	angVector.x = line[1].position.x - line[0].position.x;
	angVector.y = line[1].position.y - line[0].position.y;
	thor::unitVector(angVector);

	rotAngle = thor::polarAngle(angVector);

	rotAngle = rotAngle * -1;
	

	if (rotAngle < 20)
	{
		m_rotLeft = false;
		m_rotRight = true;
	}

	if (rotAngle > 150)
	{
		m_rotLeft = true;
		m_rotRight = false;
	}

	if (m_rotRight == true)
	{
		m_pendBody->ApplyForceToCenter(b2Vec2(24, 0), false);
	}

	if (m_rotLeft == true)
	{
		m_pendBody->ApplyForceToCenter(b2Vec2(-24, 0), false);
	}
}

void SwingingTrap::render(sf::RenderWindow & t_window)
{
	m_connection.render(t_window);
	t_window.draw(m_pend);
	t_window.draw(line, 2, sf::Lines);

}

void SwingingTrap::destroy(b2World & t_world)
{
	if (m_pendBody->IsActive())
	{
		m_pendBody->SetActive(false);
		t_world.DestroyBody(m_pendBody);
	}

	if (m_connection.m_Body->IsActive())
	{
		m_connection.m_Body->SetActive(false);
		t_world.DestroyBody(m_connection.m_Body);
	}
}

void SwingingTrap::reset()
{
	rotAngle = 0;
	len = 120;
	m_angle = 0;

	m_rotRight = true;
	m_rotLeft = false;

}
