#include "myListener.h"



myListener::myListener()
{
}


myListener::~myListener()
{

}

//When contact first begins 
void myListener::BeginContact(b2Contact * contact)
{
	b2Body* one = contact->GetFixtureA()->GetBody();
	b2Body* two = contact->GetFixtureB()->GetBody();
	 a = *((int*)one->GetUserData());
	 b = *((int*)two->GetUserData());

	//For the Platforms
	if (b == 2)
	{
		m_PLATS_DISPLAYED = true;
	}

	//For the Spike Traps
	if (b == 3)
	{
		m_destroy = true;
	}

	//For Pendulum
	if (b == 4)
	{
		if (a == 6)
		{
			m_destroy = true;
		}
	}

	if (b == 6)
	{
		m_playGrass = true;
	}

	if (b == 7)
	{
		m_increaseDashes = true;
	}
}

//When contact ends 
void myListener::EndContact(b2Contact * contact)
{
	if (b == 6)
	{
		m_playGrass = false;
	}
}

//Triggered after the outcome of the collision is solved
void myListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}

//Triggered before Box2D solves the outcome of the collision
void myListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

