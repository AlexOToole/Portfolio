#include "game.h"

GameState Game::m_currentState = GameState::MENU;
LevelState Game::m_currentLevel = LevelState::LEVEL1;

Game::Game(GameData & t_level) :
	m_level(t_level),
	m_mainMenu(m_level),
	m_optionsScreen(),
	m_highScoreScreen(m_level),
	m_helpScreen(),
	m_ground(),
	m_player(),
	m_spikeTrap(),
	m_pendulumTrap(),
	m_wall(),
	m_tut(),
	m_clouds(),
	m_pickUp(),
	m_effectsManager(),
	m_gui(world),
	m_window{ sf::VideoMode{ 3840, 2160 }, "Phantom Knight", sf::Style::Fullscreen }

{
	m_window.setVerticalSyncEnabled(true);

	m_castleTexture.loadFromFile("ASSETS/SPRITES/Temple.png");
	m_castle.setTexture(m_castleTexture);
	m_castle.scale(sf::Vector2f(2, 2));

	m_castle.setPosition(-1300, -100);


	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_pauseButtons[i].setUp(m_position, m_size, sf::Color::Black, sf::Color(190, 90, 54));
		m_pauseButtons[i].setCharacterSize(64);
		m_pauseButtons[i].setString(m_labelText[i]);
	}
	m_ground.createBox(world);
	m_player.createBoxPlayer(world);
	m_boundary.setup(sf::Vector2f(-990, 200), sf::Vector2f(4090, 200), world);
	m_tut.setup();

	//TRAPS
	for (int i = 0; i < M_MAX_L1_SPIKES; i++)
	{
		m_spikeTrap[i].createBoxSpikes(sf::Vector2f(620 + (i * 40), 700), world);
	}

	m_view.setSize(3840, 2160);
	m_view.setCenter(3840 / 2, 2160 / 2);

	m_currentView.setSize(3840, 2160);
	m_currentView.setCenter((m_player.getPosition().x * SCALE), m_player.getPosition().y * SCALE);
	m_currentView.zoom(0.5);

	levelSelect();



	world.SetDebugDraw(&fooDrawInstance);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	fooDrawInstance.SetFlags(flags);
	m_player.m_playerBody->SetUserData(&num);
	world.SetContactListener(&m_listener);

	m_keyboard.setUp();
	m_keyboard.setPosition(sf::Vector2f(1480, 600));
	m_winInstructions.setCharacterSize(128);
	m_winInstructions.setColor(sf::Color(190, 90, 54));
	m_winInstructions.setString("Please Enter Your Name");
	m_winInstructions.setPosition(sf::Vector2f(1920, 250));

	m_endParticle.endEffect();
	m_clouds.cloudOne();
	m_clouds.cloudTwo();
	m_clouds.cloudThree();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		loadContent();
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::levelSelect()
{
	int i = 0;
	switch (m_currentLevel)
	{
	case LevelState::TUTORIAL:
		//PLATFORMS 
		for (GroundData const & ground : m_level.m_level1.m_groundPoints)
		{
			m_platformPoints[i] = ground.m_position;
			m_platform[i].setup(m_platformPoints[i], world);
			i++;
		}
		//PICKUPS
		m_pickUp.setup(sf::Vector2f(625, -150), world);


		break;

	case LevelState::LEVEL1:
		//PLATFORMS
		for (GroundData const & ground : m_level.m_level2.m_groundPoints)
		{
			m_platformPoints[i] = ground.m_position;
			m_platform[i].setup(m_platformPoints[i], world);
			i++;
		}

		m_pickUp.setup(sf::Vector2f(1900, -250), world);
		m_pendulumTrap.createBoxPendulum(sf::Vector2f(550, 500), world);


		break;

	case LevelState::LEVEL2:
		//PLATFORMS
		for (GroundData const & ground : m_level.m_level3.m_groundPoints)
		{
			m_platformPoints[i] = ground.m_position;
			m_platform[i].setup(m_platformPoints[i], world);
			i++;
		}

		m_pickUp.setup(sf::Vector2f(3100, -150), world);
		m_pendulumTrap.createBoxPendulum(sf::Vector2f(-150, 650), world);
		break;
	}
}

