#ifndef TUTORIALMANAGER
#define TUTORIALMANAGER

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Box2D/Box2D.h"
#include "Global.h"



class TutorialManager
{
public:
	TutorialManager();
	~TutorialManager();

	void setup();
	void update(b2Body *playerPos);
	void render(sf::RenderWindow &t_window);

	//Signs 
	sf::Sprite m_signs[3];
	sf::Texture m_signTexture;

	//Pop up messages
	sf::Texture m_popTexture[3];

	// Interaction Pop up
	sf::Sprite m_interPopUp[3];
	sf::Texture m_interPopText;

	bool m_showIntPopJump = false;
	bool m_showIntPopMove = false;
	bool m_showIntPopDash = false;


	bool m_showTutPopOne = false;
	bool m_showTutPopTwo = false;
};


#endif // !TUTORIALMANGER

