#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

vector <pair <int, int>> zapisisspiska(vector <vector <int>> spisok, int s1) {
	vector <pair <int, int>>v;
	bool chek = true;
	for (int i = 0; i < s1; i++) {
		for (int j = 0; j < spisok[i].size(); j++) {
			if (i + 1 == spisok[i][j])
				v.push_back(make_pair(i + 1, spisok[i][j]));
			else {
				for (int k = 0; k < v.size(); k++)
				{
					if (v[k].first == i + 1 && v[k].second == spisok[i][j])
					{
						chek = false;
						break;
					}
				}
				if (chek == true) {
					v.push_back(make_pair(i + 1, spisok[i][j]));
					v.push_back(make_pair(spisok[i][j], i + 1));
				}
				chek = true;
			}
		}
	}
	return v;
}

vector <pair <int, int>> comp(vector <pair <int, int>> v1, vector <pair <int, int>> v2) {
	vector <pair <int, int>>v3;
	bool chek = true;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < v2.size(); j++) {
			if (v1[i].second == v2[j].first) {
				for (int k = 0; k < v3.size(); k++)
				{
					if (v1[i].first == v3[k].first && v2[j].second == v3[k].second)
					{
						chek = false;
						break;
					}
				}
				if (chek == false)
					break;
				else
					v3.push_back(make_pair(v1[i].first, v2[j].second));
			}
			chek = true;
		}
	}
	return v3;
}
vector <vector <int>> tests(int numtest, int n1, vector <vector <int>> a1,int n2, vector <vector <int>> a2) {
	cout << "ТЕСТ №" << numtest << endl;
	cout << "список смежностей: " << endl;
	for (int i = 0; i < n1; i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < a1[i].size(); j++) {
			cout << a1[i][j] << ' ';
		}
		cout << endl;
	}
	vector <pair <int, int>> b1 = zapisisspiska(a1, n1);
	cout << "полученные пары: " << endl;
	for (int i = 0; i < b1.size(); i++)
		cout << b1[i].first << " " << b1[i].second << endl;
	// 
	cout << "список смежностей: " << endl;
	for (int i = 0; i < n2; i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < a2[i].size(); j++) {
			cout << a2[i][j] << ' ';
		}
		cout << endl;
	}
	vector <pair <int, int>> b2 = zapisisspiska(a2, n2);
	cout << "полученные пары: " << endl;
	for (int i = 0; i < b2.size(); i++)
		cout << b2[i].first << " " << b2[i].second << endl;
	//
	cout << "композиция графов: " << endl;
	vector <pair <int, int>> b3 = comp(b1, b2);
	for (int i = 0; i < b3.size(); i++)
		cout << b3[i].first << " " << b3[i].second << endl;
	int n3;
	if (n1 > n2)
		n3 = n1;
	else
		n3 = n2;
	vector <vector <int>> a3(n3);
	for (int i = 0; i < n3; i++) {
		for (int j = 0; j < b3.size(); j++) {
			if (i + 1 == b3[j].first) {
				a3[i].push_back(b3[j].second);
			}
		}
	}
	return a3;
}
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	ifstream fin;
	string str;
	fin.open("tests.txt");
	ofstream fout;
	fout.open("output.txt");
	if (!fin.is_open() && !fout.is_open()) {
		cout << "Ошибка открытия файла/файлов";
	}
	else {
		cout << "Файл прочитан"<<endl;
		for (int i = 1; i < 6; i++) {
			int n1, num = 0;
			string str;
			getline(fin, str);
			stringstream sn1(str);
			sn1 >> n1;
			vector <vector <int>> a1(n1);
			for (int i = 0; i < n1; i++) {
				str = "";
				getline(fin, str);
				stringstream ss(str);
				while (ss >> num) {
					a1[i].push_back(num);
				}
			}
			int n2;
			getline(fin, str);
			stringstream sn2(str);
			sn2 >> n2;
			vector <vector <int>> a2(n2);
			for (int i = 0; i < n2; i++) {
				str = "";
				getline(fin, str);
				stringstream ss(str);
				while (ss >> num) {
					a2[i].push_back(num);
				}
			}
			vector <vector <int>> a3=tests(i, n1, a1, n2, a2);
			fout<< "ТЕСТ №" << i << "\n";
			for (int i = 0; i < a3.size(); i++) {
				fout << i + 1 << ": ";
				for (int j = 0; j < a3[i].size(); j++) {
					fout << a3[i][j] << ' ';
				}
				fout << "\n";
			}
		}
	}
	fin.close();
	fout.close();
}