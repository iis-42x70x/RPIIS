
#include "C:\Users\omen\source\repos\SufMs\SufMs\SufMs.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "RU");
	suffMs suffixArray;

	suffixArray.inputString(&suffixArray);

	suffixArray.buildSuffArr(&suffixArray);
	cout << endl;

	cout << "Минимальный циклический сдвиг строки: \n";
	cout << suffixArray.minCycle();

	cout << endl;

	suffixArray.largestCommonPref(1, 3);
}
