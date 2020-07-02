#ifndef UILIBRARY
#define UILIBRARY


#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <math.h>
#include "PickUps.h"
#include <Thor/Animations.hpp>
class Label
{
public:
	Label();
	~Label();

	void setPosition(sf::Vector2f t_pos);
	void setColor(sf::Color t_color);
	void setCharacterSize(int t_size);
	void setString(std::string t_string);
	void render(sf::RenderWindow &t_window);
	std::string getString() { return m_label.getString(); }
private:
	sf::Text m_label;
	sf::Font m_font;
};

class Button
{
public:
	Button();
	~Button();
	//defaults arguments.
	void setUp(sf::Vector2f t_pos = sf::Vector2f(0, 0), sf::Vector2f t_size = sf::Vector2f(300, 50), sf::Color t_buttonColor = sf::Color::Black, sf::Color t_textColor = sf::Color::Green);
	void setString(std::string t_string);
	void setCharacterSize(int t_size);
	void setTextColor(sf::Color t_color) { m_text.setFillColor(t_color); }
	void setButtonColor(sf::Color t_color) { m_button.setFillColor(t_color); }
	void setHighlightColor(sf::Color t_color) { m_highlight.setFillColor(t_color); }
	void setPosition(sf::Vector2f t_pos);
	void render(sf::RenderWindow &t_window);
	bool isHighlighted(sf::Vector2f t_mousePos);
	float getPositionX() { return m_button.getPosition().x; }
	float getPositionY() { return m_button.getPosition().y; }
	std::string getString() { return m_text.getString(); }
private:
	sf::RectangleShape m_button;
	sf::RectangleShape m_highlight;
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	bool m_highlighted = false;
};

class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	void setUp();
	void update(sf::Vector2f t_mousePos, bool t_mouseDown);
	void render(sf::RenderWindow &t_window);
	void setPosition(sf::Vector2f t_position);
	std::string getInput() { return m_input; }
	void reset() { m_input = ""; }
private:
	static const int m_MAX_KEYBOARD_BUTTONS = 26;
	Button m_keyboard[m_MAX_KEYBOARD_BUTTONS];
	Button m_spaceBar;
	Button m_del;
	Label m_label;
	sf::Vector2f m_mousePos;
	bool m_mouseDown = false;
	std::string m_input;
};

class Slider
{
public:
	Slider();
	~Slider();
	void setPosition(const sf::Vector2f t_POS);
	bool isHighlighted(sf::Vector2f t_mousePos);
	int getValue() { return m_value; }
	void processingEvents(sf::Event t_event);
	void update(sf::Vector2f t_mousePos);
	void render(sf::RenderWindow &t_window);
private:
	sf::RectangleShape m_outline;
	sf::RectangleShape m_slider;
	sf::CircleShape m_grip;
	float m_radius = 40;
	sf::Vector2f m_position = { sf::Vector2f(1920 / 2,1080 / 2) };
	sf::Vector2f m_size = { sf::Vector2f(400,50) };
	bool m_highlighted = false;
	const sf::Color M_ORANGE = { 255,153,0 };
	int m_value = m_size.x / 4;
	bool m_mouseDown = false;
};

class GuiPanel
{
public:
	GuiPanel(b2World & t_world);
	~GuiPanel();
	void update(sf::Vector2f t_newPos, int t_dashNum, sf::Time t_elapsed, sf::Vector2f t_startPos, sf::Vector2f t_endPos);
	void render(sf::RenderWindow &t_window);
	void reset();
	int getScore() { return m_score / m_elapsed.asSeconds(); }
private:
	sf::RectangleShape m_panel;
	Label m_timerText;
	Label m_time;
	Label m_dashes;
	static const int M_MAX_PICKUPS = 3;
	PickUps m_pickups[M_MAX_PICKUPS];
	int m_currentPickups = M_MAX_PICKUPS;
	//ANIMATIONS
	sf::Clock m_frameClock;
	//Animation Frames
	thor::FrameAnimation m_hover;

	thor::Animator<sf::Sprite, std::string> m_animator;
	void addFrames(thor::FrameAnimation& animation, int x, int y, int yFirst, int yLast, float duration);
	bool draw = true;
	int m_pickupNum = 7;

	sf::Sprite m_pickUpSprite[M_MAX_PICKUPS];
	sf::Texture m_pickUpTexture;
	sf::Image m_image;

	int m_score = 1000000;
	sf::Time m_elapsed;
	//progress bar
	sf::RectangleShape m_outline;
	sf::RectangleShape m_progress;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_endPosition;
	std::stringstream m_sstream;
};
#endif // !UILIBRARY