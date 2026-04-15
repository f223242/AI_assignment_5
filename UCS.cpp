#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;      // Weighted adjacency matrix

public:
    Graph(int v)
    {
        vertices = v;

        adj = new int*[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adj[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                adj[i][j] = 0;   // 0 means no edge
        }
    }

    void addEdge(int u, int v, int weight)
    {
        adj[u][v] = weight;
        adj[v][u] = weight;   // Remove for directed graph
    }

    void UCS(int start)
    {
        int *cost = new int[vertices];
        bool *visited = new bool[vertices];

        // Initialize cost and visited
        for (int i = 0; i < vertices; i++)
        {
            cost[i] = 99999;  // Infinity
            visited[i] = false;
        }

        cost[start] = 0;

        for (int count = 0; count < vertices - 1; count++)
        {
            // Find node with minimum cost
            int minCost = 99999;
            int u = -1;

            for (int i = 0; i < vertices; i++)
            {
                if (!visited[i] && cost[i] < minCost)
                {
                    minCost = cost[i];
                    u = i;
                }
            }

            if (u == -1)
                break;

            visited[u] = true;

            // Update cost of adjacent vertices
            for (int v = 0; v < vertices; v++)
            {
                if (adj[u][v] != 0 && !visited[v])
                {
                    if (cost[u] + adj[u][v] < cost[v])
                    {
                        cost[v] = cost[u] + adj[u][v];
                    }
                }
            }
        }

        // Print shortest costs
        cout << "Minimum cost from source:\n";
        for (int i = 0; i < vertices; i++)
        {
            cout << "Node " << i << " : " << cost[i] << endl;
        }

        delete[] cost;
        delete[] visited;
    }

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

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    g.UCS(start);

    system("pause");
    return 0;
}