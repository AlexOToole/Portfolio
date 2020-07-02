#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "Graph.h"
#include <map>
#include <array>
#include "UiLibrary.h"



class Game
{
public:
	Game();
	~Game();

	void run();
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void circleSetUp();
	void textSetup();
	void drawMap();
	void initiate();
	void reset();
	void isHighligthed(sf::Vector2f t_mousePos);
	void setWeigths();

	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::View m_view;
	bool m_render = true;
	static const int M_MAX_SIZE = 30;
	sf::CircleShape m_nodes[M_MAX_SIZE];
	sf::Text m_nodeName[M_MAX_SIZE];
	sf::Text m_instructions;
	sf::Vertex line[147];
	int m_weightInts[74];
	sf::Text m_weights[74];
	sf::Text m_heuristic;
	int start = 0;
	int end = 0;
	Button m_startButton;
	Button m_endButton;
	sf::Vector2i m_previousMousePos;
	sf::Vector2f m_updatedMousePos;
	bool m_mouseDown{ false };
	bool m_aStartComplete = false;
	bool m_firstClick = false;
	bool startValid = false;
	bool endValid = false;
	bool m_highlighted[M_MAX_SIZE] = { false };
};
#endif // !GAME