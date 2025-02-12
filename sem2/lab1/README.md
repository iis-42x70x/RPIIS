### Лабараторная работа №1
### Цель📌:

Цель моей лабараторной работы заключалась в изучении "очереди".

### Задача📑

Написать код на любом языке программирования.
Вот пример моего кода на с++:

~~~
#include "pch.h"
#include <iostream>
#include <queue>
#include <string>
#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    void Take(int n) {
        if (n > queue1.size() || n < 0) {
            cout << "Error" << endl;
            return;
        }
        else {
            for (int i = 0; i < n - 1; i++) {
                queue1.pop();
            }
            cout << queue1.front() << endl;
        }
    }
    
    void setQueue(string s) {
        queue1.push(s);
    }

private:
    queue<string> queue1;
};

TEST(SolutionTest, TestAdd) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.setQueue("One");
    sol.setQueue("Two");
    sol.setQueue("Tree");
    sol.Take(2);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Two\n");
}

TEST(SolutionTest, TestOverflow) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.setQueue("One");
    sol.setQueue("Two");
    sol.setQueue("Tree");
    sol.Take(4);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error\n");
}

TEST(SolutionTest, TestHollowQueue) {
    Solution sol;
    testing::internal::CaptureStdout();
    sol.Take(1);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
~~~

### Разбор кода
1. В этом коде мы имеем класс "Solution".
2. В этом классе присуствуют две функции: "Take" & "SetQueue".
3. SetQueue выполняет задачу заполнения очереди.
4. Take выполняет задачу взятия n-го элемента очереди.
5. В коде представлены тесты в количестве: 3.
6. TestAdd выполняет проверку на правильность алгоритма взятия n-го элемента очереди.
7. TestOverflow выполняет проверку на корректность n.
8. TestHollowQueue выполняет проверку на взятие элемента из пустой очереди.
9. В этом коде соблюдены все требования к лабараторной работе.

### Литература
<a href="https://www.klex.ru/1718">📗</a>.
<a href="https://www.google.by/books/edition/%D0%9E%D0%BB%D0%B8%D0%BC%D0%BF%D0%B8%D0%B0%D0%B4%D0%BD%D0%BE%D0%B5_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC/34KzDwAAQBAJ?hl=ru&gbpv=1&printsec=frontcover">📘</a>.
<a href="https://cchgeu.ru/upload/iblock/8b4/nrwdckls1bi7zzrfr2fnwx88145v1341/metodichka-Informatika-1.pdf">📕</a>.
