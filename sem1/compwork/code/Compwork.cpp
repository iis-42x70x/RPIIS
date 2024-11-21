#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int v,  vector<vector<int>>& graph, vector<bool>& visited, stack<int>& vertexOrder)
{
    visited[v] = true;
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[v][i] && !visited[i]) { 
            dfs(i, graph, visited, vertexOrder);
        }
    }
    vertexOrder.push(v);
}

void dfsTranspose(int v, vector < vector <int> >& transposedGraph, vector <bool>& visited) {
    visited[v] = true;
    for (int i = 0; i < transposedGraph.size(); ++i) {
        if (transposedGraph[v][i] && !visited[i]) { 
            dfsTranspose(i, transposedGraph, visited);
        }
    }
}

bool StrongConnectionCheck( vector < vector <int> >& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack <int> vertexOrder;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited, vertexOrder);
        }
    }
    vector < vector <int> > transposedGraph(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transposedGraph[j][i] = graph[i][j];
        }
    }
    visited.assign(n,false);
    int componentCount = 0;
    while (!vertexOrder.empty()) {
        int v = vertexOrder.top();
        vertexOrder.pop();
        if (!visited[v]) {
            componentCount++;
            dfsTranspose(v, transposedGraph, visited);
        }
    }
    return componentCount==1;
}
void runTest(int testNum)
{
    int n;
    cin >> n;
    vector < vector <int> > graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> graph[i][j];
        }
    }
    cout<<"Тест "<<testNum<<": \n";
    cout<<"Число вершин - "<< n <<"\nМатрица смежности\n";
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cout<<graph[i][j]<<" ";
        }
        cout<<'\n';
    }
    if (StrongConnectionCheck(graph) == true){
        cout << "Граф сильно-связный.";
    }
    else{
        cout << "Граф не сильно-связный.";
    }
    cout<<'\n';
}
void UserInput()
{
    cout<<"Введите число вершин графа: ";
    int n;
    cin >> n;
    vector < vector <int> > graph(n, vector<int>(n));
    cout<<"Введите матрицу смежности размером "<<n<<"x"<<n<<'\n';
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> graph[i][j];
        }
    }
    if (StrongConnectionCheck(graph) == true){
        cout << "Граф сильно-связный.";
    }
    else{
        cout << "Граф не сильно-связный.";
    }
}
int main()
{
    cout<<"Выберите, как хотите ввести исходные данные для программы\n"
    <<"1. Из файла\n"
    <<"2. Вручную\n"
    <<"Любое другое число - выход из программы\n";
    int type;
    cin>>type;
    switch (type)
    {
    case 1: 
        freopen("tests.txt", "r", stdin);
        for(int testNum=1; testNum<6; testNum++){
            runTest(testNum); 
        }
    break;
    case 2: 
        UserInput(); 
    break;
    default:
        cout<<"Завершение программы ...";
    break;
    }
    cout<<'\n';
    return 0;
}
