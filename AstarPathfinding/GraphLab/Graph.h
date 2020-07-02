#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <utility>

using namespace std;

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

template<class NodeType, class ArcType>
class NodeSearchCostComparer
{
public:
	// typedef the classes to make our lives easier.
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	bool operator()(Node * n1, Node * n2)
	{
		std::pair<std::string, int> p1 = n1->data();
		std::pair<std::string, int> p2 = n2->data();
		return p1.second + n1->m_heuristic > p2.second + n2->m_heuristic;
	}
};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    This is the graph class, it contains all the
//                  nodes.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph 
{
public:           
	// typedef the classes to make our lives easier.
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;


    // Constructor and destructor functions
    Graph( int size );
    ~Graph();

    // Accessors
    Node * nodeIndex(int index) const {
		return m_nodes.at(index);
    }

    // Public member functions.
    bool addNode( NodeType data, int index, int t_x, int t_y);
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* pNode, std::function<void(Node *)> f_visit);
    void breadthFirst( Node* pNode, std::function<void(Node *)> f_visit);
	void adaptedBreadthFirst( Node* pCurrent, Node* pGoal );
	void ucs(Node* start, Node* dest, std::function<void(Node *)> f_visit,
		std::vector<Node *> & path);
	void aStar(Node* start, Node* dest, std::function<void(Node *)> f_visit,
		std::vector<Node *> & path);
