#include "Clouds.h"



Clouds::Clouds()
{
	//Particles
// Load image that contains animation steps
	if (!m_particleTexture[0].loadFromFile("ASSETS/SPRITES/cloud1.png"))
	{
		std::cout << " No File Found " << std::endl;
	}
	if (!m_particleTexture[1].loadFromFile("ASSETS/SPRITES/cloud2.png"))
	{
		std::cout << " No File Found " << std::endl;
	}
	if (!m_particleTexture[2].loadFromFile("ASSETS/SPRITES/cloud3.png"))
	{
		std::cout << " No File Found " << std::endl;
	}

}


Clouds::~Clouds()
{
}

void Clouds::update(sf::Vector2f pos)
{
	sf::Time frameTime = particleClock.restart();

	if (!paused) // if its not paused then update the coulds position
	{
		cloudOneSystem.update(frameTime);
		cloudTwoSystem.update(frameTime);
		cloudThreeSystem.update(frameTime);
	}

	//Cloud One
	m_cloudOneEmitter.setParticlePosition(thor::Distributions::rect(pos, sf::Vector2f(0, 640)));
	m_cloudOneEmitter.setParticleVelocity(velocity);

	//Cloud Two
	m_cloudTwoEmitter.setParticlePosition(thor::Distributions::rect(pos, sf::Vector2f(0, 640)));
	m_cloudTwoEmitter.setParticleVelocity(velocity);

	//Cloud Three
	m_cloudThreeEmitter.setParticlePosition(thor::Distributions::rect(pos, sf::Vector2f(0, 640)));
	m_cloudThreeEmitter.setParticleVelocity(velocity);
}

void Clouds::render(sf::RenderWindow & t_window)
{
	// draw the cloud systems
	t_window.draw(cloudOneSystem);
	t_window.draw(cloudTwoSystem);
	t_window.draw(cloudThreeSystem);
}

void Clouds::cloudOne()
{

	// Create emitter
	m_cloudOneEmitter.setEmissionRate(cloudEmissionRate);
	m_cloudOneEmitter.setParticleLifetime(sf::seconds(40.0f));
	m_cloudOneEmitter.setParticleScale(sf::Vector2f(1, 1));
	m_cloudOneEmitter.setParticleRotation(0);


	// Create particle system, add reference to emitter
	cloudOneSystem.setTexture(m_particleTexture[0]);
	cloudOneSystem.addEmitter(thor::refEmitter(m_cloudOneEmitter));

	//sets the gradient at which to fade the clouds
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color(255, 255, 255);
	gradient[0.5f] = sf::Color(255, 255, 255);
	gradient[1.f] = sf::Color(255, 255, 255);


	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.20f, 0.20f);

	// Add particle affectors
	cloudOneSystem.addAffector(thor::AnimationAffector(colorizer));
	cloudOneSystem.addAffector(thor::AnimationAffector(fader));
	cloudOneSystem.addAffector(thor::ForceAffector(sf::Vector2f(10.f, 0.f)));
}

void Clouds::cloudTwo()
{
	// Create emitter
	m_cloudTwoEmitter.setEmissionRate(cloudEmissionRate);
	m_cloudTwoEmitter.setParticleLifetime(sf::seconds(40.0f));
	m_cloudTwoEmitter.setParticleScale(sf::Vector2f(1, 1));
	m_cloudTwoEmitter.setParticleRotation(0);


	// Create particle system, add reference to emitter
	cloudTwoSystem.setTexture(m_particleTexture[1]);
	cloudTwoSystem.addEmitter(thor::refEmitter(m_cloudTwoEmitter));
	
	//sets the gradient at which to fade the clouds
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color(255, 255, 255);
	gradient[0.5f] = sf::Color(255, 255, 255);
	gradient[1.f] = sf::Color(255, 255, 255);


	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	// Add particle affectors
	cloudTwoSystem.addAffector(thor::AnimationAffector(colorizer));
	cloudTwoSystem.addAffector(thor::AnimationAffector(fader));
	cloudTwoSystem.addAffector(thor::ForceAffector(sf::Vector2f(10.f, 0.f)));
}

void Clouds::cloudThree()
{
	// Create emitter
	m_cloudThreeEmitter.setEmissionRate(cloudEmissionRate);
	m_cloudThreeEmitter.setParticleLifetime(sf::seconds(40.0f));
	m_cloudThreeEmitter.setParticleScale(sf::Vector2f(1, 1));
	m_cloudThreeEmitter.setParticleRotation(0);


	// Create particle system, add reference to emitter
	cloudThreeSystem.setTexture(m_particleTexture[2]);
	cloudThreeSystem.addEmitter(thor::refEmitter(m_cloudThreeEmitter));

	//sets the gradient at which to fade the clouds
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color(255, 255, 255);
	gradient[0.5f] = sf::Color(255, 255, 255);
	gradient[1.f] = sf::Color(255, 255, 255);


	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	// Add particle affectors
	cloudThreeSystem.addAffector(thor::AnimationAffector(colorizer));
	cloudThreeSystem.addAffector(thor::AnimationAffector(fader));
	cloudThreeSystem.addAffector(thor::ForceAffector(sf::Vector2f(10.f, 0.f)));
}
