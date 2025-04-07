#include "Difference.hpp"
#include "Tuple.hpp"
#include "Set.hpp"
#include <fstream>
#include <stack>
using namespace std;


size_t findClosestClosingBrace(const string &s, size_t idx)
{
	for (int i = idx; i < s.size(); i++)
	{
		if (s[i] == '}')
		{
			return i;
		}
	}
	return string::npos;
}

size_t findClosestClosingAngleBracket(const string &s, size_t idx)
{
	for (int i = idx; i < s.size(); i++)
	{
		if (s[i] == '>')
		{
			return i;
		}
	}
	return string::npos;
}

Set<string> getSetByString(string &, size_t);

Tuple<string> getTupleByString(string &tupleStr, size_t beginIdx = 0)
{
	Tuple<string> t;
	string currentValue;
	for (size_t i = beginIdx; i < tupleStr.size(); i++)
	{
		if (tupleStr[i] == ' ')
		{
			if (currentValue == "<")
			{
				t.add(getTupleByString(tupleStr, i + 1));
				tupleStr.erase(i - 1, findClosestClosingAngleBracket(tupleStr, i) - i + 3);
				i -= 2;
			}
			else if (currentValue == ">")
			{
				return t;
			}
			else if (currentValue == "{")
			{
				t.add(getSetByString(tupleStr, i + 1));
				tupleStr.erase(i - 1, findClosestClosingBrace(tupleStr, i) - i + 3);
				i -= 2;
			}
			else
			{
				if (!currentValue.empty()) {
					t.add(currentValue);
				}
			}
			currentValue.clear();
		}
		else
		{
			currentValue.push_back(tupleStr[i]);
		}
	}
	
	if (!currentValue.empty() && currentValue != ">")
	{
		t.add(currentValue);
	}
	
	return t;
}

Set<string> getSetByString(string &setStr, size_t beginIdx)
{
	Set<string> s;
	string currentValue;

	for (size_t i = beginIdx; i < setStr.size(); i++)
	{
		if (setStr[i] == ' ')
		{
			if (currentValue == "{")
			{
				s.add(getSetByString(setStr, i + 1));
				setStr.erase(i - 1, findClosestClosingBrace(setStr, i) - i + 3);
				i -= 2;
			}
			else if (currentValue == "}")
			{
				return s;
			}
			else if (currentValue == "<")
			{	
				s.add(getTupleByString(setStr, i + 1));
				setStr.erase(i - 1, findClosestClosingAngleBracket(setStr, i) - i + 3);
				i -= 2;
			}
			else
			{
				if (!currentValue.empty()) {
					s.add(currentValue);
				}
			}
			currentValue.clear();
		}
		else
		{
			currentValue.push_back(setStr[i]);
		}
	}
	
	if (currentValue == "}")
	{
		return s;
	}
	if (!currentValue.empty())
	{
		s.add(currentValue);
	}
	
	return s;
}

bool bracketsAreCorrect(const string &s)
{
	stack <char> balance;
	for (char current : s)
	{
		switch (current)
		{
			case '{':
				balance.push('}');
				break;
			case '<':
				balance.push('>');
				break;
			case '}':
			case '>':
				if (balance.empty() || balance.top() != current)
				{
					return false;
				}
				balance.pop();
				break;
			default:
				break;
		}
	}
	return balance.empty();
}

Set <string> getSet(ifstream &file)
{
	Set <string> s;
	string Str;
	getline(file, Str);

	if (Str.front() != '{' || Str.back() != '}')
	{
		cout << "The set is invalid. Please, fix the file.\n";
		exit(EXIT_FAILURE);
	}
	Str.erase(Str.begin());
	Str.pop_back();

	if( Str.size() == 0)
		return s;

	for(int i = 0; i<Str.size();){
		if(Str[i] == ' ')
			Str.erase(i,1);
		else	
			i++;
	}
	for(int i = 0; i<Str.size(); i++){
		if(Str[i] == ',')
			Str[i] = ' ';
	}
	for(int i=0; i<Str.size()-1; i++){
		if(Str[i] != ' ' && Str[i+1] != ' '){
			Str.insert(i+1, " ");
		}
	}

	if (!bracketsAreCorrect(Str)) {
		cout << "The set is invalid. Please, fix the file.\n";
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Str.size(); i++) {
		if (!isalpha(Str[i]) && !isdigit(Str[i]) &&
			Str[i] != ' ' && Str[i] != ',' &&
		    Str[i] != '}' && Str[i] != '{' &&
		    Str[i] != '<' && Str[i] != '>')
		{
			cout << "The set is invalid. Please, fix the file.\n";
			exit(EXIT_FAILURE);
		}
	}

	s = getSetByString(Str, 0);
	
	return s;
}

int main()
{

	ifstream file("Test8.txt");
	if (!file) {
        cerr << "Failed to open file.\n";
        return 1;
    }

	Set <string> s1 = getSet(file);
	Set <string> s2 = getSet(file);
	cout<<"Inputed sets:\n"<<s1<<endl<<s2<<endl;
    Set <string> res = Difference(s1, s2);
	cout << "Difference:\n" << res;

	file.close();
    return 0;
}