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
#include<vector>
using namespace std;

class parking_lots
{
  private:
    int N;
    vector<int> graph;
    vector<int> dist;
    vector<int> empty;
    vector<int> visited;
    vector<int> path_prev;

  public:
    // Default Constructor
    parking_lots();

    // Calculates Shortest distances from Source Node(0) to all nodes
    void shortest();

    /*
      Returns the Node with the smallest distance from source that
      has not been visited, if no such node exists (all nodes visited)
      then returns -1
    */
    int min_not_visited();

    /*
      Updates Shortest distances from the given node
    */
    void update_dist(int);

    void print();
};

// Member Functions Definitions
parking_lots::parking_lots()
{
  cout << "Nodes: " ;
  cin >> N;

  graph.reserve(N*N);
  dist.reserve(N);
  empty.reserve(N);
  visited.reserve(N);
  path_prev.reserve(N);

  // Allocate and Initialise the Graph
  cout << "Distances as an Adjacency Matrix:" << endl;

  for(int i = 0 ; i < N*N; i++)
  {
    int d;
    cin >> d;
    graph.push_back(d);
  }

  // Allocate and Initialise distances array
  dist[0] = 0;
  for(int i = 1; i < N; i++)
    dist[i] = INT_MAX;    // Initialise the distances to maximum possible

  // Allocate and Initialise lot empty array
  empty[0] = -1;          // Source Node not available for parking (Entrance)
  for(int i = 1; i < N; i++)
    empty[i] = 1;

  // Allocate and Initialise visited array
  for(int i = 0; i < N; i++)
    visited[i] = 0;
  
}

void parking_lots::shortest()
{
  // Source (Entrance, 0) as initial node
  int curr = 0;  
  path_prev[0] = 0;
  do
  {
    //cout << curr;
    update_dist(curr);
    visited[curr] = 1;
    curr = min_not_visited();

  } while(curr != -1);
}

int parking_lots::min_not_visited()
{
  vector<int> dist_n;
  dist_n.reserve(N);

  for(int i = 0; i < N; i++)
    dist_n[i] = dist[i]*(!visited[i]);

  int min = INT_MAX;
  int ind = -1;
  for(int i = 1; i < N; i++)
  {
    if( dist_n[i] < min && dist_n[i] != 0 )
    {
      min = dist_n[i];
      ind = i;
    }
  }
  return ind;
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
  cout << "\nTotal Nodes: " << N <<endl;

  int k = 0;
  cout << "Graph: " << endl;
  for(int i = 0 ; i < N*N; i++)
  {
    if(k == N)
    {
      k = 0;
      cout << endl;
    }
    cout << graph[i];
    k++;
  }

  cout << "\nDistances:\n";
  for(int i = 0 ; i < N; i++)
    cout << dist[i] << "\t";

  cout << "\nAvailable Lots:\n";
  for(int i = 0 ; i < N; i++)
    cout << empty[i] << "\t";

  cout << "\nVisited Nodes:\n";
  for(int i = 0 ; i < N; i++)
    cout << visited[i] << "\t";

  cout << "\nPath Prev:\n";
  for(int i = 0 ; i < N; i++)
    cout << path_prev[i] << "\t";
}

int main()
{
  parking_lots lot;

  lot.shortest();
  cout << endl;
  lot.print();
  
  return 0;
}
