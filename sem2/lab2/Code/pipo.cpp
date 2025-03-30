#include <iostream>
#include "Header.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    Set MultiSet[123];
    string path = "test_diff.txt";

    Do_Symm_Diff(MultiSet, path);

    return 0;
}