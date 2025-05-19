#include <iostream>
#include "Difference.h"
int main()
{
	string path;
	path = "sets.txt";
	Set diff(path);
	cout << "  _______________________________________________" << endl << endl;
	cout << "  Set 1 : ";
	diff.PrintSet(1);
	cout << "  Set 2 : ";
	diff.PrintSet(2);
	cout << "  Result of 1 \\ 2 Difference:   ";
	diff.SetDifference(1);
	diff.PrintDifference();
	cout << "  Result of 2 \\ 1 Difference:   ";
	diff.SetDifference(2);
	diff.PrintDifference();
	cout << "\033[1A" << "  _______________________________________________" << endl;
	return 0;
}