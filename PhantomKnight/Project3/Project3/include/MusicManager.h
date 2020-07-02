#ifndef MUSICMANAGER
#define MUSICMANAGER

#include "Global.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "myListener.h"
#include "EndGoalParticle.h"
#include <math.h>
#include "Thor/Vectors.hpp"


class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	void playEffect(sf::Sound &t_sound); // plays the effect that is passed to it 
	void stopEffect(sf::Sound &t_sound); // Stops the effect that is passed to it
	
	// Get the volume from the options screen and sets all the the releveant sounds
	void sfxVolume(int &sfxVol); 
	void musicVolume(int &musicVol);

	//Updates the sounds based on what the player is doing 
	void updateEffects(Player & t_player,myListener & t_listener,EndGoalParticle & t_endPos);

	//Plays the menu music when in the menu and stop the other sounds
	void playMenuMusic();


	//Collisions With the Ground
	sf::Sound m_groundSound;
	sf::SoundBuffer m_groundBuffer;

	//Dashing Sound Effect
	sf::Sound m_dashEffect;
	sf::SoundBuffer m_dashBuffer;

	//Jump Sound Effect
	sf::Sound m_jumpEffect;
	sf::SoundBuffer m_jumpBuffer;

	//Ambient Music
	sf::Sound m_ambiantSound;
	sf::SoundBuffer m_ambiantBuffer;

	//End Goal Sound
	float distVec;
	sf::Sound m_endSound;
	sf::SoundBuffer m_endBuffer;

	//Menu Music
	sf::Music m_backgroundMusic;


};

#endif // !MUSICMANAGER

