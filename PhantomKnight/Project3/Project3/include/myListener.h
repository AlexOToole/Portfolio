#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include <iostream> 
#include "Player.h"
class myListener : public b2ContactListener
{
public:
	myListener();
	~myListener();


	bool m_destroy = false; // sets the state to lost
	bool m_gravityOff = false; //turns gravity off
	bool m_increaseDashes = false; // increases dashes
	bool m_playGrass = false; 

	bool m_PLATS_DISPLAYED = false;


	void BeginContact(b2Contact* contact); //Triggered whenever two shapes first come into contact with each other.
	void EndContact(b2Contact* contact);  //Triggered over and over again as long as shapes continue to be in contact.
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); //Triggered before Box2D solves the outcome of the collision.
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold); //Triggered after the outcome of the collision is solved.

	//Shapes User data set to these
	int a;
	int b;
	

};

