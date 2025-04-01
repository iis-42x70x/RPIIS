#ifndef MNOZH_H
#define MNOZH_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

struct mnozh {
    vector<char> elem;          
    vector<mnozh*> podmnozh;    
};

void add_mnozh(mnozh* mn, string str);

void create(int i, vector<mnozh>& set);

void view(const vector<mnozh>& sets);

void view_single(const mnozh* mn,bool isRoot = true);

void delete_mnozh(mnozh* mn);

void Union(int a, int b, vector<mnozh>& set);

void find(const vector<mnozh>& set, char ch);

bool find_one(const mnozh* mn, char ch);

#endif
