#include "UiLibrary.h"

/// <summary>
/// Label section of the UI Library
/// </summary>
Label::Label()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\AGENCYB.ttf"))
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
	m_label.setFillColor(sf::Color(190, 90, 54));
}

Label::~Label()
{
}

void Label::setPosition(sf::Vector2f t_pos)
{
	m_label.setOrigin(m_label.getLocalBounds().width / 2, m_label.getLocalBounds().height / 2);
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
	m_label.setOrigin(m_label.getLocalBounds().width / 2, m_label.getLocalBounds().height / 2);
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
	if (!m_font.loadFromFile("ASSETS\\FONTS\\AGENCYB.ttf"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading text" << std::endl;
	}
}


Button::~Button()
{
}

void Button::setUp(sf::Vector2f t_pos, sf::Vector2f t_size, sf::Color t_buttonColor, sf::Color t_textColor)
{
	m_text.setString("Button Text");
	m_position = t_pos;
	m_size = t_size;


	m_button.setSize(m_size);
	m_button.setOrigin(m_button.getLocalBounds().width / 2, m_button.getLocalBounds().height / 2);
	m_button.setPosition(m_position);
	m_button.setFillColor(t_buttonColor);
	m_text.setCharacterSize(52);
	m_text.setFont(m_font);
	m_text.setFillColor(t_textColor);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getCharacterSize() / 4));

	m_highlight.setSize(sf::Vector2f(m_size.x + 10.0f, m_size.y + 10));
	m_highlight.setOrigin(m_highlight.getLocalBounds().width / 2, m_highlight.getLocalBounds().height / 2);
	m_highlight.setPosition(m_position);
	m_highlight.setFillColor(sf::Color(255, 240, 218));
}

void Button::setString(std::string t_string)
{
	m_text.setString(t_string);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getCharacterSize() / 4));
}

void Button::setCharacterSize(int t_size)
{
	m_text.setCharacterSize(t_size);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getCharacterSize() / 4));
}

void Button::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_button.setPosition(t_pos);
	m_highlight.setPosition(m_position);
	m_text.setPosition(sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_text.getCharacterSize() / 4));
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

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::setUp()
{
	std::stringstream ss;
	std::string temp;
	int x = 160;
	int y = 160;
	for (int i = 1; i <= m_MAX_KEYBOARD_BUTTONS; i++)
	{
		m_keyboard[i - 1].setUp(sf::Vector2f(x += 160, y), sf::Vector2f(140, 140), sf::Color::Black, sf::Color(190, 90, 54));
		if (i % 5 == 0)
		{
			y += 160;
			x = 160;

		}
		ss << char(65 + (i - 1));
		ss >> temp;
		//		std::string temp = "" + char(65 + i);
		m_keyboard[i - 1].setString(temp);
		ss.clear();

	}
	m_spaceBar.setUp(sf::Vector2f(640, y), sf::Vector2f(470, 140), sf::Color::Black, sf::Color(190, 90, 54));
	m_spaceBar.setString("Space");
	m_del.setUp(sf::Vector2f(960, y), sf::Vector2f(140, 140), sf::Color::Black, sf::Color(190, 90, 54));
	m_del.setString("Del");

	m_label.setPosition(sf::Vector2f(500, 10));
}

void Keyboard::update(sf::Vector2f t_mousePos, bool t_mouseDown)
{
	for (int i = 0; i < m_MAX_KEYBOARD_BUTTONS; i++)
	{
		if (m_keyboard[i].isHighlighted(t_mousePos))
		{
			if (t_mouseDown)
			{
				if (m_input.size() <= 10)
				{
					m_input = m_input + m_keyboard[i].getString();
				}
			}
		}
	}
	if (m_spaceBar.isHighlighted(t_mousePos))
	{
		if (t_mouseDown)
		{
			if (m_input.size() <= 16)
			{
				m_input = m_input + " ";
			}
		}
	}

	if (m_del.isHighlighted(t_mousePos))
	{
		if (t_mouseDown)
		{
			if (m_input.size() > 0)
			{
				m_input.pop_back();
			}
		}
	}
	m_label.setString(m_input);
}

void Keyboard::render(sf::RenderWindow &t_window)
{
	//t_window.clear(sf::Color::White);
	for (int i = 0; i < m_MAX_KEYBOARD_BUTTONS; i++)
	{
		m_keyboard[i].render(t_window);
	}
	m_spaceBar.render(t_window);
	m_del.render(t_window);
	m_label.render(t_window);
}

