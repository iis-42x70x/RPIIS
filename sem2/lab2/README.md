# Лабораторная работа №2

## Цели:
* Выполнить свой вариант работы;
* Реализовать решение варианта на высокоуровневом ЯП(В моём случае C++)
## Вариант:
Реализовать программу, формирующую множество равное разности двух исходных множеств (без учёта кратных вхождений элементов).
## Реализация:

**Данная программа написана на C++.**

Для начала нужно определить способ задания множества. Оно задавалось в виде {A, B, {C, <D, E>, F}}.

В файле `Set.hpp` описаны функции для данных типа `Set`(множество). В файле `Tuple.hpp` - для типа `Tuple`. В файле `Difference.hpp` описана сама реализация нахождения разности 2-х множеств.

### 1. Нормализация множества
Данная функция нормализует множество, приводя его в каноническую форму и сохраняет его в структуру типа `Set` для дальнейшей обработки:
```
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
```
### 2. Нахождение разности
Данная функция, по сути, делает почти всю работу программы:
```
template<typename T>
Set<T> Difference(Set<T> a, Set<T> b)
{
	Set<T> s;
	
    for(size_t i = 0; i < a.getsize(); i++){
        bool foundInB = false;
        for(size_t j = 0; j < b.getsize(); j++){
            if(a.elements[i] == b.elements[j]){
                foundInB = true;
                break;
            }
        }
        if(!foundInB)
            s.add(a.elements[i]);
    }
	
	return s;
}

```
### 3. Функция для правильной обработки множества
Данная рекурсивная функция считывает множество из строки и сохраняет его в структуру типа `Set`. 
```
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
```
Реализована аналогичная функция для считывания ориентированных множеств.

## Тесты

### 1:

Входные данные:
```
{ < 1 , 2, { 4 , 3 } >,5 }
{ 5,< 1,2 { 3,4 } > }
```
Результат программы:
```
Inputed sets:
{ < 1, 2, { 4, 3 } >, 5 }
{ 5, < 1, 2, { 3, 4 } > }
Difference:
{  }
```

### 2:

Входные данные:
```
{}
{}
```
Результат программы:
```
Inputed sets:
{  }
{  }
Difference:
{  }
```

### 3:

Входные данные:
```
{ <a, b  }
{<>}
```
Результат программы:
```
The set is invalid. Please, fix the file.
```

### 4:

Входные данные:
```
{ < <a, b>, c>, d }
{ < <a,b >, c> }
```
Результат программы:
```
Inputed sets:
{ < < a, b >, c >, d }
{ < < a, b >, c > }
Difference:
{ d }
```

### 5:

Входные данные:
```
{a, <e, {b, c}, d> }
{<d, {b,c}, e>}
```
Результат программы:
```
Inputed sets:
{ a, < e, { b, c }, d > }
{ < d, { b, c }, e > }
Difference:
{ a, < e, { b, c }, d > }
```

### 6:

Входные данные:
```
{{{a}}}
{{{b}}}
```
Результат программы:
```
Inputed sets:
{ { { a } } }
{ { { b } } }
Difference:
{ { { a } } }
```


### 7:

Входные данные:
```
{{<a,b>}}
{{<a,b>}}
```
Результат программы:
```
Inputed sets:
{ { < a, b > } }
{ { < a, b > } }
Difference:
{  }
```

### 8:

Входные данные:
```
{{<a,b>}}
{{<b,a>}}
```
Результат программы:
```
Inputed sets:
{ { < a, b > } }
{ { < b, a > } }
Difference:
{ { < a, b > } }
```

Все тесты выполнены верно, программа выполняет свои функции.

## Вывод
В ходе данной лабораторной работы:
- Была реализована библиотека для работы с множествами
- Функции библиотеки позволяют находить разность двух множеств (без учёта кратных вхождений элементов).
- Алгоритм перенесён на ЯП С++. 

