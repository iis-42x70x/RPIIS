#include "Header.h"

vector<string> Union::getSet()
{
	return set;
}

vector<string> Union::setSet(vector<string>& new_set)
{
	set = new_set;
	normalizeSet();
	return set;
}

vector<string> Union::setsUnion(vector<string>& result)
{
	for (int i = 0; i < set.size(); i++)
	{
		result.push_back(set[i]);
	}
	Union temp;
	temp.setSet(result);
	return temp.getSet();
}

bool Union::Breckets_Check(string& str)
{
	stack<char> stack;
	map<char, char> breckets = { { '{', '}' }, { '<', '>' } };
	for (char c : str)
	{
		if (c == '{' || c == '<')
		{
			stack.push(c);
		}
		else if (c == '}' || c == '>')
		{
			if (stack.empty() || breckets[stack.top()] != c)
				return false;
			stack.pop();
		}
	}

	return stack.empty();
}

bool Union::Checking_Set(string& set)
{
	bool previous_comma = true;
	int brecket_level = 0;

	for (char c : set)
	{
		if (c == '{' || c == '<')
		{
			brecket_level++;
		}
		else if (c == '}' || c == '>')
		{
			brecket_level--;
			if (brecket_level < 0)
				return false;
		}

		if (c == ',')
		{
			if (previous_comma)
			{
				cout << "Неверный ввод несколько запятых подряд";
				return false;
			}
			previous_comma = true;
		}
		else if(!isspace(c))
		{
			previous_comma = false;
		}
	}

	if (previous_comma)
	{
		cout << "Запятая не может быть последним элементом";
		return false;
	}

	return true;
}

string Union::removeSpaces(string& str)
{
	string result;
	for (char c : str)
	{
		if (!isspace(c))
			result += c;
	}

	return result;
}

vector <string> Union::parseSet(string str)
{
	vector<string> result;

	str = removeSpaces(str);
	if (str.empty())
	{
		cout << "Строка пуста!" << endl;
		return result;
	}

	if (str[0] != '{' && str[str.size() - 1] != '}')
	{
		cout << "Множество должно быть в фигурных скобках!" << endl;
		return result;
	}

	if (!Breckets_Check(str))
	{
		cout << "Неверная структура скобок!" << endl;
		return result;
	}

	if (!Checking_Set(str))
	{
		return result;
	}

	str = str.substr(1, str.length() - 2);

	if (str.empty())
		return result;

	string current;
	int breckets_count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (c == '{' || c == '<') breckets_count++;
		else if (c == '}' || c == '>') breckets_count--;

		if (c == ',' && breckets_count == 0)
		{
			if(!current.empty())
			{
				if (ValidElement(current))
				{
					result.push_back(current);
				}
				else
				{
					cout << "Неверный элемент!" << endl;
					return vector<string>();
				}
				current.clear();
			}
		}
		else
		{
			current += c;
		}
	}

	if (!current.empty())
	{
		if (ValidElement(current))
		{
			result.push_back(current);
		}
		else
		{
			cout << "Неверный элемент!" << endl;
			return vector<string>();
		}
	}
	removeDuplicates(result);
	return result;
}

bool Union::ValidElement(string& elem)
{
	if (elem.empty()) return false;

	if (elem[0] == '-' || isdigit(elem[0]))
	{
		bool valid = true;
		for (int i = 1; i < elem.length(); i++)
		{
			if (!isdigit(elem[i]))
			{
				valid = false;
				break;
			}
		}

		if (!valid) return false;
		return true;
	}

	if (isalpha(elem[0]))
	{
		bool valid = true;
		for (int i = 1; i < elem.length(); i++)
		{
			if (!isalpha(elem[i]))
			{
				valid = false;
				break;
			}
		}

		if (!valid) return false;
		return true;
	}

	if (elem[0] == '<' && elem[elem.length() - 1] == '>') {
		return Breckets_Check(elem);
	}

	if (elem[0] == '{' && elem[elem.length() - 1] == '}') {
		return Breckets_Check(elem);
	}

	return false;
}

void Union::removeDuplicates(vector<string>& set)
{
	if (set.empty()) return;

	vector<string> unique;
	for (int i = 0; i < set.size(); i++)
	{
		bool flag = true;
		for (int j = 0; j < unique.size(); j++)
		{
			if (set[i] == unique[j])
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			unique.push_back(set[i]);
		}
	}

	set = unique;
}

void printUnion(vector<string> result)
{
	if (result.empty())
	{
		cout << "{}" << endl;
		return;
	}

	cout << "{ ";
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i];
		if (i < result.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << " }" << endl;
}

bool Union::Correct_Set(string str)
{
	if (removeSpaces(str) == "{}") return true;
	return !parseSet(str).empty();
}

void Union::add(string& str)
{
	vector<string> newElements = parseSet(str);
	set.insert(set.end(), newElements.begin(), newElements.end());
	normalizeSet();
}

void read_file(vector<Union>& sets)
{
	ifstream file("test.txt");
	if (file.is_open())
	{
		int new_size;
		file >> new_size;
		file.ignore();
		sets.resize(new_size);
		for (int i = 0; i < sets.size(); i++)
		{
			string str;
			getline(file, str);
			sets[i].add(str);
		}
		file.close();
	}
	else
	{
		cout << "Не удалось открыть файл" << endl;
	}
}

string Union::sortSetString(string str) {
	if (str.empty() || (str[0] != '{' && str[0] != '<')) return str;

	string inner = str.substr(1, str.length() - 2);
	vector<string> elements;

	string current;
	int breckets_count = 0;

	for (int i = 0; i < inner.length(); i++) {
		char c = inner[i];
		if (c == '{' || c == '<') breckets_count++;
		else if (c == '}' || c == '>') breckets_count--;

		if (c == ',' && breckets_count == 0) {
			if (!current.empty()) {
				elements.push_back(current);
				current.clear();
			}
		}
		else {
			current += c;
		}
	}
	if (!current.empty()) {
		elements.push_back(current);
	}

	for (int i = 0; i < elements.size(); i++) {
		elements[i] = sortSetString(elements[i]);
	}

	sort(elements.begin(), elements.end());

	string result = str[0] == '{' ? "{" : "<";
	for (int i = 0; i < elements.size(); i++) {
		result += elements[i];
		if (i < elements.size() - 1) result += ",";
	}
	result += str[0] == '{' ? "}" : ">";

	return result;
}

void Union::normalizeSet() {
	for (int i = 0; i < set.size(); i++) {
		set[i] = sortSetString(set[i]);
	}
	removeDuplicates(set);
}