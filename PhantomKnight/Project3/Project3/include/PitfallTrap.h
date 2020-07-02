#ifndef PITFALLTRAP
#define PITFALLTRAP

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "Global.h"
#include <iostream>
class PitfallTrap
{
public:
	PitfallTrap();
	~PitfallTrap();

	void createBoxSpikes(sf::Vector2f t_pos, b2World &t_world);
	void render(sf::RenderWindow &t_window);
	void destroy(b2World & t_world);



	int m_spikeNum = 3;
	int m_spikeSpacing = 12;

	sf::Sprite m_spikes[3];
	sf::Texture m_spikeTexture;

	//Ground
	b2BodyDef m_pitFallDef;
	b2Body* m_pitFallBody;
	b2PolygonShape m_pitFallShape;
	b2FixtureDef m_pitFallFixtureDef;

};

#endif // !PitfallTrap


