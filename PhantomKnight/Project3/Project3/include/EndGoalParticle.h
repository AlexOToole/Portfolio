#ifndef ENDGOALPARTICLE
#define ENDGOALPARTICLE

#include "Box2D/Box2D.h"
#include <iostream>
#include "Global.h"
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>
#include <SFML/Graphics.hpp>
#include<limits>

class EndGoalParticle
{
public:
	EndGoalParticle();
	~EndGoalParticle();

	void update(sf::Vector2f pos);
	void gameUpdate(b2Body * body);
	void render(sf::RenderWindow &t_window);
	void menuEffect();
	void endEffect();

	//Used for the particles to do with the player
	sf::Texture m_particleTexture;

	//PARTICLES
	sf::Clock particleClock;
	thor::ParticleSystem particleEnd;
	thor::UniversalEmitter m_particleEmitter;
	thor::PolarVector2f velocity = { 0, -20.f };
	thor::FadeAnimation fader = { 0.1f, 0.1f };

	sf::Vector2f pos;

	sf::Time m_frameTime;

	bool paused = false;

	bool menuE = false;
	bool endGameE = false;

};

#endif // !ENDGOALPARTICLE

