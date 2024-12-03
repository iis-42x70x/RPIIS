#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>

using namespace std;
int Size(vector<int> n);
vector<vector<int>> incidenceToAdjacency(const vector<vector<int>> &incidenceMatrix)
{
    int vertices = incidenceMatrix.size(); 
    int edges = incidenceMatrix[0].size(); 

    vector<vector<int>> adjacencyMatrix(vertices, vector<int>(vertices, 0));

    for (int j = 0; j < edges; ++j)
    {
        int startVertex = -1; 
        int endVertex = -1;   

        for (int i = 0; i < vertices; ++i)
        {
            if (incidenceMatrix[i][j] == 1)
            {
                if (startVertex == -1)
                {
                    startVertex = i; 
                }
                else
                {
                    endVertex = i; 
                    break;         
                }
            }
        }

        if (startVertex != -1 && endVertex != -1)
        {
            adjacencyMatrix[startVertex][endVertex] = 1;
            adjacencyMatrix[endVertex][startVertex] = 1; 
        }
    }

    return adjacencyMatrix;
}
bool Find(vector<int> v, int n)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == n)
            return 1;
    }
    return 0;
}
vector<pair<int, int>> removeDuplicates(vector<pair<int, int>> &pairs)
{
    set<pair<int, int>> uniquePairs;

    for (const auto &p : pairs)
    {
        if (p.first < p.second)
        {
            uniquePairs.insert(p);
        }
        else
        {
            uniquePairs.insert({p.second, p.first});
        }
    }

    // Преобразуем set обратно в вектор
    vector<pair<int, int>> result(uniquePairs.begin(), uniquePairs.end());
    return result;
}
int findChords(vector<vector<int>> cycles, vector<vector<int>> &graph)
{
    vector<pair<int, int>> result;
    vector<pair<int, int>> chords;
    for (int i = 0; i < cycles.size(); i++)
    {
        if (cycles[i].size() > 3)
        {
            for (int j = 0; j < cycles[i].size(); j++)
            {
                if (j >= 1 && j < cycles[i].size() - 1)
                {
                    for (int k = 0; k < j - 1; k++)
                    {
                        if (Find(graph[cycles[i][j]], cycles[i][k]))
                        {
                            result.push_back(make_pair(cycles[i][j], cycles[i][k]));
                        }
                    }
                    for (int k = j + 2; k < cycles[i].size(); k++)
                    {
                        if (Find(graph[cycles[i][j]], cycles[i][k]))
                        {
                            result.push_back(make_pair(cycles[i][j], cycles[i][k]));
                        }
                    }
                }
                else if (j == cycles[i].size() - 1)
                {
                    for (int k = 1; k < j - 1; k++)
                    {
                        if (Find(graph[cycles[i][j]], cycles[i][k]))
                        {
                            result.push_back(make_pair(cycles[i][j], cycles[i][k]));
                        }
                    }
                }
                else
                {
                    for (int k = j + 2; k < cycles[i].size() - 1; k++)
                    {
                        if (Find(graph[cycles[i][j]], cycles[i][k]))
                        {
                            result.push_back(make_pair(cycles[i][j], cycles[i][k]));
                        }
                    }
                }
            }
        }
    }
    chords = removeDuplicates(result);
    return chords.size();
}
void removeCycles(vector<vector<int>> &result)
{
    for (int i = 0; i < result.size() - 1; i++)
    {
        for (int j = i + 1; j < result.size(); j++)
        {
            if (result[i].size() == result[j].size() && Size(result[i]) == Size(result[j]))
            {
                result[j].clear();
            }
        }
    }
}
void dfs(int v, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &path, unordered_set<int> &pathSet, vector<vector<int>> &cycles)
{
    visited[v] = true;
    path.push_back(v);
    pathSet.insert(v);

    for (int neighbor : graph[v])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, graph, visited, path, pathSet, cycles);
        }
        else if (pathSet.find(neighbor) != pathSet.end())
        {
            // цикл
            vector<int> cycle;
            auto it = find(path.begin(), path.end(), neighbor);
            for (; it != path.end(); ++it)
            {
                cycle.push_back(*it);
            }
            cycles.push_back(cycle);
        }
    }

    
    path.pop_back();
    pathSet.erase(v);
    visited[v] = false; 
    
}

vector<vector<int>> findCycles(const vector<vector<int>> &adjacencyMatrix)
{
    vector<vector<int>> cycles;
    vector<vector<int>> graph(adjacencyMatrix.size());

    // v spisok smezhnosti
    for (size_t i = 0; i < adjacencyMatrix.size(); i++)
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                graph[i].push_back(j);
            }
        }
    }

    vector<bool> visited(graph.size(), false);
    vector<int> path;
    unordered_set<int> pathSet;

    for (int i = 0; i < graph.size(); i++)
    {
        dfs(i, graph, visited, path, pathSet, cycles);
    }
    for (int i = 0; i < cycles.size(); i++)
    {
        if (cycles[i].size() < 3)
        {
            cycles[i].clear();
        }
    }
    removeCycles(cycles);

    cycles.erase(remove_if(cycles.begin(), cycles.end(), [](const vector<int> &v)
                           { return v.empty(); }),
                 cycles.end());
    cout << "Найденные циклы:" << endl;

    for (const auto &cycle : cycles)
    {
        for (int v : cycle)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << endl
         << "итого хорд в графе: " << findChords(cycles, graph);
    return cycles;
}
int Size(vector<int> n)
{
    int temp = 0;
    for (int i = 0; i < n.size(); i++)
    {
        temp += n[i];
    }
    return temp;
}

int main()
{
    vector<vector<int>> incidence = {{1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
                                     {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                     {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                                     {0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
                                     {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
                                     {0, 0, 0, 0, 0, 1, 0, 1, 1, 0},
                                     {0, 0, 0, 0, 0, 0, 1, 1, 0, 0}};

    // int rows, cols;
    // cin >> rows >> cols;
    // vector<vector<int>> incidence;
    // for (int i = 0; i < rows; i++)
    // {
    //     vector<int> temp1;
    //     for (int j = 0; j < cols; j++)
    //     {
    //         int temp;
    //         cin >> temp;
    //         temp1.push_back(temp);
    //     }
    //     incidence.push_back(temp1);
    // }
    findCycles(incidenceToAdjacency(incidence));

    return 0;
}