void Keyboard::setPosition(sf::Vector2f t_position)
{
	int x = t_position.x;
	int y = t_position.y;
	for (int i = 1; i <= m_MAX_KEYBOARD_BUTTONS; i++)
	{
		m_keyboard[i - 1].setPosition(sf::Vector2f(x += 160, y));
		if (i % 5 == 0)
		{
			y += 160;
			x = t_position.x;
		}
	}
	m_spaceBar.setPosition(sf::Vector2f( x + 320, y));
	m_del.setPosition(sf::Vector2f(x + 640, y));
	m_label.setPosition(sf::Vector2f(t_position.x + 480, t_position.y - 150));
}

Slider::Slider()
{
	//Outline
	m_outline.setSize(m_size);
	m_outline.setOrigin(m_outline.getLocalBounds().width / 2, m_outline.getLocalBounds().height / 2);
	m_outline.setPosition(m_position);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineThickness(10);
	m_outline.setOutlineColor(sf::Color::Black);

	//Main slider
	m_slider.setSize(m_size);
	m_slider.setOrigin(m_slider.getLocalBounds().width / 2, m_slider.getLocalBounds().height / 2);
	m_slider.setPosition(m_position);
	m_slider.setFillColor(sf::Color::Green);

	m_grip.setRadius(m_radius);
	m_grip.setOrigin(sf::Vector2f(m_grip.getLocalBounds().width / 2, m_grip.getLocalBounds().height / 2));
	m_grip.setPosition(sf::Vector2f(m_position.x + (m_size.x / 2), m_position.y));
	m_grip.setFillColor(sf::Color::Black);
	m_grip.setOutlineThickness(5);
	m_grip.setOutlineColor(sf::Color::Black);

}

Slider::~Slider()
{
}

void Slider::setPosition(const sf::Vector2f t_POS)
{
	m_position = t_POS;
	m_outline.setPosition(m_position);
	m_slider.setPosition(m_position);
	m_grip.setPosition(sf::Vector2f(m_position.x + (m_size.x / 2), m_position.y));
}

