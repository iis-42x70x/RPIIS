#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>
#include <ctime>

using namespace std;

class Graph {
public:
    bool deleteVertexOrEdge;
    vector<vector<int>> matrix;
    int n = 0;

#pragma region Class constructors
    // explicit - для предотвращения неявного преобразования типов при инициализации
    explicit Graph (const vector<vector<int>>& m, const bool vertexOrEdge) {
        matrix = m;
        n = (int)m.size();
        deleteVertexOrEdge = vertexOrEdge;
    }

    explicit Graph (int n) {
        this->n = n;
        matrix.assign(n, vector<int>(n));
    }
#pragma endregion

    string toString()  {
        string res;
        for(int i = 0;i < n;i++) {
            for(int j = i;j < n;j++) {
                if(matrix[i][j] == 1) {
                    res += to_string(i) + " -- " + to_string(j) + ";" + "\n";
                }
            }
        }
        return res;
    }
    vector<vector<int>> showGraph (){
        return matrix;
    }


    static vector<vector <int>> RemoveAll(vector<vector<int>> *a, const vector<int>& b) { //+
        for (int i = 0; i < a->size(); i++) {
            if ((*a)[i] == b) {
                a->erase(a->begin() + i);
            }
        }
        return *a;
    }

    void NewEdge (int k, int m) {
        matrix [k][m] = matrix [m][k] = 1;
    }

    bool ContEdge (int k, int m) {
        return (matrix[k][m] == 1);
    }

#pragma region Cycles
    bool FindCycle (vector <int>* result, vector<int> used, int parent, int v) {
        used.resize(n, 0);
        used[v] = 1;
        for (int i = 0; i < n; i++) {
            if (i == parent) continue;
            if (matrix[v][i] == 0) continue;
            if (used[i] == 0) {
                result->push_back(v);
                if (FindCycle(result, used, v, i)) {
                    // Цикл найден
                    return true;
                }
                else {
                    result->pop_back();
                }
            }
            if (used[i] == 1) {
                result->push_back(v);
                auto cycle = new vector <int>;
                for (int j = 0; j < result->size(); j++) {
                    if ((*result)[j] == i) {
                        for (int k = j; k < result->size(); k++) {
                            (*cycle).push_back((*result)[k]);
                        }
                        result->clear();
                        for (int & l : *cycle) {
                            result->push_back(l);
                        }
                        return true;
                    }
                }
                return true;
            }
        }
        used[v] = 2;
        return false;
    }

    // Возврат найденного цикла
    vector <int>* GetCycle() {
        auto cycle = new vector<int>();
        bool isCycle = FindCycle(cycle, *new vector<int>, -1, 0);
        if(!isCycle) {
            return nullptr;
        }
        else {
            auto* result = new vector<int>();
            for (int v:*cycle) result->push_back(v);
            return result;
        }
    }
#pragma endregion

#pragma region Dfs and segments
    //Поиск сегментов
    void dfsSegments(vector <int> used, vector<bool>* laidVertexes, Graph* result, int v) {
        used[v] = 1;
        for (int i = 0; i < n; i++) {
            if (matrix[v][i]==1){
                result->NewEdge(v,i);
                if (used[i] == 0 && !(*laidVertexes)[i]) dfsSegments(used, laidVertexes, result, i);
            }
        }
    }

