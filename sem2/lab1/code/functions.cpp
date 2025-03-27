#include "header.h"

vector <pair<string, int>> fillingcounter(string str, int strlength, vector <pair<string, int>> counter) {
    for (int i = 1; i < strlength;i++) {
        bool check = false;
        for (int j = 0;j < counter.size();j++) {
            string temp = counter[j].first;
            if (str[i] == temp[0]) {
                check = true;
                counter[j].second++;
                break;
            }
        }
        if (!check) {

            counter.push_back({ "",1 });
            counter[counter.size() - 1].first += str[i];
        }
    }
    return counter;
}
// ��������� ������ ������� � ������� �������� ������� �������
vector <pair<string, int>> sortcounter(int length, vector <pair<string, int>> counter)
{
    for (int i = 0;i < length;i++) {
        for (int j = 1;j < length - i;j++) {
            if (counter[j - 1].second < counter[j].second) {
                swap(counter[j - 1], counter[j]);
            }
        }
    }
    return counter;
}
//������� �������
vector <Node> makequeue(vector <Node> queue, vector <pair<string, int>> counter, int length) {
    for (int i = 0;i < length;i++) {
        queue.push_back(Node());
        queue[i].size = 1;
        queue[i].ch = counter[i].first;
        queue[i].freq = counter[i].second;
        queue[i].leftchild = NULL;
        queue[i].rightchild = NULL;
    }
    return queue;
}
//������� ������ ��� �������� ������������� �������
vector <pair<string, string>> makeencodinglist(vector <pair<string, string>> encoding, vector <pair<string, int>> counter, int length) {
    for (int i = 0;i < length;i++) {
        encoding.push_back({ counter[i].first,"" });
    }
    return encoding;
}
//��������� �������
vector <Node> sortqueue(vector <Node> queue, int queuesize) {
    for (int i = queuesize - 1;i > 0;i--) {
        if (queue[i - 1].freq < queue[i].freq) {
            swap(queue[i], queue[i - 1]);
        }
        if (queue[i - 1].freq == queue[i].freq) {
            if (queue[i - 1].size < queue[i].size) {
                swap(queue[i], queue[i - 1]);
            }
        }
    }
    return queue;
}
//�������� ��� ��������� �������� ������� � ������ � ���������� � ������� ������������ ������
vector <Node> maketree(vector <Node> tree, vector <Node> queue) {
    int treelen = 0;

    while (queue.size() > 1) {
        int len = queue.size();
        if (queue[len - 1].pushed == false && queue[len - 1].size == 1) {
            tree.push_back(queue[len - 1]);
            treelen++;
        }
        if (queue[len - 2].pushed == false && queue[len - 2].size == 1) {
            tree.push_back(queue[len - 2]);
            treelen++;
        }
        tree.push_back(Node());
        tree[treelen].pushed = true;

        tree[treelen].size = queue[len - 1].size + queue[len - 2].size;

        tree[treelen].ch += queue[len - 1].ch;
        tree[treelen].ch += queue[len - 2].ch;
        tree[treelen].freq = queue[len - 1].freq + queue[len - 2].freq;
        queue.erase(queue.begin() + queue.size() - 1);
        queue.erase(queue.begin() + queue.size() - 1);
        queue.push_back(tree[treelen]);

        queue = sortqueue(queue, queue.size());

        treelen++;
    }
    return tree;
}
//������� ������ �����
vector <Node> linkingtree(vector <Node> tree, int treelen) {
    for (int i = 2;i < treelen;i++)
    {
        bool first = false;

        for (int j = i - 1;j >= 0;j--) {
            string temp = tree[i].ch;
            if (!tree[j].linked && !first && temp.find(tree[j].ch) != string::npos) {
                tree[i].leftchild = &tree[j];
                first = true;
                tree[j].linked = true;
                j--;
            }
            if (!tree[j].linked && first && temp.find(tree[j].ch) != string::npos) {
                tree[i].rightchild = &tree[j];
                first = false;
                tree[j].linked = true;
                break;
            }
        }
    }
    return tree;
}
//������� ������ ������ ��� ������ ������������ �� ������ � ���������� ��������� �������� � ������ ���
string encode(string ch, string str, Node currentnode) {
    if (currentnode.leftchild != NULL && currentnode.rightchild != NULL) {
        Node leftchild = *currentnode.leftchild;
        string temp = leftchild.ch;
        if (temp.find(ch) != string::npos) {
            str += "1";
            return encode(ch, str, leftchild);
        }
        else {
            str += "0";
            Node rightchild = *currentnode.rightchild;
            return encode(ch, str, rightchild);
        }
    }
    else return str;
}
//��������� ������ � ���������� � ������� ������������� ������� �� �����������
vector <pair<string, string>> fillencodedsymbols(vector <pair<string, string>> encoding, Node currentnode) {
    for (int i = 0;i < encoding.size();i++) {
        encoding[i].second = encode(encoding[i].first, encoding[i].second, currentnode);
        //cout << encoding[i].first << ":  " << encoding[i].second << endl;
    }
    return encoding;
}
//������� ����������� ����������� ��� ������ ������� � ���������
string showencodedstr(string encodedstr, vector <pair<string, string>> encoding, int strlength, int encodinglen, string str) {
    for (int i = 0; i < strlength;i++) {
        for (int j = 0; j < encodinglen;j++) {
            string  temp = encoding[j].first;
            if (str[i] == temp[0]) {
                encodedstr += encoding[j].second;
                cout << encoding[j].second;
                break;
            }
        }
    }
    return encodedstr;
}
/*�������������� ������������� ��������� ��� ������ ����������� �� ������
string decode(Node currentnode, int k, string str, string encodedstr, Node tree) {

    if (k != 0) {
        if (encodedstr[k - 1] == '\0') {
            return str;
        }
    }
    if (currentnode.leftchild == NULL && currentnode.rightchild == NULL) {
        str += currentnode.ch;
        return decode(tree, k, str, encodedstr, tree);
    }
    else {
        if (encodedstr[k] == '0') {
            return decode(*currentnode.rightchild, k + 1, str, encodedstr, tree);
        }
        else {
            return decode(*currentnode.leftchild, k + 1, str, encodedstr, tree);
        }
    }
}*/
//main
string result(string input) {
    vector <pair<string, int>> counter;
    vector <Node> tree;

    counter.push_back({ "", 1 });
    counter[0].first += input[0];

    int strlength = input.length();

    counter = fillingcounter(input, strlength, counter);

    if (counter.size()<2)
        return "error";

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

    string encodedstr = "";

    encodedstr = showencodedstr(encodedstr, encoding, strlength, counterlen, input);

    /*currentnode = tree[tree.size() - 1];
    string str2 = "";
    cout << endl;
    str2 = decode(tree[tree.size() - 1], 0, str2, encodedstr, tree[tree.size() - 1]);
    cout << str2;*/

    return encodedstr;
}
