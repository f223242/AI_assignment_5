#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;   // Adjacency matrix

public:
    // Constructor
    Graph(int v)
    {
        vertices = v;

        // Allocate memory for adjacency matrix
        adj = new int*[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adj[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                adj[i][j] = 0;
        }
    }

    // Add edge
    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;   // Remove this for directed graph
    }

    // BFS function
    void BFS(int start)
    {
        bool *visited = new bool[vertices];

        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        // Manual queue
        int *queue = new int[vertices];
        int front = 0, rear = 0;

        visited[start] = true;
        queue[rear++] = start;

        while (front < rear)
        {
            int current = queue[front++];
            cout << current << " ";

            for (int i = 0; i < vertices; i++)
            {
                if (adj[current][i] == 1 && !visited[i])
                {
                    visited[i] = true;
                    queue[rear++] = i;
                }
            }
        }

        delete[] visited;
        delete[] queue;
    }

    // Destructor
    ~Graph()
    {
        for (int i = 0; i < vertices; i++)
            delete[] adj[i];
        delete[] adj;
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

    cout << "BFS Traversal: ";
    g.BFS(start);

    system("pause");
    return 0;
}