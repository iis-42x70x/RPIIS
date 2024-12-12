//
//  main.cpp
//  Raschet_rabota
//
//  Created by Dmitry Burbas on 11/12/2024.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int input_graph(vector<vector<int>>& matr_adjacency_graph,int count_vert_inp){
    matr_adjacency_graph.resize(count_vert_inp,vector<int>(count_vert_inp));
    for (int i=0; i<count_vert_inp; i++) {
        for (int j=0; j<count_vert_inp; j++) {
            cin >> matr_adjacency_graph[i][j];
            while (matr_adjacency_graph[i][j] !=1 &&matr_adjacency_graph[i][j]!=0) {
                cerr << "Wrong input matrix! Input only 1 or 0!\n";
                exit(1);
            }
        }
    }
    return 0;
}
int print_graph(vector<vector<int>>matr_adjacency_graph,int count_vert_inp){
    cout <<"   ";
    for (int k=0; k<count_vert_inp; k++) {
        cout << k+1 <<" ";
    }
    cout <<"\n";
    for (int i=0; i<count_vert_inp; i++) {
        cout <<i+1<<"| ";
        for (int j=0; j<count_vert_inp; j++) {
            cout << matr_adjacency_graph[i][j]<<" ";
        }
        cout <<"|\n";
    }
    return 0;
}
int print_list_adj_graph(vector<vector<int>>matr_adj_graph,int count_vert_inp){
    for (int i=0; i<count_vert_inp; i++) {
        cout << i+1<< ": ";
        for (int j=0; j<count_vert_inp; j++) {
            if (matr_adj_graph[i][j]==1) {
                cout << i+1 <<"--"<<j+1 <<" ";
            }
        }
        cout <<"\n";
    }
    return 0;
}
int is_planar_graph(vector<vector<int>>matr_adj,int count_vertex){
    int count_edge=0;
    if(count_vertex<5)cout << "Graph is planar\n";
    if (count_vertex>=5) {
        for (int a=0; a<count_vertex-4; a++) {
            for (int b=0; b<count_vertex-4; b++) {
                for (int i=0; i<5; i++) {
                    for (int j=i+1; j<5; j++) {
                        if (matr_adj[i+a][b+j]==1 && matr_adj[b+j][a+i]==1) {
                            count_edge++;
                        }
                        if (count_edge==10) {
                            cout << "Graph is non-planar\n";
                            return 0;
                        }
                    }
                }
//                cout << k<<" "<<b<<" "<< count_edge<<"\n";
                count_edge=0;
            }
        }
        for (int x=0; x<count_vertex-5; x++) {
            for (int y=0; y<count_vertex-5; y++) {
                for (int i=0; i<3; i++) {
                    for (int j=0; j<3; j++) {
                        if (matr_adj[x+5-i][y+j]==1 &&matr_adj[x+i][y+3+j]) {
                            count_edge++;
                            if (count_edge==9) {
                                cout << "Graph is non-planar\n";
                                return 0;
                            }
//                            cout << x<< " "<<y << " "<< count_edge<<"\n";
                        }
                    }
                }
                count_edge=0;
            }
        }
    }
    cout << "Graph is planar\n";
    
    return 0;
}

int main() {
    int count_vert_graph;
    cout << "Enter the number of vertices of graph: ";
    cin >> count_vert_graph;
    vector<vector<int>>matr_adjacency_graph;
    cout << "Enter the matrix of adjacency of graph: \n";
    input_graph(matr_adjacency_graph, count_vert_graph);
    cout << "Matrix of adjacency: \n";
    print_graph(matr_adjacency_graph, count_vert_graph);
//    print_list_adj_graph(matr_adjacency_graph, count_vert_graph);
    is_planar_graph(matr_adjacency_graph, count_vert_graph);
    return 0;
}
