#include "EndGoalParticle.h"



EndGoalParticle::EndGoalParticle()
{


	
}




EndGoalParticle::~EndGoalParticle()
{
}

void EndGoalParticle::update(sf::Vector2f pos)
{
	sf::Time frameTime = particleClock.restart();

	if (!paused)
	{
		particleEnd.update(frameTime);

	}


		//m_particleEmitter.setParticlePosition(pos);
		m_particleEmitter.setParticlePosition(thor::Distributions::rect(pos, sf::Vector2f(1920, 0)));
		m_particleEmitter.setParticleVelocity(velocity);

}

void EndGoalParticle::gameUpdate(b2Body * body)
{
	sf::Time frameTime = particleClock.restart();

	if (!paused)
	{
		particleEnd.update(frameTime);

	}

	//m_particleEmitter.setParticlePosition(pos);
	m_particleEmitter.setParticlePosition(thor::Distributions::rect(sf::Vector2f(body->GetPosition().x  * SCALE, body->GetPosition().y * SCALE), sf::Vector2f(100, 0)));
	m_particleEmitter.setParticleVelocity(velocity);
}

void EndGoalParticle::render(sf::RenderWindow & t_window)
{
	t_window.draw(particleEnd);
}

void EndGoalParticle::menuEffect()
{
	//Particles
// Load image that contains animation steps
	if (!m_particleTexture.loadFromFile("ASSETS/SPRITES/starTwo.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	// Create emitter
	m_particleEmitter.setEmissionRate(100.f);
	m_particleEmitter.setParticleLifetime(sf::seconds(5.0f));
	//m_particleEmitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	m_particleEmitter.setParticleScale(sf::Vector2f(1, 1));
	m_particleEmitter.setParticleRotation(0);


	// Create particle system, add reference to emitter

	particleEnd.setTexture(m_particleTexture);
	particleEnd.addEmitter(thor::refEmitter(m_particleEmitter));

	// Build color gradient (green -> teal -> blue)
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color(255, 0, 0);
	gradient[0.5f] = sf::Color(0, 255, 0);
	gradient[1.f] = sf::Color(0, 0, 255);


	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	// Add particle affectors
	particleEnd.addAffector(thor::AnimationAffector(colorizer));
	particleEnd.addAffector(thor::AnimationAffector(fader));
	particleEnd.addAffector(thor::TorqueAffector(20));
	particleEnd.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 250.f)));
}

void EndGoalParticle::endEffect()
{		
	//Particles
// Load image that contains animation steps
		if (!m_particleTexture.loadFromFile("ASSETS/SPRITES/particle.png"))
		{
			std::cout << " No File Found " << std::endl;
		}

		// Create emitter
		m_particleEmitter.setEmissionRate(100.f);
		m_particleEmitter.setParticleLifetime(sf::seconds(5.0f));
		//m_particleEmitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
		m_particleEmitter.setParticleScale(sf::Vector2f(0.25, 0.25));
		m_particleEmitter.setParticleRotation(0);


		// Create particle system, add reference to emitter

		particleEnd.setTexture(m_particleTexture);
		particleEnd.addEmitter(thor::refEmitter(m_particleEmitter));

		// Build color gradient (green -> teal -> blue)
		thor::ColorGradient gradient;
		gradient[0.0f] = sf::Color(255, 240, 206);
		gradient[0.5f] = sf::Color(255, 231, 146);
		gradient[1.f] = sf::Color(255, 173, 52);

		// Create color and fade in/out animations
		thor::ColorAnimation colorizer(gradient);
		thor::FadeAnimation fader(0.1f, 0.1f);

		// Add particle affectors
		particleEnd.addAffector(thor::AnimationAffector(colorizer));
		particleEnd.addAffector(thor::AnimationAffector(fader));
		particleEnd.addAffector(thor::TorqueAffector(20));
		particleEnd.addAffector(thor::ForceAffector(sf::Vector2f(0.f, -250.f)));
}
