#include "Header.h"

int main() {
    cout << "vvedite stroku: ";
    string input;
    getline(cin,input);

    vector <pair<string, int>> counter;
    vector <Node> tree;
    
    counter.push_back({ "", 1 });
    counter[0].first += input[0];
    
    int strlength = input.length();

    counter = fillingcounter(input, strlength, counter);

    int counterlen = counter.size();

    counter = sortcounter(counterlen, counter);

    vector <Node> queue;
    vector <pair<string, string>> encoding;

    queue = makequeue(queue, counter, counterlen);

    encoding = makeencodinglist(encoding, counter, counterlen);

    tree = maketree(tree, queue);
    tree = linkingtree(tree, tree.size());
    
    Node currentnode = tree[tree.size() - 1];

    encoding = fillencodedsymbols(encoding,currentnode);

    string encodedstr = showencodedstr("", encoding, strlength, counterlen, input);

    currentnode = tree[tree.size() - 1];
    string output = decode(tree[tree.size() - 1], 0, "", encodedstr, tree[tree.size() - 1]);;
    cout << endl << output;
}
