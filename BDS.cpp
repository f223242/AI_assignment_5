#include <iostream>
using namespace std;

class Graph
{
private:
    int vertices;
    int **adj;

    // BFS step (one level expansion)
    bool BFS(int queue[], int &front, int &rear, bool visited[], bool otherVisited[])
    {
        if (front == rear)
            return false;

        int current = queue[front++];
        
        for (int i = 0; i < vertices; i++)
        {
            if (adj[current][i] == 1 && !visited[i])
            {
                visited[i] = true;
                queue[rear++] = i;

                // If visited by other search → meeting point found
                if (otherVisited[i])
                    return true;
            }
        }
        return false;
    }

public:
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
        adj[v][u] = 1;   // Remove for directed graph
    }

    void bidirectionalSearch(int start, int goal)
    {
        if (start == goal)
        {
            cout << "Start is Goal.\n";
            return;
        }

        bool *visitedStart = new bool[vertices];
        bool *visitedGoal  = new bool[vertices];

        for (int i = 0; i < vertices; i++)
        {
            visitedStart[i] = false;
            visitedGoal[i]  = false;
        }

        int *queueStart = new int[vertices];
        int *queueGoal  = new int[vertices];

        int frontStart = 0, rearStart = 0;
        int frontGoal  = 0, rearGoal  = 0;

        // Initialize
        visitedStart[start] = true;
        queueStart[rearStart++] = start;

        visitedGoal[goal] = true;
        queueGoal[rearGoal++] = goal;

        while (frontStart < rearStart && frontGoal < rearGoal)
        {
            // Expand from start side
            if (BFS(queueStart, frontStart, rearStart, visitedStart, visitedGoal))
            {
                cout << "Path Found using Bidirectional Search.\n";
                return;
            }

            // Expand from goal side
            if (BFS(queueGoal, frontGoal, rearGoal, visitedGoal, visitedStart))
            {
                cout << "Path Found using Bidirectional Search.\n";
                return;
            }
        }

        cout << "No Path Found.\n";

        delete[] visitedStart;
        delete[] visitedGoal;
        delete[] queueStart;
        delete[] queueGoal;
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

    g.bidirectionalSearch(start, goal);

    system("pause");
    return 0;
}