#include "Platform.h"


Platform::Platform()
{
	m_baseTexture.loadFromFile("ASSETS/SPRITES/platform.png");
}


Platform::~Platform()
{
	//m_platformBody->GetWorld()->DestroyBody(m_platformBody);
}

void Platform::setup(sf::Vector2f t_pos, b2World &t_world)
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	m_platformDef.position = { t_pos.x / SCALE , t_pos.y / SCALE };
	m_platformDef.type = b2_staticBody;
	m_platformBody = t_world.CreateBody(&m_platformDef);

	m_platformShape.SetAsBox((230.000000181f / 2) / SCALE, (26.f / 2) / SCALE);
	m_platformFixtureDef.density = 1.0f;
	m_platformFixtureDef.friction = 1.0f;
	m_platformFixtureDef.shape = &m_platformShape;
	m_platformBody->CreateFixture(&m_platformFixtureDef);
	m_platformBody->SetUserData(&m_platNum);

	m_base.setTexture(m_baseTexture);
	//Have to divide the resolution by this to set origin 
	m_base.setScale(0.619195047, 0.4);
	m_base.setOrigin(162.4f, 35.f);
	m_base.setPosition(m_platformBody->GetPosition().x*SCALE - 10, m_platformBody->GetPosition().y*SCALE - 2);
}

void Platform::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_base);
}

void Platform::setAsIce()
{
	m_platformFixtureDef.friction = 0.0f; //sets the platform to have no friction 
	m_platformBody->CreateFixture(&m_platformFixtureDef); // Sets this new property 
	m_baseTexture.loadFromFile("ASSETS/SPRITES/iceBase.png"); // changes the sprite 
}

void Platform::setAsGrass()
{
	m_platformFixtureDef.friction = 1.0f;
	m_platformBody->CreateFixture(&m_platformFixtureDef);
	m_baseTexture.loadFromFile("ASSETS/SPRITES/platform.png");
}

void Platform::destroy(b2World & t_world)
{
	if (m_platformBody->IsActive())
	{
		m_platformBody->SetActive(false);
		t_world.DestroyBody(m_platformBody);
	}
}


