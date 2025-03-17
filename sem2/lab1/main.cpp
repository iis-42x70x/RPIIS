#include "huffman.hpp"

int main() {
    setlocale(LC_ALL, "Russian");
    string text;
    cout << "Введите текст: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Пустой ввод!\n";
        return 0;
    }

    int frequencies[256];
    calculateFrequencies(text, frequencies);

    Node* huffmanTree = buildHuffmanTree(frequencies);
    if (!huffmanTree) {
        cout << "Ошибка построения дерева!\n";
        return 1;
    }

    string codes[256];
    generateCodes(huffmanTree, "", codes);

    string encoded = encodeText(text, codes);
    string decoded = decodeText(huffmanTree, encoded);

    cout << "\nИсходный текст: " << text
        << "\nЗакодированный: " << encoded
        << "\nДекодированный: " << decoded
        << "\nРезультат: " << (text == decoded ? "Успех!" : "Ошибка!")
        << "\n";

    freeTree(huffmanTree);
    return 0;
}
