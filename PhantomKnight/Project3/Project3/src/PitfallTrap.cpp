#include "PitfallTrap.h"



PitfallTrap::PitfallTrap()
{
	m_spikeTexture.loadFromFile("ASSETS/SPRITES/newSpike.png");
}


PitfallTrap::~PitfallTrap()
{
}

void PitfallTrap::createBoxSpikes(sf::Vector2f t_pos, b2World &t_world)
{
	m_pitFallDef.position = { t_pos.x / SCALE, t_pos.y / SCALE };
	m_pitFallDef.type = b2_staticBody;
	m_pitFallBody = t_world.CreateBody(&m_pitFallDef);

	m_pitFallShape.SetAsBox((30 / 1.5) / SCALE, (35.f / 2) / SCALE);
	m_pitFallFixtureDef.density = 1.0f;
	m_pitFallFixtureDef.friction = 1.0f;
	m_pitFallFixtureDef.shape = &m_pitFallShape;
	m_pitFallBody->CreateFixture(&m_pitFallFixtureDef);
	m_pitFallBody->SetUserData(&m_spikeNum);

	for (int i = 0; i < 3; i++)
	{
		m_spikes[i].setTexture(m_spikeTexture);
		m_spikes[i].scale(0.05, 0.05);
		m_spikes[i].setOrigin(400, 377.5);
		m_spikes[i].setPosition((m_pitFallBody->GetPosition().x * SCALE) + i * m_spikeSpacing, m_pitFallBody->GetPosition().y * SCALE);
	}
}

void PitfallTrap::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 3; i++)
	{
		t_window.draw(m_spikes[i]);

	}
}

void PitfallTrap::destroy(b2World & t_world)
{
	if (m_pitFallBody->IsActive())
	{
		m_pitFallBody->SetActive(false);
		t_world.DestroyBody(m_pitFallBody);
	}
}
