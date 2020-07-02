#ifndef CLOUDS
#define CLOUDS

#include "Box2D/Box2D.h"
#include <iostream>
#include "Global.h"
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>
#include <SFML/Graphics.hpp>
#include<limits>
      


class Clouds
{
public:
	Clouds();
	~Clouds();

	void update(sf::Vector2f pos);
	void render(sf::RenderWindow &t_window);

	void cloudOne();
	void cloudTwo();
	void cloudThree();

	//Used for the particles to do with the player
	sf::Texture m_particleTexture[3];

	//PARTICLES
	sf::Clock particleClock;
	thor::PolarVector2f velocity = { 0, -20.f };
	thor::FadeAnimation fader = { 0.1f, 0.1f };

	//Cloud One
	thor::ParticleSystem cloudOneSystem;
	thor::UniversalEmitter m_cloudOneEmitter;

	//Cloud One
	thor::ParticleSystem cloudTwoSystem;
	thor::UniversalEmitter m_cloudTwoEmitter;

	//Cloud One
	thor::ParticleSystem cloudThreeSystem;
	thor::UniversalEmitter m_cloudThreeEmitter;

	//starting pos of the clouds
	sf::Vector2f pos;

	//timer for the clouds
	sf::Time m_frameTime;

	
	bool paused = false;


	int cloudNum;

	//Rate of emmision
	float cloudEmissionRate = 0.2f;

};


#endif // !CLOUDS

