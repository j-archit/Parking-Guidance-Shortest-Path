/*
  INTELLIGENT GUIDANCE PARKING SYSTEM USING MODIFIED DIJKSTRA’S ALGORITHM

  Implementation of the software part of the said proposal for MTE component of
  IT353 - Data Structures and Algorithms.

  Submitted by
  Archit Jain     2K18/EC/041
  Deepanshu Pal   2K18/EC/060
*/

#include<iostream>
#include<climits>
using namespace std;

class edge_node
{
  /*
    int nodeID, weight;   // Node Number, weight of edge from parent vertex
    edge_note* nextedge;  // Pointer to next edge 
  */
  public:
    int nodeID, weight;
    edge_node* nextedge;

    edge_node(int ID, int edge)   
    {
      nodeID = ID;
      weight = edge;
      nextedge = nullptr;
    } 
    void print()
    {
      cout << "Edge" << nodeID << ":" << weight << ":" << nextedge << endl;
    }
};

class vertex 
{
  /*
    int nodeID;           // Node Number
    edge_note* nextedge;  // Pointer to the first node that is edge connected to the vertex
    vertex* next;         // Pointer to the Next Vertex in the DLL
    int dist;             // Shortest Distance from Source Node
    int pathprev;         // Previous Node of the Shortest Path
    bool visited          // For use with the Dijkstra's Algo, indicates whether the node has been visited before
    bool lotempty;        // Indicates whether the Node is currently empty 
  */
  public:
    int nodeID;           
    edge_node* nextedge;     
    vertex* next;          
    int dist;           
    int pathprev;
    bool visited;
    bool lotempty;     
  
    vertex()
    {
      nodeID = 0;
      nextedge = nullptr;
      next = nullptr;
      dist = 0;
      pathprev = 0;
      visited = false;
      lotempty = false;
    }

    vertex(int ID)
    {
      nodeID = ID;
      nextedge = nullptr;
      next = nullptr;
      dist = INT32_MAX;
      pathprev = ID;
      visited = false;
      lotempty = false;
    }    

    void print()
    {
      cout << "IDed Vertex "<< nodeID << ":" << nextedge << ":" << next << ":" << dist << ":" << pathprev << ":" << visited << ":" << lotempty << endl;
    }
};

class parking_lots
{
  /*
    Requires the use of vertex and the edge node classes.
    Stores everything about the parking lot, the structure and the nodes, 
    distances (edge weights)
  */
  private:
    int N;
    vertex source;

    // Builds the required list for the graph
    void buildgraph();

    // Returns the Node with the smallest distance from source that
    // has not been visited, if all nodes have been visited, then this return -1
    int min_not_visited();

    // Updates Shortest distances to all connected nodes from the 
    // given node and it's path_prev
    void update_dist(int ID);

    // Calculates Shortest distances from Source Node(0) to all nodes
    void shortest();
    
  public:
    // Default Constructor
    parking_lots();

    // Prints all the graph info list
    void print();

    // Prints Current Distances of all vertices
    void print_dist();

    // Prints Shortest Path Node by Node
    void print_path();

    // Reserves a parking node and Prints the Path to it
    void provide_lot();
};

// Member Functions Definitions
void parking_lots::buildgraph()
{
  cout << "Number of Nodes: " ;
  cin >> N;

  // Build Vertices of the List
  vertex* curr = &source;
  for(int i = 1; i < N; i++)
  {
    curr->next = new vertex(i);
    curr = curr->next;
  }
  
  // Initialise the Graph
  int val;
  vertex* vert = &source;
  
  cout << "Distances as an Adjacency Matrix:" << endl;
  for(int i = 0 ; i < N; i++)
  { 
    edge_node* edge = vert->nextedge;
    for (int j = 0; j < N; j++)
    {
      cin >> val;
      if(val == -1)
      {
          continue;
      }
      edge_node* e = new edge_node(j, val);
      if(vert->nextedge == nullptr)
      {
        vert->nextedge = e;
        edge = e;
      }
      else
      {
        edge->nextedge = e;
        edge = e;
      }
    }
    vert = vert->next;
  }
}

int parking_lots::min_not_visited()
{
  int ID = -1;
  vertex* current = &source;
  int min = INT32_MAX;
  while(current != nullptr)
  {
    if(!current->visited)
    {
      if(current->dist < min)
      {
        min = current->dist;
        ID = current->nodeID;
      }
    }
    current = current->next;
  }
  return ID;
}

void parking_lots::update_dist(int ID)
{
  vertex* vert = &source;
  // Reach the source vertex 
  for(int i = 0; i < ID; i++)
    vert = vert->next;

  edge_node* edge = vert->nextedge; 
  
  // To Traverse the vertex list for updating the Shortest Distance and Path Previous
  vertex* curr = &source;
  int trav = 0;
  
  while(edge != nullptr)
  {
    for(int i = 0; i < edge->nodeID - trav; i++)
      curr = curr->next;
    trav = edge->nodeID;
    if(curr->dist > vert->dist + edge->weight)
    {
      curr->dist = vert->dist + edge->weight;
      curr->pathprev = vert->nodeID;
    }

    edge = edge->nextedge;
  }
  vert->visited = true;
}

parking_lots::parking_lots()
{
  buildgraph();
  shortest();
  print();
  print_dist();
  print_path();
}

void parking_lots::shortest()
{
  int node = 0;
  while(node != -1)
  { 
    update_dist(node);
    node = min_not_visited();
  }
}

void parking_lots::print()
{
  vertex* current = &source;
  do
  {
    edge_node* edge = current->nextedge;

    current->print();
    current = current->next;
    do
    {
      edge->print();
      edge = edge->nextedge;
    } while (edge != nullptr);
    
  } while (current != nullptr);
  
}

void parking_lots::print_dist()
{
  vertex* vert = &source;
  // Reach the source vertex 
  cout << "Distances" << endl;
  for(int i = 0; i < N; i++)
  {
    cout << "Vertex " << vert->nodeID << ":" << vert->dist <<endl;
    vert = vert->next;
  } 
}

void parking_lots::print_path()
{
  int* path_arr = new int[N];
  vertex* vert = &source;
  // Reach the source vertex 
  for(int i = 0; i < N; i++)
  {
    *(path_arr + i) = vert->pathprev;
    vert = vert->next;
  }
  cout << "Path" << endl;
  for(int node = 0; node < N; node++)
  {
    int p = node;
    cout << "Vertex " << node << ":";
    while( p != 0 )
    {
      cout << *(path_arr + p) << " ";
      p = *(path_arr + p);
    }
    cout<< endl;
  }
}

void parking_lots::provide_lot()
{

}

int main()
{
  parking_lots lot;

  return 0;

  int exit_cont = 1;
  while(exit_cont)
  {
    cout << "Enter 1 for a Ticket, 0 to exit" << endl;
    cin >> exit_cont;
    if(!exit_cont)
      break;
    //lot.provide_lot();
  }
}
