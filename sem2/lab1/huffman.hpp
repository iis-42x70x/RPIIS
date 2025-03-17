#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <string>

using namespace std;

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;
};

struct NodeQueue {
    Node* nodes[256];
    int size = 0;

    bool isEmpty() const;
    void insert(Node* node);
    Node* extractMin();
};

Node* createNode(char symbol, int frequency, Node* left = nullptr, Node* right = nullptr);
void calculateFrequencies(const string& text, int frequencies[]);
Node* buildHuffmanTree(int frequencies[]);
void generateCodes(Node* node, string code, string codes[]);
string encodeText(const string& text, string codes[]);
string decodeText(Node* root, const string& encodedText);
void freeTree(Node* node);

#endif
