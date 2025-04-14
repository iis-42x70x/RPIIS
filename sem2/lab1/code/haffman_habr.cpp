#include <iostream>
#include "Header.h"
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

int main()
{
	int choose;
	cout << "Enter 1 if you want to type your own message, type 2 if ypu want to use ready messages from file: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
	{
		char handwriting[100];
		cin.ignore();
		cout << "Enter your message: ";
		cin.getline(handwriting, 100);
		cout << endl;
		buildHuffmanTree(handwriting);
		break;
	}
	case 2:
	{
		string text;
		ifstream fin;
		fin.open("testing.txt");
		while (getline(fin, text))
		{
			buildHuffmanTree(text);
			cout << endl << endl;
		}
		break;
	}
	default:
	{
		cout << "Wrong. Try again.";
		return 0;
	}
	}
	return 0;
}