    // Возврат сегментов
    vector <Graph>* getSegments (vector<bool>* laidVertexes, vector<vector<bool>>* edges) {
        auto segments = new vector<Graph> ();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrix[i][j] == 1 && !(*edges)[i][j] && (*laidVertexes)[i] && (*laidVertexes)[j]) {
                    auto *t = new Graph(n);
                    t->NewEdge(i, j);
                    (*segments).push_back(*t);
                }
            }
        }
        auto* used = new vector<int>(n);
        for (int i = 0; i < n; i++) {
            if ((*used)[i] == 0 && !(*laidVertexes)[i]) {
                auto* res = new Graph(n);
                dfsSegments(*used, laidVertexes, res, i);
                segments->push_back(*res);
            }
        }
        return segments;
    }

    // Поиск цепи
    void dfsChain(vector<bool>* used, vector<bool>* laidVertexes, vector<int>* chain, int v) {
        (*used)[v] = true;
        chain->push_back(v);
        for (int i = 0; i < n; i++) {
            if (matrix[v][i] == 1 && (*used)[i] == false) {
                if (!(*laidVertexes)[i]) {
                    dfsChain(used, laidVertexes, chain, i);
                } else {
                    chain->push_back(i);
                }

                return;
            }
        }
    }

    // Получение цепей графа
    vector<int>* getChain(vector<bool>* laidVertexes) {
        auto result = new vector<int>();
        for (int i = 0; i < n; i++) {
            if ((*laidVertexes)[i]) {
                bool inGraph = false;
                for (int j = 0; j < n; j++) {
                    if (ContEdge(i, j)) {
                        inGraph = true;
                        break;
                    }
                }
                if (inGraph) {
                    dfsChain(new vector<bool>(n), laidVertexes, result, i);
                    break;
                }
            }
        }
        return result;
    }

    // Укладка цепей графа
    static void layChain(vector<vector<bool>>* result, vector <int> chain, bool cyclic) {
        for (int i = 0; i < chain.size() - 1; i++) {
            (*result)[chain[i]][chain[i + 1]] = true;
            (*result)[chain[i + 1]][chain[i]] = true;
        }
        if (cyclic) {
            (*result)[chain[0]][chain[chain.size() - 1]] = true;
            (*result)[chain[chain.size() - 1]][chain[0]] = true;
        }
    }
#pragma endregion

#pragma region Faces
    // Проверка наличия у грани нужных сегментов
    bool isFaceContainsSegment(vector <int> face, Graph segment, vector<bool>* laidVertexes) const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (segment.ContEdge(i, j)) {
                    if (((*laidVertexes)[i] && (find(face.begin(), face.end(), i) == face.end()))
                        || ((*laidVertexes)[j] && (find(face.begin(), face.end(), j) == face.end()))) {
                        return false;
                        }
                }
            }
        }
        return true;
    }

    // Подсчет гранй относящихся к сегменту
    vector <int> calcNumOfFacesContainedSegments (vector<vector<int>> *intFaces, const vector<int>& extFace,
                                                  vector <Graph> segments, vector<bool>* laidVertexes,vector<vector<int>>* destFaces) {
        auto count = new vector<int>(segments.size());
        for (int i = 0; i < segments.size(); i++) {
            for (const vector<int>& face: *intFaces) {
                if (isFaceContainsSegment(face, segments[i], laidVertexes)) {
                    (*destFaces)[i] = face;
                    (*count)[i]++;
                }
            }
            if (isFaceContainsSegment(extFace, segments[i], laidVertexes)) {
                (*destFaces)[i] = extFace;
                (*count)[i]++;
            }
        }
        return *count;
    }

#pragma endregion

#pragma region Check Graph
    bool isTree() {
        vector<bool> used (n, 0);
        used[0] = 1;
        queue<pair<int, int>> q;
        q.push(make_pair(-1, 0));

        while (!q.empty()) {
            auto front = q.front();
            q.pop();

            for(int i = 0; i < n; i++) {
                if(front.first == i)
                    continue;
                if(matrix[front.second][i] == 1) {
                    if(used[i] == 0) {
                        q.push(make_pair(front.second, i));
                        used[front.second] = true;
                    }
                    else return false;
                }

            }
        }
        return true;
    }
    bool PreCheckedGraph() {
        return isTree() || n < 5;
    }
    bool CheckGraphForm() {
        if (matrix.size() > n) {
            return true;
        }
        for (int x = 0; x < n; x++) {
            for (int y = x+1; y < n; y++) {
                if (matrix[x][y] == 0 && matrix[y][x] !=0) {
                    return true;
                }
                if (matrix[x][y]!=0 && matrix[y][x] == 0) {
                    return true;
                }
            }
        }
        vector<int>* c = GetCycle();
        if (c== nullptr) {
            return true;
        }
        return false;
    }

#pragma endregion

