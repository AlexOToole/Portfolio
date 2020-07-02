#include "UiLibrary.h"

/// <summary>
/// Label section of the UI Library
/// </summary>
Label::Label()
{
	if (!m_font.loadFromFile("ASSETS/ALGER.TTF"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading text" << std::endl;
	}
	m_label.setFont(m_font);
	//default
	m_label.setString("");
	m_label.setPosition(sf::Vector2f(0, 0));
	m_label.setCharacterSize(64);
	m_label.setOrigin(m_label.getLocalBounds().width / 2, m_label.getLocalBounds().height / 2);
	m_label.setFillColor(sf::Color::Green);
}

Label::~Label()
{
}

void Label::setPosition(sf::Vector2f t_pos)
{
	m_label.setPosition(t_pos);
}

void Label::setColor(sf::Color t_color)
{
	m_label.setFillColor(t_color);
}

void Label::setCharacterSize(int t_size)
{
	m_label.setCharacterSize(t_size);
	m_label.setOrigin(m_label.getLocalBounds().width / 2, m_label.getLocalBounds().height / 2);
}

void Label::setString(std::string t_string)
{
	m_label.setString(t_string);
}

void Label::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_label);
}



/// <summary>
/// Button section of the UI library
/// </summary>
Button::Button()
{
	if (!m_font.loadFromFile("ASSETS/ALGER.TTF"))
	{

	}
}


Button::~Button()
{
}

void Button::setUp(sf::Vector2f t_pos, sf::Vector2f t_size)
{
	m_label.setString("");
	m_position = t_pos;
	m_size = t_size;


	m_button.setSize(m_size);
	m_button.setOrigin(m_button.getLocalBounds().width / 2, m_button.getLocalBounds().height / 2);
	m_button.setPosition(m_position);
	m_button.setFillColor(sf::Color::Red);
	m_text.setFont(m_font);
	m_text.setCharacterSize(48);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setPosition(sf::Vector2f(m_button.getPosition().x - 70, m_button.getPosition().y - 30));

	m_highlight.setSize(sf::Vector2f(m_size.x + 10.0f, m_size.y + 10));
	m_highlight.setOrigin(m_highlight.getLocalBounds().width / 2, m_highlight.getLocalBounds().height / 2);
	m_highlight.setPosition(m_position);
	m_highlight.setFillColor(sf::Color::Green);
}

void Button::setString(std::string t_string)
{
	m_text.setString(t_string);
}

void Button::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_button.setPosition(t_pos);
	m_highlight.setPosition(m_position);
}

bool Button::isHighlighted(sf::Vector2f t_mousePos)
{
	if (t_mousePos.x > m_position.x - m_size.x / 2 && t_mousePos.x < m_position.x + m_size.x / 2
		&& t_mousePos.y > m_position.y - m_size.y / 2 && t_mousePos.y < m_position.y + m_size.y / 2)
	{
		m_highlighted = true;
		return m_highlighted;
	}
	else
	{
		m_highlighted = false;
		return m_highlighted;
	}
}

void Button::render(sf::RenderWindow & t_window)
{
	if (m_highlighted)
	{
		t_window.draw(m_highlight);
	}
	t_window.draw(m_button);
	t_window.draw(m_text);
}