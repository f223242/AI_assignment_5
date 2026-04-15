#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;

    // Recursive DLS function
    bool DLSUtil(int current, int goal, int limit, bool visited[])
    {
        cout << current << " ";

        if (current == goal)
            return true;

        if (limit <= 0)
            return false;

        visited[current] = true;

        for (int i = 0; i < vertices; i++)
        {
            if (adj[current][i] == 1 && !visited[i])
            {
                if (DLSUtil(i, goal, limit - 1, visited))
                    return true;
            }
        }

        return false;
    }

public:
    // Constructor
    Graph(int v)
    {
        vertices = v;

        adj = new int*[vertices];
        for (int i = 0; i < vertices; i++)
        {
            adj[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                adj[i][j] = 0;
        }
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;  // Remove for directed graph
    }

    void DLS(int start, int goal, int limit)
    {
        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        cout << "Traversal: ";

        if (DLSUtil(start, goal, limit, visited))
            cout << "\nGoal Found!";
        else
            cout << "\nGoal Not Found within depth limit.";

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

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start, goal, limit;

    cout << "Enter start node: ";
    cin >> start;

    cout << "Enter goal node: ";
    cin >> goal;

    cout << "Enter depth limit: ";
    cin >> limit;

    g.DLS(start, goal, limit);

    system("pause");
    return 0;
}