void Game::loadContent()
{

}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			m_mouseDown = true;
		}
		if (m_currentState == GameState::OPTIONS)
		{
			m_optionsScreen.processingEvents(event);
		}
	}
}

void Game::update(sf::Time)
{
	tempSFX = m_optionsScreen.getSFX();
	tempMUSIC = m_optionsScreen.getMusic();
	temp = m_optionsScreen.getMusic();
	m_effectsManager.sfxVolume(tempSFX);
	m_effectsManager.musicVolume(tempMUSIC);
	switch (m_currentState)
	{
	case GameState::AUTHOR:
		break;

	case GameState::SPLASH:
		break;

	case GameState::MENU:
		m_view.setCenter(3840 / 2, 2160 / 2);
		reset();
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		m_mainMenu.update(m_updatedMousePos, m_mouseDown);

		if (m_mainMenu.m_play == true)
		{
			m_currentState = GameState::SELECTSCREEN;
			m_mainMenu.m_play = false;
		}
		if (m_mainMenu.m_options == true)
		{
			m_currentState = GameState::OPTIONS;
			m_mainMenu.m_options = false;
		}
		if (m_mainMenu.m_help == true)
		{
			m_currentState = GameState::HELP;
			m_mainMenu.m_help = false;
		}
		if (m_mainMenu.m_highscores == true)
		{
			m_currentState = GameState::HIGHSCORES;
			m_mainMenu.m_highscores = false;
		}
		if (m_mainMenu.m_exit == true)
		{
			m_window.close();
		}
		m_mouseDown = false;

		m_effectsManager.playMenuMusic();
		break;

	case GameState::TUTORIAL:
		m_currentView.setCenter(0, m_player.getPosition().y * SCALE - (400));
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		if (!m_win)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_pause = true;
				//m_currentState = GameState::MENU;
			}
			if (m_pause)
			{
				m_pauseTime = m_elapsed;
				m_clock.restart();
				m_pauseButtons[0].setPosition(sf::Vector2f(m_position.x, m_position.y - 30));
				m_pauseButtons[1].setPosition(sf::Vector2f(m_position.x, m_position.y + 90));


				if (m_pauseButtons[0].isHighlighted(m_updatedMousePos))
				{
					if (m_mouseDown)
						//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						m_pause = false;
						m_mouseDown = false;
					}
				}
				if (m_pauseButtons[1].isHighlighted(m_updatedMousePos))
				{
					if (m_mouseDown)
						//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						m_currentState = GameState::MENU;
						m_mouseDown = false;
					}
				}
			}
			else
			{
				m_elapsed = m_clock.getElapsedTime() + m_pauseTime;
				m_pauseTime = sf::seconds(0.0f);
				world.Step(timeStep, velocityIterations, positionIterations);
				m_tut.update(m_player.m_playerBody);
				m_player.updateSprite(m_player.m_playerBody);

				//COLLISIONS RESPONSES
				if (m_listener.m_destroy == true)
				{
					//world.DestroyBody(m_player.m_playerBody);
					m_listener.m_destroy = false;
					m_currentState = GameState::GAMEOVER;
				}

				if (m_listener.m_increaseDashes == true)
				{
					m_pickUp.m_pickupBody->SetActive(false);
					m_pickUp.draw = false;
					m_listener.m_increaseDashes = false;
					m_player.increaseDashes();
				}
				//SOUNDS 
				m_effectsManager.updateEffects(m_player, m_listener, m_endParticle);
				m_mouseDown = false;
			}

			//View boundaries (LEFT & RIGHT)
						//Left Side
			if (m_player.m_playerBody->GetPosition().x > 0 && m_player.m_playerBody->GetPosition().x < 3100 / SCALE)
			{
				m_currentView.setCenter((m_player.getPosition().x * SCALE), m_player.getPosition().y * SCALE - (400));
			}
			//Right Side
			if (m_player.m_playerBody->GetPosition().x > 3100 / SCALE)
			{
				m_currentView.setCenter(3100, m_player.getPosition().y * SCALE - (400));
			}

			//LEVEL DIFFERENCES
					//Tutorial 
			if (m_currentLevel == LevelState::TUTORIAL)
			{
				//Top Side
				if (m_player.m_floating)
				{
					m_currentView.setCenter(3100, -500);
				}

				m_platform[3].setAsGrass();
				m_platform[5].setAsGrass();
				m_platform[8].setAsGrass();

				//Win Statement
				if (m_player.m_playerBody->GetPosition().x * SCALE > 3800 && m_player.m_playerBody->GetPosition().x * SCALE < 3900
					&& m_player.m_playerBody->GetPosition().y * SCALE > -260 && m_player.m_playerBody->GetPosition().y * SCALE < -80)
				{
					m_player.m_dashing = false;
					m_player.m_playerShown = true;
					m_player.m_playerBody->SetLinearVelocity(b2Vec2(0, -3));
					m_player.floatUp(m_player.m_playerBody);
				}

				if (m_player.m_playerBody->GetPosition().x * SCALE > 3700 && m_player.m_playerBody->GetPosition().x * SCALE < 3900
					&& m_player.m_playerBody->GetPosition().y * SCALE > -1720 && m_player.m_playerBody->GetPosition().y * SCALE < -880)
				{
					m_player.movingParticles.clearEmmiters();
					m_player.movingParticles.clearParticles();

					m_win = true;
					m_player.m_floating = false;
					m_currentState = GameState::GAMEOVER;
				}
			}


			if (m_currentLevel == LevelState::LEVEL1)
			{
				m_pendulumTrap.updateSprite(m_pendulumTrap.m_pendBody);

				//Top Side
				if (m_player.m_floating)
				{
					m_currentView.setCenter(1600, -918);
				}

				m_platform[3].setAsIce();
				m_platform[5].setAsIce();
				m_platform[8].setAsIce();

				//Win Statement
				if (m_player.m_playerBody->GetPosition().x * SCALE > 1600 && m_player.m_playerBody->GetPosition().x * SCALE < 1700
					&& m_player.m_playerBody->GetPosition().y * SCALE < -518 && m_player.m_playerBody->GetPosition().y * SCALE > -600)
				{
					m_player.m_dashing = false;
					m_player.m_playerShown = true;
					m_player.m_playerBody->SetLinearVelocity(b2Vec2(0, -3));
					m_player.floatUp(m_player.m_playerBody);
				}

				if (m_player.m_playerBody->GetPosition().x * SCALE > 1600 && m_player.m_playerBody->GetPosition().x * SCALE < 1700
					&& m_player.m_playerBody->GetPosition().y * SCALE < -1280 && m_player.m_playerBody->GetPosition().y * SCALE > -1800)
				{
					m_player.movingParticles.clearEmmiters();
					m_player.movingParticles.clearParticles();

					m_win = true;
					m_player.m_floating = false;
					m_currentState = GameState::GAMEOVER;
				}
			}
			if (m_currentLevel == LevelState::LEVEL2)
			{
				m_pendulumTrap.updateSprite(m_pendulumTrap.m_pendBody);

				//Top Side
				if (m_player.m_floating)
				{
					m_currentView.setCenter(1900, -778);
				}
				m_platform[3].setAsGrass();
				m_platform[5].setAsGrass();
				m_platform[8].setAsGrass();
				m_platform[11].setAsIce();
				m_platform[12].setAsIce();
				m_platform[8].setAsIce();

				//Win Statement
				if (m_player.m_playerBody->GetPosition().x * SCALE > 1800 && m_player.m_playerBody->GetPosition().x * SCALE < 1950
					&& m_player.m_playerBody->GetPosition().y * SCALE < -378 && m_player.m_playerBody->GetPosition().y * SCALE > -450)
				{
					m_player.m_dashing = false;
					m_player.m_playerShown = true;
					m_player.m_playerBody->SetLinearVelocity(b2Vec2(0, -3));
					m_player.floatUp(m_player.m_playerBody);
				}

				if (m_player.m_playerBody->GetPosition().x * SCALE > 1800 && m_player.m_playerBody->GetPosition().x * SCALE < 1950
					&& m_player.m_playerBody->GetPosition().y * SCALE < -1080 && m_player.m_playerBody->GetPosition().y * SCALE > -2050)
				{
					m_player.movingParticles.clearEmmiters();
					m_player.movingParticles.clearParticles();

					m_win = true;
					m_player.m_floating = false;
					m_currentState = GameState::GAMEOVER;
				}
			}

			m_endParticle.gameUpdate(m_platform[14].m_platformBody);
			m_clouds.update(sf::Vector2f(-1000, -400));
			m_pickUp.update();

			m_position.x = m_currentView.getCenter().x;
			m_position.y = m_currentView.getCenter().y - m_size.y;
			m_dashCount = m_player.getDashes();
			m_gui.update(sf::Vector2f(m_currentView.getCenter().x, m_currentView.getCenter().y - 490), m_dashCount, m_elapsed, sf::Vector2f(740 / SCALE, 650 / SCALE), m_platformPoints[14]);
			break;

	case GameState::SELECTSCREEN:
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		m_levelSelectScreen.update(m_updatedMousePos, m_mouseDown);
		if (m_levelSelectScreen.m_mainMenu)
		{
			m_currentState = GameState::MENU;
			m_levelSelectScreen.m_mainMenu = false;
		}
		if (m_levelSelectScreen.m_tutorial)
		{
			m_currentLevel = LevelState::TUTORIAL;
			m_levelSelectScreen.m_tutorial = false;
			levelSelect();
			m_currentState = GameState::TUTORIAL;
		}
		if (m_levelSelectScreen.m_level1)
		{
			m_currentLevel = LevelState::LEVEL1;
			m_levelSelectScreen.m_level1 = false;
			levelSelect();
			m_currentState = GameState::TUTORIAL;
		}
		if (m_levelSelectScreen.m_level2)
		{
			m_currentLevel = LevelState::LEVEL2;
			m_levelSelectScreen.m_level2 = false;
			levelSelect();
			m_currentState = GameState::TUTORIAL;
		}
		m_mouseDown = false;
		break;

	case GameState::HELP:
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		m_helpScreen.update(m_updatedMousePos, m_mouseDown);
		if (m_helpScreen.m_mainMenu)
		{
			m_currentState = GameState::MENU;
			m_helpScreen.m_mainMenu = false;
		}
		m_mouseDown = false;
		break;

	case GameState::OPTIONS:
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		m_optionsScreen.update(m_updatedMousePos, m_mouseDown);
		if (m_optionsScreen.m_mainMenu)
		{
			m_currentState = GameState::MENU;
			m_optionsScreen.m_mainMenu = false;
		}
		m_mouseDown = false;
		break;

	case GameState::HIGHSCORES:
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		m_highScoreScreen.keyPressed(m_updatedMousePos, m_mouseDown);
		//m_highScoreScreen.newScore(90, "Alex");
		if (m_highScoreScreen.m_mainMenu)
		{
			m_currentState = GameState::MENU;
			m_highScoreScreen.m_mainMenu = false;
		}
		m_mouseDown = false;
		break;
	case GameState::GAMEOVER:
		m_gameOverButton.setUp(sf::Vector2f(1920, 2020), m_size, sf::Color::Black, sf::Color(190, 90, 54));
		m_gameOverButton.setCharacterSize(64);
		m_gameOverButton.setString("Return to Menu");
		if (!m_win)
		{
			m_winText.setString("You Lose");
		}
		else
		{
			m_winText.setString("You Win!");
		}
		m_currentView.setCenter(3840 / 2, 2160 / 2);
		m_winText.setPosition(sf::Vector2f(1920, 100));
		m_winText.setCharacterSize(128);
		m_previousMousePos = (sf::Mouse::getPosition(m_window));
		m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
		if (m_win)
		{
			m_keyboard.update(m_updatedMousePos, m_mouseDown);
		}
		if (m_gameOverButton.isHighlighted(m_updatedMousePos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_playerName = m_keyboard.getInput();
				m_score = m_gui.getScore();
				m_highScoreScreen.newScore(m_score, m_playerName);
				m_currentState = GameState::MENU;
			}
		}
		m_mouseDown = false;
	default:
		break;
		}
		m_mouseDown = false;
	}
}
void Game::render()
{
	m_window.clear();

	switch (m_currentState)
	{
	case GameState::AUTHOR:
		break;

	case GameState::SPLASH:
		break;

	case GameState::MENU:
		m_window.setView(m_view);

		m_mainMenu.render(m_window);
		break;

	case GameState::TUTORIAL:
		m_window.clear(sf::Color(135, 206, 235));
		m_clouds.render(m_window);
		m_window.draw(m_castle);
		m_window.setView(m_currentView);
		m_player.render(m_window);
		m_endParticle.render(m_window);
		m_gui.render(m_window);

		for (int y = 0; y < M_MAX_L1_SPIKES; y++)
		{
			m_spikeTrap[y].render(m_window);
		}

		if (m_currentLevel == LevelState::TUTORIAL)
		{
			m_tut.render(m_window);
			//Displaying the platforms
			if (m_listener.m_PLATS_DISPLAYED == true)
			{
				m_pickUp.render(m_window);

				for (int i = 0; i < M_MAX_PLATFORMS; i++)
				{
					m_platform[i].render(m_window);
				}
			}
			else if (m_listener.m_PLATS_DISPLAYED == false)
			{
				m_platform[0].render(m_window);
			}
		}

		if (m_currentLevel == LevelState::LEVEL1)
		{
			m_pickUp.render(m_window);

			m_pendulumTrap.render(m_window);

			////Displaying the platforms
			for (int i = 0; i < M_MAX_PLATFORMS; i++)
			{
				m_platform[i].render(m_window);
			}
		}

		if (m_currentLevel == LevelState::LEVEL2)
		{
			m_pickUp.render(m_window);

			m_pendulumTrap.render(m_window);

			//////Displaying the platforms
			for (int i = 0; i < M_MAX_PLATFORMS; i++)
			{
				m_platform[i].render(m_window);
			}
		}

		if (m_pause)
		{
			for (int i = 0; i < M_MAX_BUTTONS; i++)
			{
				m_pauseButtons[i].render(m_window);
			}
		}
		if (m_pause != true)
		{
			world.DrawDebugData();
		}
		m_ground.render(m_window);

		break;
	case GameState::SELECTSCREEN:
		m_levelSelectScreen.render(m_window);
		break;
	case GameState::HELP:
		m_helpScreen.render(m_window);
		break;

	case GameState::OPTIONS:
		m_optionsScreen.render(m_window);
		break;

	case GameState::HIGHSCORES:
		m_highScoreScreen.render(m_window);
		break;
	case GameState::GAMEOVER:
		m_window.clear(sf::Color(114, 148, 138));
		m_window.setView(m_view);
		m_winText.render(m_window);
		if (m_win)
		{
			m_keyboard.render(m_window);
			m_winInstructions.render(m_window);
		}
		m_gameOverButton.render(m_window);
	default:
		break;
	}


	m_window.display();
}

void Game::reset()
{
	m_clock.restart();
	m_pause = false;
	m_win = false;
	m_player.reset();
	m_pickUp.draw = true;
	m_player.m_dashing = false;
	m_pendulumTrap.reset();
	m_listener.m_PLATS_DISPLAYED = false;

	for (int i = 0; i < M_MAX_PLATFORMS; i++)
	{
		m_platform[i].destroy(world);
	}

	m_dashCount = 3;
	m_gui.reset();
	m_pickUp.destroy(world);
	m_pendulumTrap.destroy(world);
	m_keyboard.reset();
}



