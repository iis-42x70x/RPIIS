#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	string path = "matrix.txt";
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout << "Файл не найлен\n";
	}
	else
	{
        int count = 0;
        int temp;

        while (!fin.eof())
        {
            fin >> temp;
            count++;
        }
        
        fin.seekg(0, ios::beg);
        fin.clear();

        
        int count_space = 0;
        char symbol;
        while (!fin.eof())
        {           
            fin.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }
        

        
        fin.seekg(0, ios::beg);
        fin.clear();

        

        int rows = count / (count_space + 1);
        int columns = count_space + 1;

        double** matrix;
        matrix = new double* [rows];
        for (int i = 0; i < rows; i++) matrix[i] = new double[columns];

        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                fin >> matrix[i][j];

        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
                cout << matrix[i][j] << "\t";
            cout << "\n";
        }


        bool check2sv = true;        
        for (int i = 0; i < rows; i++) 
        {
            int count = 0;
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] == 1)
                {
                    count++;                   
                }
                
            }
            if (count < 2) {
                
                check2sv = false;
            }
        }

        if (check2sv != false)
        {
            cout << "Граф двусвязный\n";
        }
        else
        {
            cout << "Граф не двусвязный\n";
        }
        

        for (int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;

        fin.close();
        
	}

	
	
}
