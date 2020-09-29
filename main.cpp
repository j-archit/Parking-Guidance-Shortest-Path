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
    float* graph;
    float* dist;
    int* empty;

  public:
    parking_lots();
    void shortest();        // Calculates Shortest distances from Source Node(0)
};

parking_lots::parking_lots()
{
  cout << "Parking Lots + 1: " ;
  cin >> N;

  // Allocate and Initialise the Graph
  cout << "Distances as an Adjacency Matrix:" << endl;
  graph = new float[N*N];
  for(int i = 0 ; i < N*N; i++)
    cin >> *(graph+i*sizeof(int));

  // Allocate and Initialise distances array
  dist = new float[N];
  dist[0] = 0;
  for(int i = 1; i < N; i++)
    dist[i] = INT_MAX;    // Initialise the distances to maximum possible

  // Allocate and Initialise lot empty array
  empty = new int[N];
  empty[0] = -1;          // Source Node not available for parking (Entrance)
  for(int i = 1; i < N; i++)
    empty[i] = 1;


  // Printing the initialised
  int k = 0;
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

  cout << "\nDistances:" << endl;
  for(int i = 0 ; i < N; i++)
    cout << dist[i] << "\t";

  cout << "\nAvailable:" << endl;
  for(int i = 0 ; i < N; i++)
    cout << empty[i] << "\t";


}

void parking_lots::shortest()
{
  int* visited;
  // Allocate and Initialise visited array
  visited = new int[N];
  for(int i = 0; i < N; i++)
    visited[i] = 0;

  cout << "\nVisited:" << endl;
  for(int i = 0 ; i < N; i++)
    cout << visited[i] << "\t";

  // Source (Entrance, 0) as initial node
   

}

int main()
{
  parking_lots lot;
  lot.shortest();


  return 0;
}
