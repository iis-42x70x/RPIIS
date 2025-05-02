# Лабараторная работа #2

## Цели работы:

* Изучить базовые понятия теории множеств
* Научиться реализовывать основные алгоритмы при работе со множествами

## Задачи:

* Разработать библиотеку для работы со множествами на любом императивном языке программирования
* Разработать тесты, которые демонстрирует работоспособность реализованной библиотеки

## Вариант:

8. Реализовать программу, формирующую без повторений всевозможные
неориентированные множества из элементов исходного неориентированного множества,
количество элементов в сформированных множествах должно быть равно исходному
натуральному n.

## Понятия:

* _Множество_ – простейшая информационная конструкция и математическая структура,позволяющая рассматривать какие-то объекты как целое, связывая их.

* _Элементы множества_ – объекты, связываемые некоторым множеством.
* _Подмножество_ – множество, все элементы которого принадлежат другому множеству.
* _Мощность множества_ – количество элементов во множестве .
* _Кортеж_ – упорядоченное множество элементов.


Множества бывают:

* _Ориентированными_ (важен порядок элементов во множестве) 
* _Неориентированными_ (порядок элементов во множестве не важен)



## Алгоритмы: 

### Проверка входной строки на правильность: 

```cpp
bool is_correct(string str) {

	size_t pos = str.find('=');
	string name = str.substr(0, pos);
	bool corname = false;
	for (int i = 0; i < name.size(); i++) {
		int el = name[i];
		if (!isspace(el)) {
			corname = true;
			break;
		}
	}
	if (!corname) return false;

	if (pos != string::npos) {
		str = str.substr(pos + 1);
		str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
	}

	if (str.front() != '{' || str.back() != '}') return false;
	str = str.substr(1, str.size() - 2);

	size_t last_symb = str.find_last_not_of(" \t");
	if (last_symb != string::npos && str[last_symb] == ',') {
		return false;
	}

	stack<char> skobki;
	string current;

	for (int i = 0; i < str.size(); i++) {
		char element = str[i]; 
		
		if(element == '{' || element == '<') {
			skobki.push(element);
			current += element;
		}
		else if (element == '}' || element == '>') {
			if (skobki.empty()) return false;
			char begin = skobki.top();
			if (element == '}' && begin != '{' || element == '>' && begin != '<') return false;
			skobki.pop();
			current += element;
		}

		else if (element == ',') {
			if (current.empty()) return false;
			current.clear();
		}
		else if (!isspace(element)) {
			current += element;
		}
	}

	vector<string> str_parse = parse(str);
	for (auto& elem : str_parse) {
		if (elem.empty() || elem == "," || elem == "{,}" || elem == "<,>") {
			return false;
		}
	}

	string value = str.substr(pos+1);
	value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

	for (size_t i = 1; i < value.size(); ++i) {
		if ((value[i - 1] == '}' || value[i - 1] == '>') &&
			(value[i] == '{' || value[i] == '<')) {
			return false;
		}
	}

	if (!skobki.empty()) return false;

	return true;
}
```

### Разбиение множества на элементы: 

```cpp
vector<string> parse(string str) {
	vector<string> str_elements;
	string current;
	int vlozh = 0;

	size_t pos = str.find('=');
	if (pos != string::npos) {
		str = str.substr(pos+1);

		size_t start = str.find_first_not_of(" \t");
		if (start != string::npos) {
			str = str.substr(start);
		}
	}

	if (str[0] == '{' && str[str.size()-1] == '}') {
		str = str.substr(1, str.size()-2);
	}

	for (int i = 0; i < str.size(); i++) {
		char el = str[i];

		if (el == '{' || el == '<') {
			if (vlozh == 0 && !current.empty()) {
				str_elements.push_back(current);
				current.clear();
			}
			vlozh++;
			current += el;
		}
		else if (el == '}' || el == '>') {
			current += el;
			vlozh--;
			if (vlozh == 0 && !current.empty()) {
				str_elements.push_back(current);
				current.clear();
			}
		}
		else if (el == ',' && vlozh == 0) {
			if (!current.empty()) {
				current.erase(remove_if(current.begin(), current.end(), ::isspace), current.end());
				str_elements.push_back(current);
				current.clear();
			}
		}
		else if (!isspace(el)) {
			current += el;
		}
	}
	if (!current.empty()) {
		str_elements.push_back(current);
	}

	return str_elements;

}
```

