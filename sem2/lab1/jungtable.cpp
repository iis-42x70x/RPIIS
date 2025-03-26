#include "pch.h"
#include "jungtable.h"
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

int jungtable::push(int element)
{
    //проверка на повторяемость элементов
    int flag = 0;
    for (int i = 0; i < body.size(); i++) {
        for (int j = 0; j < body[i].size(); j++) {
            if (element == body[i][j]) { flag++; }
        }
    }
    if (flag != 0) { return 404; }

    //добавление элемента
    for (int i = 0; ; i++) {
        if (body.size() < i + 1) {
            body.push_back(vector<int>(1, element));
            i = 0;
            break;
        }
        else if (body[i][body[i].size() - 1] < element) {
            body[i].push_back(element);
            i = 0;
            break;
        }
        else {
            int position = body[i].size() - 1;
            while (position >= 0 && element < body[i][position]) {
                position--;
            }
            int temp = body[i][position + 1];
            body[i][position + 1] = element;
            element = temp;
        }
    }
    return 0;
}

int jungtable::del(int x, int y)
{
    if (x > 0 && y > 0 && y == body[x - 1].size() && x <= body.size() && (x == body.size() || body[x].size() < y)) {
        x--;
        y--;
        int element = body[x][y];
        body[x].erase(body[x].begin() + y);
        if (body[x].empty()) { body.erase(body.end()-1); }
        for (int i = x - 1; i >= 0; i--) {
            int position = body[i].size() - 1;
            while (body[i][position] > element) {
                position--;
            }
            int temp = body[i][position];
            body[i][position] = element;
            element = temp;
        }
        return 0;
    }
    else { return 404; }
}

void jungtable::print()
{
    for (int i = 0; i < body.size(); i++) {
        for (int j = 0; j < body[i].size(); j++) {
            cout << setw(3) << body[i][j];
        }
        cout << endl;
    }
}