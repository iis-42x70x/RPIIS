#include "Header.hpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	
	string str;
	while(true){
		cout << "Введите множество:" << endl;
		getline(cin, str);
		if (is_correct(str)) {
			break;
		}
		else {
			cout << "Некорректный ввод" << endl;
		}
	}
	
	vector<string> elements= parse(str);
	
	int n = 0;
	while (true) {
		cout << "Введите параметр n: ";
		if (!(cin >> n)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Некоректный ввод\n";
			continue;
		}
		else if (n > elements.size()) {
			cout << "Значение параметра не должно превышать количестов элементов" << endl;
		}
		else break;
	}

	set<set<string>> combination = combinations(elements, n);

	for (auto& comb : combination) {
		cout << "{ ";
		for (auto& el : comb) {
			cout << el << " ";
		}
		cout << "}" << endl;
	}

	return 0;
}