#include "DashParticle.h"



DashParticle::DashParticle()
{
	//Particles
	// Load image that contains animation steps
	if (!m_particleTexture.loadFromFile("ASSETS/SPRITES/dashP.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

	// Create emitter
	m_particleEmitter.setEmissionRate(30.f);
	m_particleEmitter.setParticleLifetime(sf::seconds(0.25f));
	m_particleEmitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	m_particleEmitter.setParticleScale(sf::Vector2f(0.125, 0.125));
	m_particleEmitter.setParticleRotation(-20);


	// Create particle system, add reference to emitter
	particleSystem.setTexture(m_particleTexture);
	particleSystem.addEmitter(thor::refEmitter(m_particleEmitter));

	//// Build color gradient (green -> teal -> blue)
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color::Black;
	gradient[0.5f] = sf::Color(198, 13, 0);
	gradient[1.f] = sf::Color::Black;


	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	// Add particle affectors
	particleSystem.addAffector(thor::AnimationAffector(colorizer));
	particleSystem.addAffector(thor::AnimationAffector(fader));
	particleSystem.addAffector(thor::TorqueAffector(10.f));
	particleSystem.addAffector(thor::ForceAffector(sf::Vector2f((30.f), 0.0f)));
}


DashParticle::~DashParticle()
{

}

void DashParticle::update(b2Body * body)
{

	pos = { (body->GetPosition().x * SCALE) + 10,(body->GetPosition().y * SCALE)};
	sf::Time frameTime = particleClock.restart();
	if (!paused)
	{
		particleSystem.update(frameTime);
	}
	// Set initial particle position and velocity, rotate vector randomly by maximal 10 degrees
	m_particleEmitter.setParticlePosition(thor::Distributions::rect(pos, sf::Vector2f(0,30)));
	m_particleEmitter.setParticleVelocity(velocity);
}

void DashParticle::render(sf::RenderWindow & t_window)
{
	t_window.draw(particleSystem);
}

void DashParticle::clearParticles()
{
	particleSystem.clearParticles();
}
