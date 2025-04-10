#include <iostream>
#include "Binary Tree.h"

using namespace std;

int main()
{
	Tree a;
	int arr[]{ 100, 200, 50, 250, 75, 25, 150 };
	a.insert(100);
	a.insert(200);
	a.insert(75);
	a.insert(50);
	a.insert(150);
	a.insert(175);
	a.insert(125);
	a.insert(80);
	a.insert(60);
	a.insert(25);
	a.print();
	a.search(25);
	a.search(1);
	a.pop(50);
	a.print();
	cout << "\n\n";
	a.bypass();
	cout << "\n\n";
	a.build(arr, 7);
	a.print();
}
