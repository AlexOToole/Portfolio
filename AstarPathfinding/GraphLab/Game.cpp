#include "Game.h"


typedef GraphArc<std::pair<string, int>, int> Arc;
typedef GraphNode<std::pair<string, int>, int> Node;
void visit(Node * node) {
	cout << "Expanding: " << node->data().first << " ";
	//node->m_visited = true;
	cout << "Cost: " << node->data().second << " ";
	cout << "Estimate: " << node->m_heuristic << endl;

}

Graph<std::pair<string, int>, int > graph(30);
std::map<std::string, int> myMap;
std::vector<Node *> path;

Game::Game() :
	m_window{ sf::VideoMode{ 1000, 1000 }, "SFML" }
{
	m_view.setCenter(250, 250);
	m_view.zoom(0.8);
	m_font.loadFromFile("ASSETS/ALGER.TTF");
	textSetup();
	m_startButton.setUp(sf::Vector2f(100, -80), sf::Vector2f(200, 40));
	m_endButton.setUp(sf::Vector2f(400, -80), sf::Vector2f(200, 40));
	m_startButton.setString("Start");
	m_endButton.setString("Reset");
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		m_nodeName[i].setCharacterSize(20);
		m_nodeName[i].setFillColor(sf::Color::Black);
		m_nodeName[i].setFont(m_font);
	}

	std::pair<std::string, int> nodeLabel;
	std::array<float, 30> xPos;
	std::array<float, 30> yPos;
	int i = 0;
	int X, Y = 0;
	ifstream myfile;
	myfile.open("nodes.txt");

	while (myfile >> nodeLabel.first >> X >> Y) {
		graph.addNode(nodeLabel, i, X, Y);

		myMap[nodeLabel.first] = i;
		i++;
	}

	myfile.close();
	myfile.open("Q2Arcs.txt");

	std::string from, to;
	int weight;
	int j = 0;
	int k = 0;
	sf::Vector2f temp = { 0,0 };
	sf::Vector2f temp2 = { 0,0 };
	while (myfile >> from >> to >> weight) {
		graph.addArc(myMap[from], myMap[to], weight);
		// TODO: Show the arc weights
		m_weightInts[k] = weight;
		line[j].position = sf::Vector2f(graph.nodeIndex(myMap[from])->m_position.first, graph.nodeIndex(myMap[from])->m_position.second);
		j++;
		line[j].position = sf::Vector2f(graph.nodeIndex(myMap[to])->m_position.first, graph.nodeIndex(myMap[to])->m_position.second);
		j++;
		k++;
	}
	myfile.close();
	for (int i = 0; i < 74; i++)
	{
		m_weights[i].setString("W:" + std::to_string(m_weightInts[i]));
		std::cout << m_weightInts[i] << std::endl;
	}
	circleSetUp();
	setWeigths();
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
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

	}
}

void Game::update(sf::Time)
{
	m_previousMousePos = (sf::Mouse::getPosition(m_window));
	m_updatedMousePos = m_window.mapPixelToCoords(m_previousMousePos);
	if (m_startButton.isHighlighted(m_updatedMousePos))
	{
		if (startValid && endValid)
		{
			if (m_mouseDown)
			{
				//reset();
				initiate();
			}
		}
	}
	if (m_endButton.isHighlighted(m_updatedMousePos))
	{
		if (m_mouseDown)
		{
			reset();
		}
	}
	if (!m_aStartComplete)
	{
		isHighligthed(m_updatedMousePos);
	}
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		if (graph.nodeIndex(i)->m_visited)
		{
			m_nodes[i].setFillColor(sf::Color::Blue);
		}
		if (graph.nodeIndex(i)->m_expanded)
		{
			m_nodes[i].setFillColor(sf::Color::Red);
		}
		if (graph.nodeIndex(i)->m_onPath)
		{
			m_nodes[i].setFillColor(sf::Color::Green);
		}
	}
	m_mouseDown = false;
}

void Game::render()
{
	m_window.setView(m_view);
	m_window.clear(sf::Color::Black);
	m_startButton.render(m_window);
	m_endButton.render(m_window);
	drawMap();
	if (!m_aStartComplete)
	{
		m_window.draw(m_instructions);
	}
	else
	{
		for (int i = 0; i < 74; i++)
		{
			m_window.draw(m_weights[i]);
		}
	}

	m_window.display();
}

