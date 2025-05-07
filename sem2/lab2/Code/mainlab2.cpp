/*Читает два множества из файла (возможны вложенные множества и кортежи).

Проверяет корректность скобок и символов.

Разбирает строку в структуру данных (множество и кортежи).

Вычисляет симметрическую разность между этими двумя множествами.

Печатает результат.*/

#include "simdiff.hpp"
#include "Tuple.hpp"
#include "Sets.hpp"
#include <fstream>
#include <stack>
using namespace std;

// Находит позицию закрывающей фигурной скобки
size_t findClosingBracePosition(const string &inputStr, size_t startPos) {
    for (size_t i = startPos; i < inputStr.size(); i++) {
        if (inputStr[i] == '}') {
            return i;
        }
    }
    return string::npos;
}

// Находит позицию закрывающей угловой скобки
size_t findClosingAngleBracketPosition(const string &inputStr, size_t startPos) {
    for (size_t i = startPos; i < inputStr.size(); i++) {
        if (inputStr[i] == '>') {
            return i;
        }
    }
    return string::npos;
}

// Предварительное объявление
Set<string> parseSetFromString(string &, size_t);

// Парсит кортеж из строки
Tuple<string> parseTupleFromString(string &tupleString, size_t startPos = 0) {
    
	//Создаём пустой Tuple<string> resultTuple
	Tuple<string> resultTuple;
    string currentElement;
    
	//Проходим по строке символ за символом
    for (size_t i = startPos; i < tupleString.size(); i++) {
        if (tupleString[i] == ' ') { //Собираем символы в currentElement, пока не встретим пробел ' '.
            //Если currentElement == "<" — начинается вложенный кортеж: вызываем parseTupleFromString рекурсивно.
			if (currentElement == "<") { 
                resultTuple.append(parseTupleFromString(tupleString, i + 1));
                size_t closingPos = findClosingAngleBracketPosition(tupleString, i);
                tupleString.erase(i - 1, closingPos - i + 3);
                i -= 2;
            }
            else if (currentElement == ">") {
                return resultTuple;
            }
			//Если currentElement == "{" — начинается вложенное множество: вызываем parseSetFromString
            else if (currentElement == "{") {
                // Парсинг вложенного множества
                resultTuple.append(parseSetFromString(tupleString, i + 1));
                size_t closingPos = findClosingBracePosition(tupleString, i);
                tupleString.erase(i - 1, closingPos - i + 3);
                i -= 2;
            }
			// Особенность: после парсинга  структур они удаляются из строки чтобы не мешали следующей итерации
            else {
                if (!currentElement.empty()) {
                    resultTuple.append(currentElement);
                }
            }
            currentElement.clear();
        }
        else {
            currentElement.push_back(tupleString[i]);
        }
    }
    
    if (!currentElement.empty() && currentElement != ">") {
        resultTuple.append(currentElement);
    }
    
    return resultTuple;
}

// Парсит множество из строки
//Логика как в parseTupleFromString, только это для множества;
Set<string> parseSetFromString(string &setString, size_t startPos) {
    Set<string> resultSet;
    string currentElement;

    for (size_t i = startPos; i < setString.size(); i++) {
        if (setString[i] == ' ') {
            if (currentElement == "{") {
                // Рекурсивный парсинг вложенного множества
                resultSet.insert(parseSetFromString(setString, i + 1));
                size_t closingPos = findClosingBracePosition(setString, i);
                setString.erase(i - 1, closingPos - i + 3);
                i -= 2;
            }
            else if (currentElement == "}") {
                return resultSet;
            }
            else if (currentElement == "<") {    
                // Парсинг вложенного кортежа
                resultSet.insert(parseTupleFromString(setString, i + 1));
                size_t closingPos = findClosingAngleBracketPosition(setString, i);
                setString.erase(i - 1, closingPos - i + 3);
                i -= 2;
            }
            else {
                if (!currentElement.empty()) {
                    resultSet.insert(currentElement);
                }
            }
            currentElement.clear();
        }
        else {
            currentElement.push_back(setString[i]);
        }
    }
    
    if (currentElement == "}") {
        return resultSet;
    }
    if (!currentElement.empty()) {
        resultSet.insert(currentElement);
    }
    
    return resultSet;
}

