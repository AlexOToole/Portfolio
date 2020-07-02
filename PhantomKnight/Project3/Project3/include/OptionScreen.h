#ifndef OPTIONSCREEN
#define OPTIONSCREEN

#include <SFML/Graphics.hpp>
#include "UiLibrary.h"
#include "EndGoalParticle.h"
class OptionScreen
{
public:
	OptionScreen();
	~OptionScreen();


	void processingEvents(sf::Event t_event);
	void update(sf::Vector2f t_mousePos, bool t_clicked);
	void render(sf::RenderWindow &t_window);
	int getMusic() { return m_musicSlider.getValue(); }
	int getSFX() { return m_sfxSlider.getValue(); }
	bool m_mainMenu = false;

	EndGoalParticle particlesTest;
private:
	Label m_optionText;
	Button m_exitButton;
	Slider m_musicSlider;
	Slider m_sfxSlider;
	Label m_musicVolLabel;
	Label m_sfxVolLabel;
};

#endif // !OPTIONSCREEN