#include "VerticalWalls.h"



VerticalWalls::VerticalWalls()
{
	m_baseTexture.loadFromFile("ASSETS/SPRITES/wallSprite.png");
}


VerticalWalls::~VerticalWalls()
{
}

void VerticalWalls::setup(sf::Vector2f t_pos, b2World & t_world)
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	m_wallDef.position = { t_pos.x / SCALE , t_pos.y / SCALE };
	m_wallDef.type = b2_staticBody;
	m_wallBody = t_world.CreateBody(&m_wallDef);


	m_wallShape.SetAsBox((48.f / 2) / SCALE, (260.000000181f / 2) / SCALE);
	m_wallFixtureDef.density = 1.0f;
	m_wallFixtureDef.friction = 1.0f;
	m_wallFixtureDef.shape = &m_wallShape;
	m_wallBody->CreateFixture(&m_wallFixtureDef);
	m_wallBody->SetUserData(&m_wallNum);

	m_base.setTexture(m_baseTexture);
	//Have to divide the resolution by this to set origin 
	m_base.scale(0.619195047, 0.5);
	m_base.setOrigin(162.4f, 35.f);
	m_base.rotate(90);

	m_base.setPosition((m_wallBody->GetPosition().x + 0.1)*SCALE, (m_wallBody->GetPosition().y - 1)*SCALE);
}

void VerticalWalls::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_base);
}
