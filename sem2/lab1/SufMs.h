#pragma once

#include <iostream>
#include <cmath>
#include <string>

	
	struct suffMs
	{
		static const int alphabet = 256;
		static const int maxlen = 64;


		int size = 0;
		int suffarr[maxlen];
		char string[maxlen];

		int k;
		int** c;


			// Ввод строки
			void inputString(suffMs*);

			// Построение суффиксного массива
			void buildSuffArr(suffMs*);

			// Нахождение минимального циклического сдвига строки
			int minCycle();

			// Нахождение наибольшего общего префикса двух подстрок	
			void largestCommonPref(int i, int j);

			// Вывод суффиксного массива
			void printArr();
	
	};
