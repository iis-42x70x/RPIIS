#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

void delete_element_from_vector(vector<pair<int, int>>& mas_pair, int& siz, int number);
bool checking_vvod(int data, int size);
void insert_data(vector<vector<pair<int, int>>>& graph, int& vertex);
void delete_vertex(vector<vector<pair<int, int>>>& graph, int& vertex, int& edges);
void insert_new_edge(vector<vector<pair<int, int>>>& graph, int vertex, int& edges);
void delete_edge(vector<vector<pair<int, int>>>& graph, int vertex, int& edges);
void vivod_graphs(vector<vector<pair<int, int>>> graph, int vertex);
void BFS(vector<vector<pair<int, int>>> graph);
void ruchnoi_vvod(vector<vector<pair<int, int>>> &graph, int &vertex, int &edges);
void reading_file(vector<vector<pair<int, int>>> &graph, int &vertex, int &edges);
#endif