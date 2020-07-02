#ifndef DASHPARTICLE
#define DASHPARTICLE

#include "Box2D/Box2D.h"
#include <iostream>
#include "Global.h"
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>
#include <SFML/Graphics.hpp>
class DashParticle
{
public:
	DashParticle();
	~DashParticle();

	void update(b2Body * body);
	void render(sf::RenderWindow &t_window);
	void clearParticles();


	//Used for the particles to do with the player
	sf::Texture m_particleTexture;

	//PARTICLES
	sf::Clock particleClock;
	thor::ParticleSystem particleSystem;
	thor::UniversalEmitter m_particleEmitter;
	thor::PolarVector2f velocity = { -100.f, 15.f };
	thor::FadeAnimation fader = { 0.1f, 0.1f };

	sf::Vector2f pos;

	sf::Time m_frameTime;

	bool paused = false;
};

#endif // !DASHPARTICLE

