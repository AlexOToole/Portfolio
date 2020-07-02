#include "Player.h"



Player::Player()
{
	m_dashTimer = 0;
	m_jumpCount = 0;
	m_dashCoolDown = 0;
	m_lengthOfDash = 0;
	m_numberOfDashes = 2;
	m_playerShown = true;
	m_movingRight = true;
	ParticleSystem();
	DashParticle();



	//Animations
		// Load image that contains animation steps
	if (!image.loadFromFile("ASSETS/SPRITES/SPRITESHEET.png"))
	{
		std::cout << " No File Found " << std::endl;
	}
	image.createMaskFromColor(sf::Color::White);

	// Create texture based on sf::Image
	if (!m_Texture.loadFromImage(image))
	{
		std::cout << " No Image Found " << std::endl;
	}

	//Creates frame for each of the animations
	addFrame(runRight, 0, 1, 0, 19, 1.0f);
	addFrame(jumpRight, 0, 0, 0, 24, 1.0f);
	addFrame(idleRight, 0, 2, 0, 24, 1.0f);

	//Creates Reverse frames
	addReverseFrame(runLeft, 0, 1, 0, 19, 1.0f);
	addReverseFrame(jumpLeft, 0, 0, 0, 24, 1.0f);
	addReverseFrame(idleLeft, 0, 2, 0, 24, 1.0f);

	//Adds the animation with their corresponding durations
	animator.addAnimation("runRight", runRight, sf::seconds(1.f));
	animator.addAnimation("runLeft", runLeft, sf::seconds(1.f));

	animator.addAnimation("jumpRight", jumpRight, sf::seconds(1.5f));
	animator.addAnimation("jumpLeft", jumpLeft, sf::seconds(1.5f));

	animator.addAnimation("idleRight", idleRight, sf::seconds(1.0f));
	animator.addAnimation("idleLeft", idleLeft, sf::seconds(1.0f));


}


Player::~Player()
{
}


void Player::createBoxPlayer(b2World  &world)
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	m_bodyDef.position = b2Vec2(-740 / SCALE, 650 / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_playerBody = world.CreateBody(&m_bodyDef);

	m_shape.SetAsBox((64.f / 2) / SCALE, (70.f / 2) / SCALE);
	m_fixtureDef.density = m_density;
	m_fixtureDef.friction = m_friction;
	m_fixtureDef.shape = &m_shape;
	m_playerBody->CreateFixture(&m_fixtureDef);
	m_playerBody->SetFixedRotation(true);

	m_sprite.setTexture(m_Texture);
	m_sprite.setOrigin(32.f, 39.5f);
	m_sprite.setPosition(m_playerBody->GetPosition().x * SCALE, m_playerBody->GetPosition().y*SCALE);
}


