#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;      // Adjacency matrix
    bool *visited;  // Visited array

    // Recursive DFS function
    void DFSUtil(int v)
    {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < vertices; i++)
        {
            if (adj[v][i] == 1 && !visited[i])
            {
                DFSUtil(i);
            }
        }
    }

public:
    // Constructor
    Graph(int v)
    {
        vertices = v;

        // Allocate adjacency matrix
        adj = new int*[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adj[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                adj[i][j] = 0;
        }

        visited = new bool[vertices];
    }

    // Add edge
    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;   // Remove this line for directed graph
    }

    // DFS function
    void DFS(int start)
    {
        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        DFSUtil(start);
    }

    // Destructor
    ~Graph()
    {
        for (int i = 0; i < vertices; i++)
            delete[] adj[i];
        delete[] adj;
        delete[] visited;
    }
};

int main()
{
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "DFS Traversal: ";
    g.DFS(start);

    system("pause");
    return 0;
}