// Проверяет, правильно ли расставлены скобки {} и <>
bool validateBrackets(const string &inputStr) {

    stack<char> bracketStack;
    //Идем по строке:
	for (char currentChar : inputStr) {
        switch (currentChar) {
            case '{':
                bracketStack.push('}'); //{ кладем } в стек.
                break;
            case '<':
                bracketStack.push('>'); //< кладем > в стек.
                break;
            case '}':
            case '>':
                if (bracketStack.empty() || bracketStack.top() != currentChar) {
                    return false; //Если стек пустой или символ не совпадает с вершиной — ошибка.
                }
                bracketStack.pop(); //Иначе — убираем вершину стека.
                break;
            default:
                break;
        }
    }
	//Если в конце стек пустой — скобки сбалансированы.
    return bracketStack.empty();
}

// Читает множество из файла
Set<string> readSetFromFile(ifstream &inputFile) {
    
	Set<string> resultSet;
    string lineContent;
    getline(inputFile, lineContent); //читаем строку

	//Проверяет, что строка начинается с { и заканчивается на }.
    if (lineContent.front() != '{' || lineContent.back() != '}') {
        cout << "Неверный формат множества. Исправьте его!\n";
        exit(EXIT_FAILURE);
    }
    
    // Удаляем внешние скобки
    lineContent.erase(lineContent.begin());
    lineContent.pop_back();

    if (lineContent.empty()) {
        return resultSet;
    }

    // Очистка и форматирование строки; удаляем пробелы и запятые
    for (size_t i = 0; i < lineContent.size();) {
        if (lineContent[i] == ' ') {
            lineContent.erase(i, 1);
        } else {
            i++;
        }
    }
    for (size_t i = 0; i < lineContent.size(); i++) {
        if (lineContent[i] == ',') {
            lineContent[i] = ' '; 
        }
    }
    
	//Проверяет скобки и символы; Вставляет пробелы между элементами для удобства разбора.
    for (size_t i = 0; i < lineContent.size() - 1; i++) {
        if (lineContent[i] != ' ' && lineContent[i+1] != ' ') {
            lineContent.insert(i+1, " ");
        }
    }

    if (!validateBrackets(lineContent)) {
        cout << "Неподходящие скобки. Исправте текст в файле!\n";
        exit(EXIT_FAILURE);
    }

    // Проверка допустимых символов
    for (char ch : lineContent) {
        if (!isalpha(ch) && !isdigit(ch) &&
            ch != ' ' && ch != ',' &&
            ch != '}' && ch != '{' &&
            ch != '<' && ch != '>') {
            cout << "Неподходящие символы. Исправте текст в файле!\n";
            exit(EXIT_FAILURE);
        }
    }

	//Вызывает parseSetFromString — превращает строку в объект Set.
    resultSet = parseSetFromString(lineContent, 0);
    return resultSet;
}

int main() {
    //открываем файл
	ifstream inputFile("Testing.txt");
    if (!inputFile) {
        cerr << "Ошибка. Файл не открылся.\n";
        return 1;
    }

	//Читаем два множества из файла (по одной строке каждое).
    Set<string> firstSet = readSetFromFile(inputFile);
    Set<string> secondSet = readSetFromFile(inputFile);
    
    cout << "Ввнденное множество:\n" << firstSet << endl << secondSet << endl;
    Set<string> differenceResult = SymmetricDifference(firstSet, secondSet);
    cout << "Симметрическая разница:\n" << differenceResult;

    inputFile.close();
    return 0;
}