### Создание комбинаций: 

```cpp
set<set<string>> combinations(vector<string>& elements, int n, int start, vector<string> current) {
	set<set<string>> result;

	if (current.size() == n) {
		result.insert(set<string>(current.begin(), current.end()));
		return result;
	}

	for (int i = start; i < elements.size(); i++) {
		current.push_back(elements[i]);
		set<set<string>> partial = combinations(elements, n, i + 1, current);
		result.insert(partial.begin(), partial.end());
		current.pop_back();
	}

	return result;
}
```

## Тесты:
```cpp
//тесты isCorrect
TEST(TestCase, TestIsCorrect1) {
	string input = "{}";
	EXPECT_TRUE(is_correct(input));
}

TEST(TestCase, TestIsCorrect2) {
	string input = "Abacadabra    =   {<a,b,<c,d>, {b, asd, as10xc}>}";
	EXPECT_TRUE(is_correct(input));
}

TEST(TestCase, TestIsCorrect3) {
	string input = "A = {axcv, ZCXasd, <,    >, 1223}";
	EXPECT_FALSE(is_correct(input));
}

//тесты на индивидуальное задание
TEST(TestCase, TestCombinations1){
	string input = "A = {axcv, ZCXasd, 1223, <b,   c>}";
	vector<string> parsering = parse(input);
	int n = 2;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 6);
}

TEST(TestCase, TestCombinations2) {
	string input = "A = {321, asd,  554 ,ZCXasd, 1223, <b, {}   c>}";
	vector<string> parsering = parse(input);
	int n = 3;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 20);
}

TEST(TestCase, TestCombinations3) {
	string input = "A = {a,b,c   ,d,e,f,g,h,i,j}";
	vector<string> parsering = parse(input);
	int n = 1;
	EXPECT_EQ(numOfSets(combinations(parsering,n)), 10);
}

//тесты на contains

TEST(TestCase, TestContains1) {
	string input = "A = {axcv, ZCXasd, 1223, <b,   c>}";
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "<b,c>"));
}

TEST(TestCase, TestContains2) {
	string input = "A = {321, xui,  554 ,ZCXasd, 1223, <b, {}   c>}";
	vector<string> parsering = parse(input);
	EXPECT_FALSE(contains(parsering, "123"));
}

TEST(TestCase, TestContains3) {
	string input = "A = {a,b,c, {}   ,d,e,f,g,h,i,j}";
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "{}"));
}

//тест на чтение из файлов

TEST(TestCase, TestFileRead1) {
	ofstream File("test.txt");
	File << "A = {axcv, ZCXasd, {<}>, 1223}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	EXPECT_FALSE(is_correct(input));
	remove("test.txt");
}

TEST(TestCase, TestFileRead2) {
	ofstream File("test.txt");
	File << "A = {1,asd,<1,{25}>,{<6,9>}}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	int n = 3;
	EXPECT_EQ(numOfSets(combinations(parsering, n)), 4);
	remove("test.txt");
}

TEST(TestCase, TestFileRead3) {
	ofstream File("test.txt");
	File << "A = {ad,23,{ad,s},<7,3>}";
	File.close();
	string input = ReadFile("test.txt");
	vector<string> parsering = parse(input);
	EXPECT_TRUE(contains(parsering, "<7,3>"));
	remove("test.txt");
}
```

## Результат работы тестов: 

![image]()

## Вывод:
Мной была разработана библиотека по работе со множествами. В ней я реализовал операцию создания всевозможных уникальных подмножеств размером n из множества .

## Материалы и источники:

* [itmm.unn.ru](https://itmm.unn.ru/wp-content/uploads/sites/19/2020/04/DM-MM-uchebnik.pdf) - учебное пособие "Дискретная математика", В.Е. Алексеев.