#include "PickUps.h"



PickUps::PickUps()
{
	image.loadFromFile("ASSETS/SPRITES/pickupSheetTwo.png");

	image.createMaskFromColor(sf::Color::White);

	// Create texture based on sf::Image
	if (!m_pickUpTexture.loadFromImage(image))
	{
		std::cout << " No Image Found " << std::endl;
	}

	addFrames(hover, 0, 0, 0, 18, 1.0f);

	//Adds the animation with their corresponding durations
	animator.addAnimation("hover", hover, sf::seconds(1.f));
}


PickUps::~PickUps()
{
}

void PickUps::setup(sf::Vector2f t_pos, b2World & t_world)
{
	//************
//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
//************
	m_pickupDef.position = { t_pos.x / SCALE , t_pos.y / SCALE };
	m_pickupDef.type = b2_dynamicBody;
	m_pickupBody = t_world.CreateBody(&m_pickupDef);

	m_pickupShape.SetAsBox((1.000000181f / 2) / SCALE, (40.f / 2) / SCALE);
	m_pickupFixtureDef.density = 1.0f;
	m_pickupFixtureDef.friction = 1.0f;
	m_pickupFixtureDef.shape = &m_pickupShape;
	m_pickupBody->CreateFixture(&m_pickupFixtureDef);
	m_pickupBody->SetUserData(&m_pickupNum);
	m_pickupBody->SetGravityScale(0.0f);

	m_pickUpSprite.setTexture(m_pickUpTexture);
	m_pickUpSprite.setOrigin(12.4f, 20.0f);
	m_pickUpSprite.setPosition(m_pickupBody->GetPosition().x*SCALE - 10, m_pickupBody->GetPosition().y*SCALE - 2);
}

void PickUps::update()
{


	if (!animator.isPlayingAnimation())
	{
		animator.playAnimation("hover");

	}

	

	// Update animator and apply current animation state to the sprite
	animator.update(frameClock.restart());
	animator.animate(m_pickUpSprite);
	

}

void PickUps::render(sf::RenderWindow & t_window)
{
	if (draw)
	{
		t_window.draw(m_pickUpSprite);
	}
}

void PickUps::destroy(b2World & t_world)
{
	if (m_pickupBody->IsActive())
	{
		m_pickupBody->SetActive(false);
		t_world.DestroyBody(m_pickupBody);
	}
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////ANIMATION FUNCTIONS////////////////////////////
/////////////////////////////////////////////////////////////////////////
//Add Animation to the Player
void PickUps::addFrames(thor::FrameAnimation & animation, int x, int y, int yFirst, int yLast, float duration)
{
	for (int i = 1; i < yLast; i++)
	{
		animation.addFrame(duration, sf::IntRect(16 * i, 0, 16, 45));
	}
}
