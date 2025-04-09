#include <iostream>
#include "Binary Tree.h"

using namespace std;

int main()
{
	Tree a;
	int arr[]{ 100, 200, 50, 250, 75, 25, 150 };
	a.insert(100);
	a.insert(200);
	a.insert(50);
	a.insert(75);
	a.insert(25);
	a.insert(300);
	a.insert(150);
	a.insert(10);
	a.insert(125);
	a.print();
	cout << "\n\n";
	a.bypass();
	a.del_comp();
	cout << "\n\n";
	a.insert(100);
	a.insert(75);
	a.insert(50);
	a.insert(80);
	a.insert(70);
	a.insert(90);
	a.insert(300);
	a.insert(200);
	a.insert(400);
	a.insert(350);
	a.insert(500);
	a.print();
	a.bypass();
	cout << "\n\n";
	a.build(arr, 7);
	a.print();
}