void Game::circleSetUp()
{
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		m_nodes[i].setRadius(20);
		m_nodes[i].setOrigin(10, 10);
		m_nodes[i].setFillColor(sf::Color::White);
		m_nodes[i].setPosition(sf::Vector2f(graph.nodeIndex(i)->m_position.first, graph.nodeIndex(i)->m_position.second));
		m_nodeName[i].setString(graph.nodeIndex(i)->data().first);
		m_nodeName[i].setOrigin(-2.5, 0);
		m_nodeName[i].setPosition(sf::Vector2f(graph.nodeIndex(i)->m_position.first, graph.nodeIndex(i)->m_position.second));
	}
	//m_nodes[start].setOutlineColor(sf::Color::Yellow);
	//m_nodes[end].setOutlineColor(sf::Color::Yellow);
	//m_nodes[start].setOutlineThickness(5);
	//m_nodes[end].setOutlineThickness(5);


	for (int i = 0; i < 147; i++)
	{
		line[i].color = sf::Color::Red;
	}
}

void Game::textSetup()
{
	for (int i = 0; i < 74; i++)
	{
		m_weights[i].setCharacterSize(24);
		m_weights[i].setOrigin(sf::Vector2f(m_heuristic.getLocalBounds().width / 2, m_heuristic.getLocalBounds().height / 2));
		m_weights[i].setFillColor(sf::Color::Cyan);
		m_weights[i].setFont(m_font);
		m_weights[i].setPosition(sf::Vector2f(-300,-300));
	}
	m_instructions.setString("Please select two nodes, Do not select the same node twice");
	m_instructions.setCharacterSize(16);
	m_instructions.setOrigin(sf::Vector2f(m_instructions.getLocalBounds().width / 2, m_instructions.getLocalBounds().height / 2));
	m_instructions.setFillColor(sf::Color::White);
	m_instructions.setFont(m_font);
	m_instructions.setPosition(sf::Vector2f(-10, -50));
}

void Game::drawMap()
{
	m_window.draw(line, 147, sf::Lines);
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		m_window.draw(m_nodes[i]);
		m_window.draw(m_nodeName[i]);
	}
}

void Game::initiate()
{
	//bool valid = false;
	//while (valid == false)
	//{ 
	//		std::cout << "Enter a whole number between 0 and 29" << std::endl;
	//		std::cout << "Enter a start point" << std::endl;
	//		std::cin >> start;
	//		std::cout << "Enter a end point" << std::endl;
	//		std::cin >> end;
	//		if (start < 0 || start > 29 || end < 0 || end > 29 || start == end)
	//		{
	//			std::cout << "Error you entered incompatable numbers" << std::endl;
	//		}
	//		if (start >= 0 && start <= 29 && end >= 0 && end <= 29 && start != end)
	//		{
	//			valid = true;
	//		}
	//	}
	//	for (int i = 0; i < M_MAX_SIZE; i++)
	//	{
	//		if (m_highlighted[i])
	//		{
	//			m_nodes[i].setOutlineColor(sf::Color::Yellow);
	//			m_nodes[i].setOutlineThickness(5);
	//			if (!startValid)
	//			{
	//				if (m_mouseDown)
	//				{
	//					start = i;
	//				}
	//			}
	//			if (startValid && !endValid)
	//			{
	//				if (m_mouseDown)
	//				{
	//					end = i;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			m_nodes[i].setOutlineThickness(0);
	//		}
	//	}
	//	if (startValid && endValid)
	//	{
	//		valid = true;
	//	}
	//}
	m_nodes[start].setOutlineColor(sf::Color::Yellow);
	m_nodes[end].setOutlineColor(sf::Color::Yellow);
	m_nodes[start].setOutlineThickness(5);
	m_nodes[end].setOutlineThickness(5);
	graph.aStar(graph.nodeIndex(start), graph.nodeIndex(end), visit, path);
	m_aStartComplete = true;
}

void Game::reset()
{
	m_window.setView(m_view);
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		m_nodes[i].setOutlineThickness(0);
		m_nodes[i].setFillColor(sf::Color::White);
		graph.nodeIndex(i)->m_expanded = false;
		graph.nodeIndex(i)->m_visited = false;
		graph.nodeIndex(i)->m_onPath = false;
		graph.nodeIndex(i)->data().second = 0;
		graph.nodeIndex(i)->m_heuristic = 0;
	}
	start = 0;
	end = 0;
	startValid = false;
	endValid = false;
	m_aStartComplete = false;
}