private:
	// ----------------------------------------------------------------
	//  Description:    A container of all the nodes in the graph.
	// ----------------------------------------------------------------

	std::vector<Node *> m_nodes;
	

};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph( int maxNodes ) : m_nodes( maxNodes, nullptr) 
{  
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   for( int index = 0; index < m_nodes.size(); index++ ) {
        if( m_nodes[index] != nullptr ) {
			delete m_nodes.at(index);
        }
   }
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index, int t_x, int t_y ) {
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if ( nullptr == m_nodes.at(index) ) {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
	  m_nodes.at(index) = new Node;
	  m_nodes.at(index)->setData(data);
	  m_nodes.at(index)->setMarked(false);
	  m_nodes.at(index)->m_position.first = t_x;
	  m_nodes.at(index)->m_position.second = t_y;
    }
   
    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) {
     // Only proceed if node does exist.
     if( nullptr != m_nodes.at(index) ) {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_nodes.size(); node++ ) {
              // if the node is valid...
              if( nullptr != m_nodes.at(node) ) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_nodes.at(node)->getArc(m_nodes.at(index) );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_nodes.at(index);
		m_nodes.at(index) = nullptr;       
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) {
     bool proceed = true; 
     // make sure both nodes exist.
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if( m_nodes.at(from)->getArc( m_nodes.at(to) ) != nullptr ) {
         proceed = false;
     }

     if (proceed == true) {
        // add the arc to the "from" node.
		 m_nodes.at(from)->addArc(m_nodes.at(to), weight );
     }
        
     return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) {
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( nullptr == m_nodes.at(from) || nullptr == m_nodes.at(to) ) {
         nodeExists = false;
     }

     if (nodeExists == true) {
        // remove the arc.
		 m_nodes.at(from)->removeArc(m_nodes.at(to) );
     }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) {
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( nullptr != m_nodes.at(from) && nullptr != m_nodes.at(to) ) {
         arc = m_nodes.at(from)->getArc(m_nodes.at(to) );
     }
                
     return arc;
}

// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() {
     for( int index = 0; index < m_nodes.size(); index++ ) {
          if( nullptr != m_nodes.at(index) ) {
			  m_nodes.at(index)->setMarked(false);
          }
     }
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst( Node* node, std::function<void(Node *)> f_visit ) {
     if( nullptr != node ) {
           // process the current node and mark it
           f_visit( node );
           node->setMarked(true);

           // go through each connecting node
           auto iter = node->arcList().begin();
           auto endIter = node->arcList().end();
        
		   for( ; iter != endIter; ++iter) {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) {
                   depthFirst( (*iter).node(), f_visit);
                }            
           }
     }
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst( Node* node, std::function<void(Node *)> f_visit) {
   if( nullptr != node ) {
	  queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( node );
      node->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) {
         // process the node at the front of the queue.
		 f_visit( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
         auto iter = nodeQueue.front()->arcList().begin();
         auto endIter = nodeQueue.front()->arcList().end();
         
		 for( ; iter != endIter; iter++ ) {
              if ( (*iter).node()->marked() == false) {
				 // mark the node and add it to the queue.
                 (*iter).node()->setMarked(true);
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
      }
   }  
}


// ----------------------------------------------------------------
//  Name:           adaptedBreadthFirst
//  Description:    Performs a breadth-first traversal the starting node
//                  specified as an input parameter, terminating at the goal.
//  Arguments:      The first parameter is the starting node.
//                  The second parameter is the goal node.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::adaptedBreadthFirst(Node* current, Node *goal)
{
	//Algorithm
	bool goalReached = false;
	std::queue<Node*> nodeQueue;
	nodeQueue.push(current);
	current->setMarked(true);

	// (*iter).node() represents a child node (endpoint of an arc)

	while (nodeQueue.size() != 0 && goalReached == false)
	{
		auto iter = nodeQueue.front()->arcList().begin();
		auto endIter = nodeQueue.front()->arcList().end();

		for (; iter != endIter; iter++)
		{
			if ((*iter).node() == goal)
			{
				goal->setPrevious(nodeQueue.front());
				goalReached = true;
			}
			if ((*iter).node()->marked() == false) 
			{
				// mark the node and add it to the queue.
				(*iter).node()->setPrevious(nodeQueue.front());
				(*iter).node()->setMarked(true);
				nodeQueue.push((*iter).node());
			}
		}
		nodeQueue.pop();
	}
	/*let goalReached = false
	enqueue(starting cell)
	mark(starting cell)
	while the queue is not empty AND goalReached == false
		for each child of the queue.front() AND
			goalReached == false
			if (child == goal)
				goalReached = true
				set previous pointer of goal to queue.front()
				end if
				if (notMarked(child))
					set previous pointer of child to queue.front()
					cell
					mark(child)
					enqueue(child)
					end if
					end for
					remove the next cell from the queue
					end while
					*/
}
template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::ucs(Node * start, Node * dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path)
{
	Node *s = start;
	std::priority_queue<Node *, std::vector<Node *>, NodeSearchCostComparer<NodeType, ArcType> > nodeQueue;
	
	// Set each path cost to infinity except for the start
	for (Node * node : m_nodes)
	{
		if (node != start)
		{
			NodeType data = node->data();
			data.second = std::numeric_limits<int>::max();
			node->setData(data);
		}
	}
	
	nodeQueue.push(s);
	s->setMarked(true);
	
	while (nodeQueue.size() != 0 && nodeQueue.top() != dest)
	{
		auto iter = nodeQueue.top()->arcList().begin();
		auto endIter = nodeQueue.top()->arcList().end();
		f_visit(nodeQueue.top());
		for (; iter != endIter; iter++)
		{
			Arc arc = (*iter);
			//arc.weight();
			// Path cost...
			 NodeType data = nodeQueue.top()->data();
			// data.first
			// Getting a ref to the child node
			 Node * child = (*iter).node();

			 if ((*iter).node() != nodeQueue.top()->previous())
			 {
				 auto distC = arc.weight() + data.second;
				 if (distC < child->data().second)
				 {
					 // Update the pair stored at this child node.
					 NodeType data;
					 data.first = child->data().first;
					 data.second = distC;
					 child->setData(data);

					 //Set previous pointer of c to pq.top()
					 (*iter).node()->setPrevious(nodeQueue.top());
				 }
				 if ((*iter).node()->marked() == false)
				 {
					 // mark the node and add it to the queue.
					 (*iter).node()->setMarked(true);
					 nodeQueue.push((*iter).node());
				 }
			 }
		}
		nodeQueue.pop();
	}
	Node *temp = nodeQueue.top();
	std::cout << temp->data().second << std::endl;

	// Loop backwards starting with dest
	 //Node * current = dest;
	 //while (current->previous() != nullptr)
	 //{
		// path.push_back(current);
	 //}
	//    path.push_back(current);
	//   
}


//Let s = the starting node, g = goal node
//Let pq = a new priority queue
//Initialise g[s] to 0
//For each node v in graph G
//Calculate h[v] // Compute estimated distance to goal for each node.
//Initialise g[v] to infinity // Don’t yet know the distances to these nodes
//Add s to the pq
//Mark(s)
//While the queue is not empty AND pq.top() != g
//For each child node c of pq.top()
//If(c != previous(pq.top())
//	Let distC = h(c) + g(c) // g(c) is actual path cost to child
//	If(distC < f(c))
//	let f[c] = distC
//	Set previous pointer of c to pq.top()
//	End if
//	If(notMarked(c))
//	Add c to the pq
//	Mark(c)
//	End if
//	End if
//	End for
//	Remove pq
template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::aStar(Node * start, Node * dest, std::function<void(Node*)> f_visit, std::vector<Node*>& path)
{
	this->clearMarks();
	Node *s = start;
	std::priority_queue<Node *, std::vector<Node *>, NodeSearchCostComparer<NodeType, ArcType> > nodeQueue;

	// Set each path cost to infinity except for the start
	for (Node * node : m_nodes)
	{
		if (node != start)
		{
			NodeType data = node->data();
			data.second = std::numeric_limits<int>::max() - 10000;
			node->setData(data);
			// node->m_x - dest-m_x
			node->m_heuristic = sqrt((dest->m_position.first - node->m_position.first) * (dest->m_position.first - node->m_position.first)
				+ (dest->m_position.second - node->m_position.second) * (dest->m_position.second - node->m_position.second));// sqrt((x2-x1)2 + (y2-y1)2)
		}
	}

	nodeQueue.push(s);
	s->setMarked(true);

	while (nodeQueue.size() != 0 && nodeQueue.top() != dest)
	{
		auto iter = nodeQueue.top()->arcList().begin();
		auto endIter = nodeQueue.top()->arcList().end();
	
		f_visit(nodeQueue.top());
		nodeQueue.top()->m_expanded = true;
		for (; iter != endIter; iter++)
		{
			Arc arc = (*iter);
			//arc.weight();
			// Path cost...
			NodeType data = nodeQueue.top()->data();
			// data.first
			// Getting a ref to the child node
			Node * child = (*iter).node();

			if ((*iter).node() != nodeQueue.top()->previous())
			{
				auto distC = (*iter).node()->m_heuristic + data.second + arc.weight();
				if (distC < (*iter).node()->data().second + (*iter).node()->m_heuristic) //g(c) -> child->data().second
				{
					// Update the pair stored at this child node.					
					NodeType childData = child->data();					
					childData.second = data.second + arc.weight();
					child->setData(childData);
					child->m_visited = true;

					//Set previous pointer of c to pq.top()
					(*iter).node()->setPrevious(nodeQueue.top());
				}
				if ((*iter).node()->marked() == false)
				{
					// mark the node and add it to the queue.
					(*iter).node()->setMarked(true);
					nodeQueue.push((*iter).node());
				}
			}
		}
		
		nodeQueue.pop();
	}
	// let temp = dest;
	// follow previous pointers back to start
	//  add each node to the vector
	//sets up temp node
	path.clear();
	Node * temp = dest;

	//outputs while it not null
	while (temp != start)
	{
		path.push_back(temp);
		temp->m_onPath = true;
		temp = temp->previous();

		
	}
	path.push_back(start);
	start->m_onPath = true;
	std::cout << "Number of Nodes in the path : " << path.size() << std::endl;
	std::cout << std::endl;
}


#include "GraphNode.h"
#include "GraphArc.h"


#endif
