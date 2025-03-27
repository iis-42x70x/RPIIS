#ifndef PIOIVIS1LAB_HEADER_H
#define PIOIVIS1LAB_HEADER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int size;
    string ch = "";
    int freq;
    struct Node* leftchild = NULL;
    struct Node* rightchild = NULL;
    bool pushed = false;
    bool linked = false;
};
vector <pair<string, int>> fillingcounter(string str, int strlength, vector <pair<string, int>> counter);
vector <pair<string, int>> sortcounter(int length, vector <pair<string, int>> counter);
vector <Node> makequeue(vector <Node> queue, vector <pair<string, int>> counter, int length);
vector <pair<string, string>> makeencodinglist(vector <pair<string, string>> encoding, vector <pair<string, int>> counter, int length);
vector <Node> sortqueue(vector <Node> queue, int queuesize);
vector <Node> maketree(vector <Node> tree, vector <Node> queue);
vector <Node> linkingtree(vector <Node> tree, int treelen);
string encode(string ch, string str, Node currentnode);
vector <pair<string, string>> fillencodedsymbols(vector <pair<string, string>> encoding, Node currentnode);
string showencodedstr(string encodedstr, vector <pair<string, string>> encoding, int strlength, int encodinglen, string str);
//string decode(Node currentnode, int k, string str, string encodedstr, Node tree);
string result(string str1);

#endif //PIOIVIS1LAB_HEADER_H
