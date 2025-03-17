#include "huffman.hpp"

bool NodeQueue::isEmpty() const {
    return size == 0;
}

void NodeQueue::insert(Node* node) {
    if (size < 256) {
        nodes[size++] = node;
    }
}

Node* NodeQueue::extractMin() {
    if (isEmpty()) return nullptr;
    int minIndex = 0;
    for (int i = 1; i < size; ++i) {
        if (nodes[i]->frequency < nodes[minIndex]->frequency) {
            minIndex = i;
        }
    }
    Node* minNode = nodes[minIndex];
    nodes[minIndex] = nodes[--size];
    return minNode;
}

Node* createNode(char symbol, int frequency, Node* left, Node* right) {
    Node* node = new Node;
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

void calculateFrequencies(const string& text, int frequencies[]) {
    for (int i = 0; i < 256; ++i) frequencies[i] = 0;
    for (char c : text) frequencies[(unsigned char)c]++;
}

Node* buildHuffmanTree(int frequencies[]) {
    NodeQueue queue;
    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] > 0) {
            queue.insert(createNode((char)i, frequencies[i]));
        }
    }

    if (queue.isEmpty()) return nullptr;

    if (queue.size == 1) {
        Node* singleNode = queue.extractMin();
        return createNode('\0', singleNode->frequency, singleNode, nullptr);
    }

    while (queue.size > 1) {
        Node* left = queue.extractMin();
        Node* right = queue.extractMin();
        Node* parent = createNode('\0', left->frequency + right->frequency, left, right);
        queue.insert(parent);
    }
    return queue.extractMin();
}

void generateCodes(Node* node, string code, string codes[]) {
    if (!node) return;

    if (!node->left && !node->right) {
        codes[(unsigned char)node->symbol] = code.empty() ? "0" : code;
        return;
    }

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

string encodeText(const string& text, string codes[]) {
    string encoded;
    for (char c : text) encoded += codes[(unsigned char)c];
    return encoded;
}

string decodeText(Node* root, const string& encodedText) {
    string decoded;
    if (!root) return decoded;

    Node* current = root;
    for (char bit : encodedText) {
        if (bit == '0') current = current->left;
        else if (bit == '1') current = current->right;
        else {
            cerr << "Ошибка: Недопустимый бит '" << bit << "'\n";
            return "";
        }

        if (!current) {
            cerr << "Ошибка: Поврежденные данные\n";
            return "";
        }

        if (!current->left && !current->right) {
            decoded += current->symbol;
            current = root;
        }
    }
    return decoded;
}

void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