bool Slider::isHighlighted(sf::Vector2f t_mousePos)
{
	//calculates the distance between mouse and circle centre
	float distX = t_mousePos.x - m_grip.getPosition().x;
	float distY = t_mousePos.y - m_grip.getPosition().y;
	if (sqrt((distX * distX) + (distY * distY)) < m_grip.getRadius())
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

void Slider::processingEvents(sf::Event t_event)
{
	if (t_event.type == sf::Event::MouseButtonPressed)
	{
		m_mouseDown = true;
	}
	if (t_event.type == sf::Event::MouseButtonReleased)
	{
		m_mouseDown = false;
	}
}
void Slider::update(sf::Vector2f t_mousePos)
{
	if (isHighlighted(t_mousePos))
	{
		m_grip.setOutlineColor(sf::Color(255, 240, 218));
		if (m_mouseDown)
		{
			m_grip.setPosition(sf::Vector2f(t_mousePos.x, m_grip.getPosition().y));
			//Distance between end of the bar and the cetre of the grip
			float distX = m_outline.getPosition().x + (m_size.x / 2) - m_grip.getPosition().x;
			m_slider.setSize(sf::Vector2f(m_size.x - distX, m_size.y));
			m_value = m_slider.getSize().x / 4;
			if (m_value > 100)
			{
				m_value = 100;
			}
			if (m_value < 0)
			{
				m_value = 0;
			}
			//boundary so the grip cant move off the slider bar
			if (m_grip.getPosition().x > m_outline.getPosition().x + (m_size.x / 2))
			{
				m_grip.setPosition(m_outline.getPosition().x + (m_size.x / 2), m_grip.getPosition().y);
			}
			if (m_grip.getPosition().x < m_outline.getPosition().x - (m_size.x / 2))
			{
				m_grip.setPosition(m_outline.getPosition().x - (m_size.x / 2), m_grip.getPosition().y);
			}
		}
	}
	else
	{
		m_grip.setOutlineColor(sf::Color::Black);
	}
	if (m_slider.getSize().x > m_size.x)
	{
		m_slider.setFillColor(sf::Color::Green);
	}
	if (m_slider.getSize().x <= (m_size.x - (m_size.x * 0.25)))
	{
		m_slider.setFillColor(sf::Color::Yellow);
	}
	if (m_slider.getSize().x <= (m_size.x - (m_size.x * 0.50)))
	{
		m_slider.setFillColor(M_ORANGE);
	}
	if (m_slider.getSize().x <= (m_size.x - (m_size.x * 0.75)))
	{
		m_slider.setFillColor(sf::Color::Red);
	}
}

void Slider::render(sf::RenderWindow & t_window)
{
	//t_window.clear(sf::Color::White);
	t_window.draw(m_outline);
	t_window.draw(m_slider);
	t_window.draw(m_grip);
}

GuiPanel::GuiPanel(b2World & t_world)
{
	m_image.loadFromFile("ASSETS/SPRITES/pickupSheetTwo.png");

	m_image.createMaskFromColor(sf::Color::White);

	// Create texture based on sf::Image
	if (!m_pickUpTexture.loadFromImage(m_image))
	{
		std::cout << " No Image Found " << std::endl;
	}

	addFrames(m_hover, 0, 0, 0, 18, 1.0f);

	//Adds the animation with their corresponding durations
	m_animator.addAnimation("hover", m_hover, sf::seconds(1.f));
	m_panel.setSize(sf::Vector2f(1920, 100));
	m_panel.setOrigin(m_panel.getLocalBounds().width / 2, m_panel.getLocalBounds().height / 2);
	m_panel.setFillColor(sf::Color(102, 111, 124, 155));

	m_timerText.setString("Time: ");
	m_time.setString("0");
	m_dashes.setString("Dashes: ");

	for (int i = 0; i < M_MAX_PICKUPS; i++)
	{
		m_pickUpSprite[i].setTexture(m_pickUpTexture);
		m_pickUpSprite[i].setOrigin(12.4f, 20.0f);
	}

}

GuiPanel::~GuiPanel()
{

}

void GuiPanel::update(sf::Vector2f t_newPos, int t_dashNum, sf::Time t_elapsed, sf::Vector2f t_startPos, sf::Vector2f t_endPos)
{
	if (!m_animator.isPlayingAnimation())
	{
		m_animator.playAnimation("hover");

	}
	// Update animator and apply current animation state to the sprite
	m_animator.update(m_frameClock.restart());
	for (int i = 0; i < M_MAX_PICKUPS; i++)
	{ 
		m_animator.animate(m_pickUpSprite[i]);
	}
	m_panel.setPosition(t_newPos);
	m_timerText.setPosition(sf::Vector2f(m_panel.getPosition().x + 620, m_panel.getPosition().y -20));
	m_time.setPosition(sf::Vector2f(m_panel.getPosition().x + 790, m_panel.getPosition().y - 20));
	std::fixed;
	m_sstream << std::setprecision(4) << (std::roundf(t_elapsed.asSeconds() * 100) / 100);
	m_time.setString(m_sstream.str());
	m_sstream.str("");
	m_dashes.setPosition(sf::Vector2f(m_panel.getPosition().x - 820, m_panel.getPosition().y - 20));
	//m_pickUpSprite.setPosition(m_panel.getPosition().x - 2800 + (0 * 100), m_panel.getPosition().y - 250);
	for (int i = 0; i < M_MAX_PICKUPS; i++)
	{ 
		m_pickUpSprite[i].setPosition(m_panel.getPosition().x - 650  + (i * 100), m_panel.getPosition().y);
	}
	if (m_currentPickups <= 3)
	{
		m_currentPickups = t_dashNum;
	}
	m_elapsed = t_elapsed;
	sf::Vector2f dist = m_endPosition - m_startPosition;
	float distX = m_outline.getPosition().x + (m_outline.getSize().x / 2) - m_progress.getPosition().x + (m_progress.getSize().x / 2);
	//std::cout << "dist "<< std::to_string(dist.x) << std::endl;
}

void GuiPanel::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_panel);
	m_timerText.render(t_window);
	m_time.render(t_window);
	m_dashes.render(t_window);
	for (int i = 0; i < m_currentPickups; i++)
	{

		t_window.draw(m_pickUpSprite[i]);
	}
	
}

void GuiPanel::reset()
{
	m_score = 1000000;
}

void GuiPanel::addFrames(thor::FrameAnimation & animation, int x, int y, int yFirst, int yLast, float duration)
{
	for (int i = 1; i < yLast; i++)
	{
		animation.addFrame(duration, sf::IntRect(16 * i, 0, 16, 45));
	}
}
