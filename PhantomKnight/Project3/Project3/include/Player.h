#ifndef PLAYER
#define PLAYER

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include "Global.h"
#include <iostream>
#include <fstream>
#include <Thor/Animations.hpp>
#include "ParticleSystem.h"
#include "DashParticle.h"


class Player
{
public:
	Player();
	~Player();

//Creates and Updates Sprite
	void createBoxPlayer(b2World &t_world);

//Movement 
	void moveRight(b2Body *t_body);
	void moveLeft(b2Body *t_body);
	void moveUp(b2Body *t_body);
	void dash(b2Body *t_body);
	void floatUp(b2Body *t_body); // floats up to win the game 
	void increaseDashes(); //increases the number of dashes the player has 
	int getDashes() { return m_numberOfDashes; } // get the dashes the player currently has 

//Updates,Render,reset 
	void updateSprite(b2Body * body);
	void render(sf::RenderWindow &t_window);
	void reset(); //resets the player after the game is either won or lost 

//Player Getters()
	b2Vec2 getPosition();

//Players Box-2D body
	b2BodyDef m_bodyDef;
	b2Body* m_playerBody;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;


//ANIMATIONS
	sf::Clock frameClock;
	//Animation Frames
	thor::FrameAnimation runRight;
	thor::FrameAnimation runLeft;
	thor::FrameAnimation jumpRight;
	thor::FrameAnimation jumpLeft;
	thor::FrameAnimation idleRight;
	thor::FrameAnimation idleLeft;
	thor::Animator<sf::Sprite, std::string> animator;
	void addFrame(thor::FrameAnimation& animation, int x, int y, int yFirst, int yLast, float duration);
	void addReverseFrame(thor::FrameAnimation& animation, int x, int y, int yFirst, int yLast, float duration);

	ParticleSystem movingParticles;
	DashParticle dashParticles;

//Bools 
	bool m_jumped; //checks if the player has jumped 
	bool m_movingRight; //checks if he last moved right 
	bool m_movingLeft; //checks if he last moved left 
	bool m_floating; // checks if hes cloating 
	bool m_dashing = false; // checks if you are dashing 
	bool m_playJumpSound; // plays the first jump sound 
	bool m_playSecondJump; // plays the second jump sound 
	bool m_playerShown; // makes the player either seen or not seen 


//Used for the sprite of the player and the animations
	sf::Sprite m_sprite;
	sf::Image image;
	sf::Texture m_Texture;

private:

	//Cooldowns
	int m_jumpTimer;
	int m_jumpTimerTwo;
	int m_dashTimer;

	//Jumping
	int m_jumpCount;
	const int MAX_JUMPS = 2;

	//Speeds
	b2Vec2 m_speed = { 12.5, 0 };
	const b2Vec2 m_dashSpeed = { 12.0 * SCALE, 0 };
	const b2Vec2 m_jumpHeight = { 0,-4.9 * SCALE };
	float m_friction = 1.0f;
	float m_density = 3.5f;

	//Players max speed 
	b2Vec2 MAX_SPEED = {0.22 * SCALE,0};



	//Dash
	int m_lengthOfDash;
	int m_dashCoolDown;
	int m_numberOfDashes;
	const int MAX_DASHES = 3;


};
#endif // !PLAYER

