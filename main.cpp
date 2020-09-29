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

class parking_lots
{
  private:
    int N;
    int* graph;
    int* dist;
    int* empty;
    int* visited;
    int* path_prev;

  public:
    // Default Constructor
    parking_lots();

    // Calculates Shortest distances from Source Node(0) to all nodes
    void shortest();

    /*
      Returns the Node with the smallest distance from source that
      has not been visited
    */
    int min_not_visited();

    /*
      Checks if all nodes visited?
      returns 1 if not visited, 0 if all nodes have been visited
    */
    int not_vis();

    /*
      Updates Shortest distances from the given node
    */
    void update_dist(int);

    void print();

    void delete_mem();
};

// Member Functions Definitions
parking_lots::parking_lots()
{
  cout << "Nodes: " ;
  cin >> N;

  // Allocate and Initialise the Graph
  cout << "Distances as an Adjacency Matrix:" << endl;
  graph = new int[N*N];
  for(int i = 0 ; i < N*N; i++)
    cin >> *(graph+i*sizeof(int));

  // Allocate and Initialise distances array
  dist = new int[N];
  dist[0] = 0;
  for(int i = 1; i < N; i++)
    dist[i] = INT_MAX;    // Initialise the distances to maximum possible

  // Allocate and Initialise lot empty array
  empty = new int[N];
  empty[0] = -1;          // Source Node not available for parking (Entrance)
  for(int i = 1; i < N; i++)
    empty[i] = 1;

  cout<<"3";
}

void parking_lots::shortest()
{
  cout<<"2";
  // Allocate and Initialise visited array
  visited = new int[N];
  for(int i = 0; i < N; i++)
    visited[i] = 0;

  // Source (Entrance, 0) as initial node
  int curr;
  path_prev[0] = 0;
  cout<<"1";
  while(not_vis())
  {
    curr = min_not_visited();
    cout << curr;
    update_dist(curr);
    visited[curr] = 1;

    cout<<"heree";
  }
}

int parking_lots::min_not_visited()
{
  float* dist_n = new float[N];
  for(int i = 0; i < N; i++)
    dist_n[i] = dist[i]*(!visited[i]);

  float min = dist_n[0];
  int ind = 0;
  for(int i = 1; i < N; i++)
  {
    if( dist_n[i] <= min && dist_n != 0 )
    {
      min = dist_n[i];
      ind = i;
    }
  }
  return ind;
}

int parking_lots::not_vis()
{
  for(int i = 0; i < N; i++)
    if(visited[i] == 0)
      return 1;
  return 0;
}

void parking_lots::update_dist(int node)
{
  int start = N*node;
  for(int i = 0; i < N; i++)
  {
    if(graph[start + i] != 0 && visited[i] != 1)
    {
      if(dist[i] > dist[node] + graph[start + i])
      {
        dist[i] = dist[node] + graph[start + i];
        path_prev[i] = node;
      }
    }
  }
}

void parking_lots::print()
{
  // Printing Everything
  cout << "Total Nodes: " << N <<endl;

  int k = 0;
  cout << "Graph: " << endl;
  for(int i = 0 ; i < N*N; i++)
  {
    if(k == N)
    {
      k = 0;
      cout << endl;
    }
    cout << *(graph+i*sizeof(int));
    k++;
  }

  cout << "\nDistances: ";
  for(int i = 0 ; i < N; i++)
    cout << dist[i] << "\t";

  cout << "\nAvailable Lots: ";
  for(int i = 0 ; i < N; i++)
    cout << empty[i] << "\t";

  cout << "\nVisited Nodes: ";
  for(int i = 0 ; i < N; i++)
    cout << visited[i] << "\t";

  cout << "\nPath Prev: ";
  for(int i = 0 ; i < N; i++)
    cout << path_prev[i] << "\t";
}

void parking_lots::delete_mem()
{
  delete [] graph;
  delete [] dist;
  delete [] empty;
  delete [] visited;
  delete [] path_prev;
}

int main()
{
  parking_lots lot;
  lot.shortest();
  lot.print();

  lot.delete_mem();
  return 0;
}
