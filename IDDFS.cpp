#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;

    // Depth-Limited Search Utility
    bool DLSUtil(int current, int goal, int limit, bool visited[])
    {
        if (current == goal)
        {
            cout << current << " ";
            return true;
        }

        if (limit <= 0)
            return false;

        visited[current] = true;
        cout << current << " ";

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

    // IDDFS function
    void IDDFS(int start, int goal)
    {
        for (int depth = 0; depth < vertices; depth++)
        {
            bool *visited = new bool[vertices];
            for (int i = 0; i < vertices; i++)
                visited[i] = false;

            cout << "\nDepth Limit: " << depth << " -> ";

            if (DLSUtil(start, goal, depth, visited))
            {
                cout << "\nGoal Found at depth " << depth << endl;
                delete[] visited;
                return;
            }

            delete[] visited;
        }

        cout << "\nGoal Not Found.";
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

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;

    cout << "Enter goal node: ";
    cin >> goal;

    g.IDDFS(start, goal);

    system("pause");
    return 0;
}