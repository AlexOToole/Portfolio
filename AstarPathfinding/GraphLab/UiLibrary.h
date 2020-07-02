#ifndef UILIBRARY
#define UILIBRARY


#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
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
	void setUp(sf::Vector2f t_pos, sf::Vector2f t_size);
	void setString(std::string t_string);
	void setPosition(sf::Vector2f t_pos);
	void render(sf::RenderWindow &t_window);
	bool isHighlighted(sf::Vector2f t_mousePos);
	float getPositionX() { return m_button.getPosition().x; }
	float getPositionY() { return m_button.getPosition().y; }
	std::string getString() { return m_label.getString(); }
private:
	sf::RectangleShape m_button;
	sf::RectangleShape m_highlight;
	sf::Font m_font;
	sf::Text m_text;
	Label m_label;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	bool m_highlighted = false;
};
#endif // !UILIBRARY