void Player::updateSprite(b2Body * body)
{
	movingParticles.update(m_playerBody);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_jumped == true)
	{
		movingParticles.clearParticles();
	}

	//Animations
		//If no other animation is playing then play the idle animation
	if (!animator.isPlayingAnimation())
	{
		if (m_movingLeft == true)//if the last direction you moved was left the play the idle left animation
		{
			animator.playAnimation("idleLeft");

		}
		if (m_movingRight == true)
		{
			animator.playAnimation("idleRight");
		}
	}

	if (m_floating != true) // if the player is not floating 
	{
		//Movement
			//Moving Left to right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (!m_jumped)
			{
				if (animator.getPlayingAnimation() != "runRight")
				{
					animator.playAnimation("runRight");
				}
			}
			moveRight(m_playerBody);
		}
		else if (m_movingRight == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_jumped == false)
		{
			if (animator.getPlayingAnimation() != "idleRight")//if the current animation is not running left 
			{
				animator.playAnimation("idleRight");
			}
		}



		//Moving Right to Left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (!m_jumped)
			{
				if (animator.getPlayingAnimation() != "runLeft")//if the current animation is not running left 
				{
					animator.playAnimation("runLeft");//Play run left animation
				}
			}
			moveLeft(m_playerBody);//Then move after all these
		}
		else if (m_movingLeft == true && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_jumped == false)
		{
			if (animator.getPlayingAnimation() != "idleLeft")//if the current animation is not running left 
			{
				animator.playAnimation("idleLeft");
			}
		}


		//Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (m_jumpCount < MAX_JUMPS) // if the current count of jumps is less than the max 
			{
				// If a certain amount of time has passed  
				m_jumped = true; //sets jumped to true 

				if (m_jumped && m_jumpCount == 0) //if jumped is true and the count is 0
				{
					m_jumpCount += 1; // increment count 
					moveUp(m_playerBody); //jump 

					//Checks the right animation to play 
					if (m_movingRight)
					{
						animator.stopAnimation();
						animator.playAnimation("jumpRight");
					}
					if (m_movingLeft)
					{
						animator.stopAnimation();
						animator.playAnimation("jumpLeft");
					}
				}

				//if the player is starting to fall 
				if (m_playerBody->GetLinearVelocity().y >= -0.1)
				{
					if (m_jumped == true && m_jumpCount == 1)
					{
						m_playSecondJump = true; // playes the second jump sound 
						m_jumpCount += 1; //increases jump count 
						m_playerBody->SetLinearVelocity(b2Vec2(m_playerBody->GetLinearVelocity().x, 0)); // sets the velocity back to 0
						moveUp(m_playerBody); // jump

						//plays relevant animation 
						if (m_movingRight)
						{
							animator.stopAnimation();
							animator.playAnimation("jumpRight");
						}
						if (m_movingLeft)
						{
							animator.stopAnimation();
							animator.playAnimation("jumpLeft");
						}
					}
				}

			}
		}

		//increments timer to correctly play sounds 
		if (m_jumped == true)
		{
			m_jumpTimer++;
		}
		//plays the first jump sound 
		if (m_jumpTimer >= 1 && m_jumpTimer <= 20)
		{
			m_playJumpSound = true;
		}
		//turns off the jump sound after a certain time 
		if (m_jumpTimer > 20)
		{
			m_playJumpSound = false;
		}

		//increment second timer
		if (m_playSecondJump == true)
		{
			m_jumpTimerTwo++;
		}

		if (m_jumpTimerTwo >= 1 && m_jumpTimerTwo <= 20)
		{
			m_playJumpSound = true;
		}
		if (m_jumpTimerTwo > 20)
		{
			m_playJumpSound = false;
		}



		//Resets the Jump count of the player
		if (m_playerBody->GetLinearVelocity().y == 0)
		{
			m_jumpCount = 0;
			m_jumpTimer = 0;
			m_jumpTimerTwo = 0;
			m_jumped = false;
			m_playSecondJump = false;
		}

		//Dashing
		if (m_dashCoolDown <= 0)
		{
			if (m_numberOfDashes > 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					m_dashing = true;
					m_playerShown = false; // stops the player being rendered 
					dash(m_playerBody); //dash 
					m_numberOfDashes--; // decrement players dashes 
					m_dashCoolDown = 250; //sets the cooldown 
					m_dashTimer = 100; // length of the dash 

				}
			}
		}

		if (m_dashTimer <= 0)
		{
			m_dashing = false; // sets the dash to be over 
			m_playerShown = true; //redraws the player 
		}
		else
		{
			movingParticles.clearParticles();

			//draw the particles after he dash
			if (m_movingRight)
			{
				dashParticles.update(m_playerBody);
			}
			if (m_movingLeft)
			{
				dashParticles.update(m_playerBody);
			}

		}

		//Cooldowns
		m_dashCoolDown--;
		m_dashTimer--;

	}


	//Setting Positions and rotations after movement
	m_sprite.setPosition(m_playerBody->GetPosition().x * SCALE, m_playerBody->GetPosition().y * SCALE);
	m_sprite.setRotation(m_playerBody->GetAngle() * 180 / b2_pi);


	// Update animator and apply current animation state to the sprite
	animator.update(frameClock.restart());
	animator.animate(m_sprite);
}

