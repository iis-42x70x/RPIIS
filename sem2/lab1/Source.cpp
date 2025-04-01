#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

struct mnozh {
    vector<char> elem;
    vector<mnozh*> podmnozh;
};

void add_mnozh(mnozh* mn, string str) {
    mnozh* current = mn;
    stack<mnozh*> levels;
    levels.push(current);

    for (char ch : str) {
        if (ch == '{') {
            mnozh* p = new mnozh;
            current->podmnozh.push_back(p);
            levels.push(current);
            current = p;
        }
        else if (ch == '}') {
            if (!levels.empty()) {
                current = levels.top();
                levels.pop();
            }
        }
        else if (ch == ',') {
            continue;
        }
        else {
            current->elem.push_back(ch);
        }
    }
}

void create(int i, vector<mnozh>& set) {
    vector<char> p;
    for (int j = 0; j < i; j++) {
        string str;
        while (true) {
            cout << "Введите " << j + 1 << " множество: ";
            cin >> str;
            vector<char> temp = p;
            bool check = true;
            for (int i = 0; i < str.size(); i++) {
                for (int j = 0; j < temp.size(); j++) {
                    if (str[i] == temp[j]) {
                        check = false;

                    }
                }
                if (str[i] != '{' && str[i] != '}' && str[i] != ',' && str[i] != ' ') {
                    temp.push_back(str[i]);
                }
            }
            if (check) {
                p = temp;
                break;
            }
            cout << "Некорректный ввод! ";
            cin.clear();
            temp.clear();
        }

        mnozh root;
        add_mnozh(&root, str);
        set.push_back(root);
    }
}

string view_single(const mnozh* mn, bool isRoot = true) {
    if (!mn) return "";

    stringstream result;

    if (!isRoot) result << "{ ";

    for (int i = 0; i < mn->elem.size(); ++i) {
        result << mn->elem[i];
        if (i != mn->elem.size() - 1) {
            result << " ";
        }
    }

    for (int i = 0; i < mn->podmnozh.size(); ++i) {
        if (!mn->elem.empty()) result << " ";
        result << view_single(mn->podmnozh[i], false);
    }

    if (!isRoot) result << " }";

    string res = result.str();

    for (int i = 0; i < res.size() - 1; i++) {
        if (res[i] == '}' && res[i + 1] == '{') {
            res.erase(res.begin() + i);
            res.erase(res.begin() + i);
            res.erase(res.begin() + i);
        }
    }
    return res;
}

void view(const vector<mnozh>& sets) {
    for (int  j = 0; j < sets.size(); j++) {
        cout << "Множество " << j + 1 << ": " << view_single(&sets[j]) << endl;
    }
}

void delete_mnozh(mnozh* mn) {
    if (!mn) return;
    for (mnozh* p : mn->podmnozh) {
        delete_mnozh(p);
    }
    delete mn;
}

void Union(int a, int b, vector<mnozh>& set) {
    for (char element : set[b - 1].elem) {
        set[a - 1].elem.push_back(element);
    }

    for (mnozh* sub : set[b - 1].podmnozh) {
        set[a - 1].podmnozh.push_back(sub);
    }

    set.erase(set.begin() + b - 1);
}

bool find_one(const mnozh* mn,char ch) {
    for (int i = 0; i < mn->elem.size(); i++) {
        if (ch == mn->elem[i]) {
			return true;
        }
    }
    for (int i = 0; i < mn->podmnozh.size(); i++) {
		if (find_one(mn->podmnozh[i], ch)) {
			return true;
		}
    }
    return false;
}

void find(const vector<mnozh>& set,char ch) {
	for (int i = 0; i < set.size(); i++) {
		if (find_one(&set[i], ch)) {
			cout << "Элемент " << ch << " принадлежит множеству " << i + 1 << endl;
            break;
		}
	}

}
