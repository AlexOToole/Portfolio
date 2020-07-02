#include "Game.h"

using namespace std;

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 

#endif 

//typedef GraphArc<std::pair<string, int>, int> Arc;
//typedef GraphNode<std::pair<string, int>, int> Node;
//
//void visit(Node * node) {
//	cout << "Expanding: " << node->data().first << " " ;
//	cout << "Cost: " << node->data().second << " ";
//	cout << "Estimate: " << node->m_heuristic << endl;
//	
//
//}

int main(int argc, char *argv[]) {
	Game game;
	game.run();
	////Graph<std::string, int> graph(6);
	//// Meaning of template arguments below:
	//// pair<string, int> is the data we are storing at each node
	//// int is the arc type (the data stored at each edge or arc)
	//Graph<std::pair<string, int>, int > graph(30);
	//std::map<std::string, int> myMap;

	//std::pair<std::string, int> nodeLabel;
	//std::array<float, 30> xPos;
	//std::array<float, 30> yPos;
	//int i = 0;
	//int X, Y = 0;
	//ifstream myfile;
	//myfile.open("nodes.txt");

	//while (myfile >> nodeLabel.first >> X >> Y) {
	//	graph.addNode(nodeLabel, i, X, Y);
	//	myMap[nodeLabel.first] = i;
	//	i++;
	//}

	//myfile.close();
	//myfile.open("Q2Arcs.txt");

	//std::string from, to;
	//int weight;
	//while (myfile >> from >> to >> weight) {
	//	graph.addArc(myMap[from], myMap[to], weight);
	//}
	//myfile.close();

	//std::vector<Node *> path;
	//graph.aStar(graph.nodeIndex(0), graph.nodeIndex(9), visit, path);
	// Now traverse the graph.
	//graph.breadthFirst(graph.nodeIndex(0), visit);
	//graph.adaptedBreadthFirst(graph.nodeIndex(0), graph.nodeIndex(15));
	////15->4->0
	//// traverse the previous pointers of the goal
	// Node * temp = graph.nodeIndex(15);
	// while (temp->previous() != nullptr)
	// {
	//	cout << temp->data() + " " + "-> ";
	//	temp = temp->previous();
	// }
	// std::cout << temp->data();
	// std::cout << std::endl;
	
	
	system("PAUSE");

}
