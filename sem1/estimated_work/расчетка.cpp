#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int vers = 10, kolvo, min = 100; bool flag;
	cout << "kolvo graphs: ";
	cin >> kolvo;
	vector<vector<int>> per(vers, vector<int>(vers));
	for (int i = 0; i < vers; i++)
		for (int j = 0; j < vers; j++)
			per[i][j] = 1;

	vector<int>v;
	for (int k = 0; k < kolvo; k++)
	{
		cout << "kolvo vers = ";
		cin >> vers;
		v.push_back(vers);
		cout << "graph:\n";
		vector<vector<int>> graph(vers, vector<int>(vers));
		for (int i = 0; i < vers; i++)
			for (int j = 0; j < vers; j++)
			{
				cin >> graph[i][j];
				if (graph[i][j] == 0) per[i][j] = 0;
			
			}
		cout << "vers: ";
		for (int i = 0; i < vers; i++)
			cout << " " << i + 1;
		cout << endl;
		cout << "rebr =";
		for (int i = 0; i < vers; i++)
			for (int j = 0; j < vers; j++)
				if (graph[i][j] != 0 && j >= i)
					cout << " <" << i + 1 << ", " << j + 1 << ">";
		cout << endl << endl;
	}

	for (int k = 0; k < kolvo; k++)
		if (v[k] < min) min = v[k];
	cout << "peresechenie vers: ";
	for (int i = 0; i < min; i++)
		cout << " " << i + 1;
	cout << endl;
	cout << "peresechenie rebra: ";
	for (int i = 0; i < min; i++)
		for (int j = 0; j < min; j++)
			if (per[i][j] != 0 && j >= i)
				cout << " <" << i+1 << ", " << j+1 << ">";
	return 0;
}