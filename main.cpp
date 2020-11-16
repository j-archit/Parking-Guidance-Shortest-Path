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
#include<fstream>
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
      lotempty = true;
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
    int* path_arr;

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

    // Initializes the path_arr with path prev values
    void arr_path();
    
  public:
    // Default Constructor
    parking_lots();

    // Prints all the graph info
    void print();

    /* 
      Prints the values of a member variable
      1 - distance
      2 - lotempty
    */
    void print_mem(int mem);

    /* 
      Prints Shortest Path 
      To all Nodes if no parameter is passed
      Or to the Node passed as parameter
    */
    void print_path(int ID = 0);

    // Returns the number of Available Empty Lots now.
    int available();

    // Reserves a parking node and Prints the Path to it
    void provide_lot();

    // Frees the empty parking lot with nodeID, ID - Under developement
    void free_lot(int ID);
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

void parking_lots::shortest()
{
  int node = 0;
  while(node != -1)
  { 
    update_dist(node);
    node = min_not_visited();
  }
}

void parking_lots::arr_path()
{
  path_arr = new int[N];
  vertex* vert = &source;
  // Reach the source vertex 
  for(int i = 0; i < N; i++)
  {
    path_arr[i] = vert->pathprev;
    vert = vert->next;
  }
}

parking_lots::parking_lots()
{
  buildgraph();
  shortest();
  arr_path();
}

void parking_lots::print()
{
  vertex* current = &source;
  while (current != nullptr)
  {
    edge_node* edge = current->nextedge;

    current->print();
    current = current->next;
    while (edge != nullptr)
    {
      edge->print();
      edge = edge->nextedge;
    } 
  }
}

void parking_lots::print_mem(int mem)
{
  vertex* vert = &source;
  // Reach the source vertex 
  mem == 1 ? cout << "Distances" << endl : cout << "Availability" <<endl;
  int k;
  for(int i = 0; i < N; i++)
  {
    mem == 1 ? k = vert->dist : k = vert->lotempty;
    cout << "Vertex " << vert->nodeID << ":" << k <<endl;
    vert = vert->next;
  } 
}

void parking_lots::print_path(int ID)
{
  int node = ID;
  for( ;node < N; node++)
  {
    int p = node;
    cout << "Lot " << node << ":";
    while( p != 0 )
    {
      cout << *(path_arr + p) << " ";
      p = *(path_arr + p);
    }
    cout << "0" << endl;
    if( ID != 0 )
      break;
  }
}

int parking_lots::available()
{
  int count = 0;
  vertex* vert = &source;
  while(vert != nullptr)
  {
    if(vert->lotempty)
      count++;
    vert = vert->next;
  }
  return count;
}

void parking_lots::provide_lot()
{
  int min = INT32_MAX;
  int lotID = 0;
  vertex* vert = source.next;
  while(vert != nullptr)
  {
    if(vert->lotempty && vert->dist < min)
    {
      min = vert->dist;
      lotID = vert->nodeID;
      cout << lotID << endl;
    }
    vert = vert->next;
  }
  if(lotID == 0)
    cout << "The Parking is Full right now, We are sorry for the Inconvenience caused." << endl;
  else
  {
    cout << "The following parking has been reserved for you: ";
    print_path(lotID);
    vert = &source;
    while(vert->nodeID != lotID)
      vert = vert->next;
    vert->lotempty = false;
  }
  
}

void parking_lots::free_lot(int ID)
{
  vertex* vert = &source;
  while(vert->nodeID != ID)
    vert = vert->next;
  vert->lotempty = true;
}


int main()
{
  fstream f;
  
  parking_lots lot;

  int menu = 5;
  while( menu )
  {
    cout << ":Welcome to Automated Parking:" << endl;
    cout << lot.available() << " space(s) available" << endl;
    cout << "1-Parking Ticket " << endl;
    cout << "2-Leave Parking " << endl;
    cout << "0-Exit" << endl;
    cout << "Your Choice:";
    cin >> menu;
    switch (menu)
    {
        case 1: {
          lot.provide_lot();
          break;
        }
        case 2: {
          cout << "Enter LotID: ";
          cin >> menu;
          lot.free_lot(menu);
        }
        case 0: break;
    }  
  }
  return 0;
}