void Game::isHighligthed(sf::Vector2f t_mousePos)
{
	for (int i = 0; i < M_MAX_SIZE; i++)
	{
		//calculates the distance between mouse and circle centre
		float distX = t_mousePos.x - m_nodes[i].getPosition().x;
		float distY = t_mousePos.y - m_nodes[i].getPosition().y;
		if (sqrt((distX * distX) + (distY * distY)) < m_nodes[i].getRadius())
		{
			m_highlighted[i] = true;
			m_nodes[i].setOutlineColor(sf::Color::Yellow);
			m_nodes[i].setOutlineThickness(5);
			if (!m_firstClick)
			{
				if (m_mouseDown)
				{
					start = i;
					startValid = true;
					m_firstClick = true;
				}
			}
			else if (m_firstClick)
			{
				if (m_mouseDown)
				{
					end = i;
					endValid = true;
					m_firstClick = false;
				}
			}
		}
		else
		{
			m_highlighted[i] = false;
			m_nodes[i].setOutlineThickness(0);
		}
	}
}

void Game::setWeigths()
{
	//row 1
	m_weights[69].setPosition(sf::Vector2f(25,-30));
	m_weights[70].setPosition(sf::Vector2f(125, -30));
	m_weights[3].setPosition(sf::Vector2f(220, -30));
	m_weights[72].setPosition(sf::Vector2f(320, -30));
	m_weights[62].setPosition(sf::Vector2f(420, -30));

	//row 2
	m_weights[7].setPosition(sf::Vector2f(0, 25));
	m_weights[7].setRotation(90);
	m_weights[2].setPosition(sf::Vector2f(55, 15));
	m_weights[2].setRotation(45);
	m_weights[5].setPosition(sf::Vector2f(150, 15));
	m_weights[5].setRotation(45);
	m_weights[9].setPosition(sf::Vector2f(345, 15));
	m_weights[9].setRotation(45);
	m_weights[14].setPosition(sf::Vector2f(445, 35));

	//row 3
	m_weights[8].setPosition(sf::Vector2f(215, 70));
	m_weights[13].setPosition(sf::Vector2f(420, 70));

	//row 4
	m_weights[10].setPosition(sf::Vector2f(0, 120));
	m_weights[10].setRotation(90);
	m_weights[11].setPosition(sf::Vector2f(100, 120));
	m_weights[11].setRotation(90);
	m_weights[19].setPosition(sf::Vector2f(150, 120));
	m_weights[19].setRotation(45);
	m_weights[17].setPosition(sf::Vector2f(250, 130));
	m_weights[23].setPosition(sf::Vector2f(330, 100));
	m_weights[23].setRotation(45);
	m_weights[15].setPosition(sf::Vector2f(440, 120));
	m_weights[15].setRotation(90);
	m_weights[16].setPosition(sf::Vector2f(540, 120));
	m_weights[16].setRotation(90);

	//row 5
	m_weights[12].setPosition(sf::Vector2f(125, 175));

	//row 6
	m_weights[32].setPosition(sf::Vector2f(0, 220));
	m_weights[32].setRotation(90);
	m_weights[35].setPosition(sf::Vector2f(120, 220));
	m_weights[35].setRotation(45);
	m_weights[40].setPosition(sf::Vector2f(240, 210));
	m_weights[40].setRotation(90);
	m_weights[38].setPosition(sf::Vector2f(280, 210));
	m_weights[38].setRotation(90);
	m_weights[41].setPosition(sf::Vector2f(330, 225));
	m_weights[41].setRotation(45);
	m_weights[42].setPosition(sf::Vector2f(365, 220));
	m_weights[42].setRotation(26);
	m_weights[54].setPosition(sf::Vector2f(540, 220));
	m_weights[54].setRotation(90);

	//row 7
	m_weights[22].setPosition(sf::Vector2f(25, 280));
	m_weights[37].setPosition(sf::Vector2f(125, 280));

	//row 8
	m_weights[27].setPosition(sf::Vector2f(0, 300));
	m_weights[27].setRotation(90);
	m_weights[20].setPosition(sf::Vector2f(150, 320));
	m_weights[29].setPosition(sf::Vector2f(340, 310));
	m_weights[29].setRotation(90);
	m_weights[73].setPosition(sf::Vector2f(420, 310));
	m_weights[73].setRotation(45);

	//row 9
	m_weights[63].setPosition(sf::Vector2f(25, 390));
	m_weights[55].setPosition(sf::Vector2f(125, 390));
	m_weights[21].setPosition(sf::Vector2f(220, 390));
	m_weights[18].setPosition(sf::Vector2f(320, 390));
	//m_weights[6].setPosition(sf::Vector2f(125, 50));
	//m_weights[7].setPosition(sf::Vector2f(220, 50));
	//m_weights[8].setPosition(sf::Vector2f(320, 50));
	//m_weights[9].setPosition(sf::Vector2f(420, 50));
}