void Player::render(sf::RenderWindow &window)
{
	if (m_playerShown)
	{
		window.draw(m_sprite);
	}
	else
	{
		dashParticles.render(window);
	}


	if (!m_playerBody->GetLinearVelocity().x == 0)
	{
		movingParticles.render(window);
	}


}

//Gets the players position on screen
b2Vec2 Player::getPosition()
{
	return m_playerBody->GetPosition();
}

//////MOVEMENT FUNCTIONS
//Move Player Right
void Player::moveRight(b2Body * body)
{
	if (body->GetLinearVelocity().x < MAX_SPEED.x)
	{
		body->ApplyLinearImpulse(m_speed, body->GetWorldCenter(), true);
		if (body->GetLinearVelocity().x == MAX_SPEED.x)
		{
			body->SetLinearVelocity(MAX_SPEED);
		}
	}
	m_movingRight = true;
	m_movingLeft = false;
}

//Move Player Left
void Player::moveLeft(b2Body * body)
{
	if (body->GetLinearVelocity().x > -MAX_SPEED.x)
	{
		body->ApplyLinearImpulse(-m_speed, body->GetWorldCenter(), true);
		if (body->GetLinearVelocity().x == -MAX_SPEED.x)
		{
			body->SetLinearVelocity(-MAX_SPEED);
		}
	}

	m_movingRight = false;
	m_movingLeft = true;
}

//Move Player Up
void Player::moveUp(b2Body * body)
{
	body->ApplyLinearImpulse(m_jumpHeight, body->GetWorldCenter(), true);
}

//Players Dash
void Player::dash(b2Body * body)
{
	if (m_movingLeft == true)
	{
		body->ApplyLinearImpulse(-m_dashSpeed, body->GetWorldCenter(), true);
	}
	if (m_movingRight == true)
	{
		body->ApplyLinearImpulse(m_dashSpeed, body->GetWorldCenter(), true);

	}

}

//float up for the end goal 
void Player::floatUp(b2Body * body)
{
	body->SetGravityScale(-0.2f);
	m_floating = true;
}

//increase player dashes 
void Player::increaseDashes()
{
	if (m_numberOfDashes < 3)
	{
		m_numberOfDashes++;
	}
}

//resets the players pos when a level is won
void Player::reset()
{
	m_playerBody->SetLinearVelocity(b2Vec2(0, 0));
	m_playerBody->SetTransform(b2Vec2(-740 / SCALE, 640 / SCALE), m_playerBody->GetAngle());
	m_playerBody->SetGravityScale(1.0f);
	m_numberOfDashes = 3;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////ANIMATION FUNCTIONS////////////////////////////
/////////////////////////////////////////////////////////////////////////
//Add Animation to the Player
void Player::addFrame(thor::FrameAnimation & animation, int x, int y, int yFirst, int yLast, float duration)
{
	//const int step = (yFirst < yLast) ? +1 : -1;
	//yLast += step;

	//for (int y = yFirst; y != yLast; y += step)
	//	animation.addFrame(duration, sf::IntRect(64 * x, 74 * y, 64, 74));



	for (int i = 0; i < yLast; i++)
	{
		animation.addFrame(duration, sf::IntRect(64 * i, 78 * y, 64, 74));

	}
	int z = 0;

}

//PROBELM WITH FLASHING WAS DUE TO THE MINUS IN THE WIDTH TAKING AWAY FROM THE STARTING X THIS MEANS FRAME 2 IS ACTUALLY THE FIRST FRAME
void Player::addReverseFrame(thor::FrameAnimation & animation, int x, int y, int yFirst, int yLast, float duration)
{
	for (int i = 0; i < yLast; i++)
	{
		animation.addFrame(duration, sf::IntRect(64 + (64 * i), 78 * y, (64 * -1), 74));
	}
}