#pragma region Vertex and Edges operations

    int mostConnectedVertex(vector< vector<int>> segment){
        int edgeNum = 0, maxEdgeNum = 0;
        int maxVertex = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(segment[i][j] == 1){
                    edgeNum++;
                }
            }
            if(edgeNum > maxEdgeNum){
                maxEdgeNum = edgeNum;
                maxVertex = i;
            }
            edgeNum = 0;
        }
        return maxVertex;
    }

    void deleteEdge(int &deletedEdgesAmount, vector< vector<int>> segment) {
        int maxVertex = mostConnectedVertex(segment);
        for(int i = 0; i < n; i++){
            if(segment[maxVertex][i] == 1){
                matrix[maxVertex][i] = 0;
                matrix[i][maxVertex] = 0;
                deletedEdgesAmount++;
                break;
            }
        }
    }

    int deleteVertex(int &deletedVerticesAmount, vector< vector<int>> segment) {
        int maxVertex = mostConnectedVertex(segment);
        matrix.erase(matrix.begin() + maxVertex);
        n--;
        for(int i = 0; i < n; i++){
            matrix[i].erase(matrix[i].begin() + maxVertex);
        }
        deletedVerticesAmount++;
        return maxVertex;
    }

#pragma endregion

    // In this case - check graph planarity
    vector<int> getPlanarLaying() {

        vector<int>* c = GetCycle();
        auto intFaces = new vector<vector<int>>;
        vector<int>* extFace = c;
        intFaces->push_back(*c);
        intFaces->push_back(*extFace);

        auto laidVertexes = new vector<bool> (n);
        auto laidEdges = new vector<vector<bool>> (n, vector<bool> (n));
        for (int i : *c) {
            (*laidVertexes)[i] = true;
        }
        layChain(laidEdges, *c, true);

        int deletedEdgesAmount = 0;
        int deletedVerticesAmount = 0;
        bool needChanges = false;
        int deletedVertex;
        vector<int> result;
        while (true) {
            vector<Graph>* segments = getSegments(laidVertexes, laidEdges);
            if (segments->empty()) {
                if(needChanges){
                    result.push_back(deletedEdgesAmount);
                    result.push_back(deletedVerticesAmount);
                }
                break;
            }
            auto destFaces = new vector<vector<int>>(segments->size());
            auto count = calcNumOfFacesContainedSegments(intFaces, *extFace, *segments, laidVertexes, destFaces);
            int mi = 0;
            for (int i = 0; i < segments->size(); i++) {
                if (count[i] < count[mi])
                    mi = i;
            }
            for(auto i : count){
                cout << i <<" ";
            }
            cout << endl;
            if (count[mi] == 0) {
                if(deleteVertexOrEdge) {

                    deletedVertex = deleteVertex(deletedVerticesAmount, ((*segments)[mi]).showGraph());

                    for(int i = 0; i < c->size(); i++){
                        if((*c)[i] > deletedVertex){
                            (*c)[i]--;
                        }
                    }
                    laidVertexes->erase(laidVertexes->begin() + deletedVertex);

                    laidEdges->erase(laidEdges->begin() + deletedVertex);
                    for(int i = 0; i < n; i++){
                        (*laidEdges)[i].erase((*laidEdges)[i].begin() + deletedVertex);
                    }

                    for(int i = 0; i < intFaces->size(); i++){
                        for(int j = 0; j < (*intFaces)[i].size(); j++){
                            if((*intFaces)[i][j] > deletedVertex){
                                (*intFaces)[i][j]--;
                            }
                        }
                    }
                    for(int i = 0; i < extFace->size(); i++){
                        if((*extFace)[i] > deletedVertex){
                            (*extFace)[i]--;
                        }
                    }
                    for(int i = 0; i < destFaces->size(); i++){
                        for(int j = 0; j < (*destFaces)[i].size(); j++){
                            if((*destFaces)[i][j] > deletedVertex){
                                (*destFaces)[i][j]--;
                            }
                        }
                    }
                }
                else {
                    deleteEdge(deletedEdgesAmount, ((*segments)[mi]).showGraph());
                }

                needChanges = true;

                /*for(auto it : ((*segments)[mi]).showGraph()){
                    for(auto itt : it){
                        cout << itt << " ";
                    }
                    cout <<endl;
                }*/
                cout << endl << endl;
                
            } else { //++++++
                //Укладка выбранного сегмента
                //Выделяем цепь между двумя контактными вершинами
                /*for(auto it : ((*segments)[mi]).showGraph()){
                    for(auto itt : it){
                        cout << itt;
                    }
                    cout <<endl;
                }*/
                
                auto chain = ((*segments)[mi]).getChain(laidVertexes);
                /*for(auto b : *chain){
                    cout << b  + 1<< " ";
                    cout << endl;
                }*/
                
                for (int i : *chain) {
                    (*laidVertexes)[i] = true;
                }
                layChain(laidEdges, *chain, false);
                vector <int> face = (*destFaces)[mi];

                auto face1 = new vector<int>();
                auto face2 = new vector<int>();
                int contactFirst = 0, contactSecond = 0;
                for (int i = 0; i < face.size(); i++) {
                    if (face[i] == (*chain)[0]) {
                        contactFirst = i;
                    }
                    if (face[i] == (*chain)[chain->size() - 1]) {
                        contactSecond = i;
                    }
                }
                auto reverseChain = *chain;
                reverse(reverseChain.begin(), reverseChain.end());
                int faceSize = face.size();
                if (face != *extFace) {

                    if (contactFirst < contactSecond) {
                        copy((*chain).begin(), (*chain).end(), back_inserter(*face1));
                        for (int i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize) {
                            face1->push_back(face[i]);
                        }
                        copy(reverseChain.begin(), reverseChain.end(), back_inserter(*face2));
                        for (int i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize) {
                            face2->push_back(face[i]);
                        }
                    } else {
                        copy(reverseChain.begin(), reverseChain.end(), back_inserter(*face1));
                        for (int i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize) {
                            face1->push_back(face[i]);
                        }
                        copy((*chain).begin(), (*chain).end(), back_inserter(*face2));
                        for (int i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize) {
                            face2->push_back(face[i]);
                        }
                    }

                    RemoveAll(intFaces,face);
                    intFaces->push_back(*face1);
                    intFaces->push_back(*face2);


                } else {
                    auto newOuterFace = new vector<int>();
                    if (contactFirst < contactSecond) {
                        copy((*chain).begin(), (*chain).end(), back_inserter(*newOuterFace));
                        for (int i = (contactSecond + 1) % faceSize; i != contactFirst; i = (i + 1) % faceSize) {
                            newOuterFace->push_back(face[i]);
                        }
                        copy((*chain).begin(), (*chain).end(), back_inserter(*face2));
                        for (int i = (contactSecond - 1 + faceSize) % faceSize; i != contactFirst; i = (i - 1 + faceSize) % faceSize) {
                            face2->push_back(face[i]);
                        }
                    } else {
                        copy(reverseChain.begin(), reverseChain.end(), back_inserter(*newOuterFace));
                        for (int i = (contactFirst + 1) % faceSize; i != contactSecond; i = (i + 1) % faceSize) {
                            newOuterFace->push_back(face[i]);
                        }
                        copy(reverseChain.begin(), reverseChain.end(), back_inserter(*face2));
                        for (int i = (contactFirst - 1 + faceSize) % faceSize; i != contactSecond; i = (i - 1 + faceSize) % faceSize) {
                            face2->push_back(face[i]);
                        }
                    }
                    RemoveAll(intFaces, *extFace);
                    intFaces->push_back(*newOuterFace);
                    intFaces->push_back(*face2);
                    extFace = newOuterFace;
                }
                delete face1;
                delete face2;
            }

        }
        return result;
    }
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("visualize.gv");
    unsigned int start_time =  clock();
    int n = 0;
    fin >> n;
    vector<vector<int>> m(n,vector <int> (n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> m[i][j];
        }
    }

    // Init new graphs (where's gr2 - copy of gr)
    auto* gr = new Graph(m,true);
    auto gr2 = new Graph(m,false);

    // Check lemma's and graph form
    if(gr->PreCheckedGraph())
        return cout << "Graph is planar" << endl, 0;

    if (gr->CheckGraphForm())
        return cout << "Incorrect graph format" << endl, 0;


    // See graph
    fout << "graph G {" << endl;
    cout << "Graph:" << endl;
    cout << gr->toString() << endl;
    fout << gr->toString();
    fout << "}";

    vector<int> result = (*gr).getPlanarLaying(); // for amount of deleted vertices
    vector<int> result2 = (*gr2).getPlanarLaying(); // for amount of deleted edges
    if(result.empty()) {
        cout << "Graph is planar" << endl;
    }
    else {
        cout << "Graph is not planar. To make this graph planar we should delete edges or vertices" << endl;
        cout << "Amount of deleted edges: " << result2[0] << endl;
        cout << "Amount of deleted vertices: " << result[1] << endl;
    }

    unsigned int end_time = clock();
    cout << endl << (end_time - start_time)/1000.0 << " sec." << endl;
    fin.close();
    fout.close();

    return 0;
}