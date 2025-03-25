#include "header.h"

int main(int argc, char* argv[]) {
	string filename;
	if (argc > 1) {
		filename = argv[1];
	}
	else {
		while (true) {
			if (filename.empty()) {
				cout << "Enter input file name: ";
				cin >> filename;
			}
			ifstream file(filename);
			if (file) {
				file.close();
				break;
			}
			cerr << "Error: Unable to open file '" << filename << "'. Try again.\n";
			filename.clear();
		}
	}
	findAllCombinations(filename);
	cout << "Processing complete. Resultst saved in output.txt" << endl;
	return 0;
}