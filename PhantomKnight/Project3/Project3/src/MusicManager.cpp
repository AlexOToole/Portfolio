#include "MusicManager.h"



MusicManager::MusicManager()
{

	if (!m_groundBuffer.loadFromFile("ASSETS/SOUND/platform.wav"))
	{
		std::cout << " No File Found " << std::endl;
	}
	m_groundSound.stop();
	m_groundSound.setBuffer(m_groundBuffer);
	m_groundSound.setLoop(true);



	if (!m_dashBuffer.loadFromFile("ASSETS/SOUND/dashThree.wav"))
	{
		std::cout << " No File Found " << std::endl;
	}
	m_dashEffect.stop();
	m_dashEffect.setBuffer(m_dashBuffer);
	m_dashEffect.setLoop(false);

	if (!m_jumpBuffer.loadFromFile("ASSETS/SOUND/jump1.wav"))
	{
		std::cout << " No File Found " << std::endl;
	}
	m_jumpEffect.stop();
	m_jumpEffect.setBuffer(m_jumpBuffer);
	m_jumpEffect.setLoop(false);


	if (!m_ambiantBuffer.loadFromFile("ASSETS/SOUND/ambiance.wav"))
	{
		std::cout << " No File Found " << std::endl;
	}
	m_ambiantSound.stop();
	m_ambiantSound.setBuffer(m_ambiantBuffer);
	m_ambiantSound.setLoop(true);

	if (!m_endBuffer.loadFromFile("ASSETS/SOUND/menuBackgroundMusic.wav"))
	{
		std::cout << " No File Found End " << std::endl;
	}
	m_endSound.stop();
	m_endSound.setBuffer(m_endBuffer);
	m_endSound.setLoop(false);


	m_backgroundMusic.openFromFile("ASSETS/SOUND/menuBackgroundMusic.wav");
	m_backgroundMusic.stop();
	m_backgroundMusic.setVolume(0);
	m_backgroundMusic.setLoop(true);
}



MusicManager::~MusicManager()
{

}

void MusicManager::playEffect(sf::Sound & t_sound)
{
	t_sound.play();
}

void MusicManager::stopEffect(sf::Sound & t_sound)
{
	t_sound.stop();
}

void MusicManager::sfxVolume(int &vol)
{
	// sets the volumes 
	m_ambiantSound.setVolume(vol); 
	m_jumpEffect.setVolume(vol);
	m_dashEffect.setVolume(vol);
	m_groundSound.setVolume(vol);

}

void MusicManager::musicVolume(int &vol)
{
	m_endSound.setVolume(vol);
	m_backgroundMusic.setVolume(vol);

}


void MusicManager::playMenuMusic()
{
	m_ambiantSound.stop();
	if (m_backgroundMusic.getStatus() != sf::SoundSource::Status::Playing)
	{
		m_backgroundMusic.play();
	}
}



void MusicManager::updateEffects(Player & t_player, myListener & t_listener,EndGoalParticle & t_endPos)
{
	m_backgroundMusic.stop();
	if (m_ambiantSound.getStatus() != sf::SoundSource::Status::Playing)
	{
		playEffect(m_ambiantSound);
	}
//GRASS SOUNDS//
	if (t_player.m_playerBody->GetLinearVelocity().x > 5 || t_player.m_playerBody->GetLinearVelocity().x < -5 && t_player.m_jumped == false && t_player.m_dashing == false) // when the player is moving and both jump and dash are not occuring 
	{
		if (t_listener.m_playGrass == true)
		{
			if (m_groundSound.getStatus() != sf::SoundSource::Status::Playing)
			{
				playEffect(m_groundSound); // play the effect
			}
		}
		else // stop the sounds 
		{
			stopEffect(m_groundSound);
		}
	}
	else
	{
		stopEffect(m_groundSound);
	}

//DASHING SOUNDS//
	if (t_player.m_dashing)
	{
		if (m_dashEffect.getStatus() != sf::SoundSource::Status::Playing)
		{
			playEffect(m_dashEffect);
		}
	}
	else
	{
		stopEffect(m_dashEffect);
	}


//Jumping
	if (t_player.m_playJumpSound == true)
	{
		if (m_jumpEffect.getStatus() != sf::SoundSource::Status::Playing)
		{
			playEffect(m_jumpEffect);
		}
	}
	else
	{
		stopEffect(m_jumpEffect);
	}

//End Goal Sound
	/*distVec = thor::length(t_endPos.pos -t_player.m_sprite.getPosition());
	std::cout << distVec << std::endl;*/

	//if (t_player.m_floating)
	//{
	//	if (m_endSound.getStatus() != sf::SoundSource::Status::Playing)
	//	{
	//		playEffect(m_endSound);
	//	}
	//}
	//else
	//{
	//	stopEffect(m_endSound);
	//}
}


