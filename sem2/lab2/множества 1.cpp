
#include "sets.h"


// функция для проверки баланса скобок
bool checkBrackets(const string& input) {
    int open = 0, close = 0;
    for (char c : input) {
        if (c == '{' || c == '<') open++;
        if (c == '}' || c == '>') close++;
    }
    return open == close;
}

// функция для разбора множества на элементы
vector<string> parseSet(const string& input) {
    vector<string> elements; // вектор для хранения элементов множества
    size_t pos = 1; // позиция в строке с 1, чтобы пропустить  скобу "{"
    string buffer; //  накопление текущего элемента 
    int openBraces = 1; // счетчик открытых скобок 
    bool inTuple = false; // флаг, указывающий, находимся ли мы внутри кортежа 


    for (; pos < input.length(); pos++) {
        char c = input[pos];

        // если символ — '<', начинаем кортеж
        if (c == '<') {
            // если мы на верхнем уровне (openBraces == 1) и не внутри кортежа,это начало нового кортежа 
            if (openBraces == 1 && !inTuple) {
                inTuple = true; //  мы внутри кортежа
                buffer += c; // '<' в буфер 
            }
            // если мы внутри вложенной структуры, увеличиваем счетчик скобок
            else {
                openBraces++;
                buffer += c;
            }
        }
        //  '>', завершаем кортеж или вложенную структуру
        else if (c == '>') {
            // мы внутри кортежа, это конец 
            if (inTuple) {
                inTuple = false; // сбрасываем флаг, кортеж завершён
                buffer += c; //  '>' в буфер 
                elements.push_back(buffer); // добавляем готовый кортеж в вектор элементов
                buffer.clear(); // очищаем 
            }
            //  мы не внутри кортежа, т.е. это может быть конец вложенного кортежа
            else {
                openBraces--; // уменьшаем счетчик
                // если мы всё ещё внутри вложенной структуры  - '>' в буфер
                if (openBraces > 0) {
                    buffer += c;
                }
                // Если все скобки закрыты и буфер не пуст,это конец элемента
                if (openBraces == 0 && !buffer.empty()) {
                    elements.push_back(buffer); //  элемент в вектор
                    buffer.clear(); // очищаем 
                }
            }
        }
        // если текущий символ — '{', и мы не внутри кортежа, это начало вложенного множества
        else if (c == '{' && !inTuple) {
            openBraces++; // увеличиваем счетчик открытых скобок 
            // если  первый уровень вложенности + буфер не пуст, до этого был накоплен простой элемент 
            if (openBraces == 2 && !buffer.empty()) {
                elements.push_back(buffer); // добавляем простой отдельный элемент в вектор 
                buffer.clear(); // очищаем 
            }
            buffer += c; //  '{' в буфер 
        }
        //  текущий символ — '}', и мы не внутри кортежа=конец вложенного множества
        else if (c == '}' && !inTuple) {
            openBraces--; // уменьшаем счетчик
            // Если мы всё ещё внутри вложенной структуры, '}' в буфер
            if (openBraces > 0) {
                buffer += c;
            }
            //  все скобки закрыты + буфер не пуст= конец текущего элемента 
            if (openBraces == 0 && !buffer.empty()) {
                elements.push_back(buffer); //  элемент в вектор
                buffer.clear(); // очищаем 
            }
        }
        // если мы на верхнем уровне и не внутри кортежа, обрабатываем элементы верхнего уровня
        else if (openBraces == 1 && !inTuple) {
            //  текущий символ — запятая, тогда это разделитель элементов на верхнем уровне
            if (c == ',') {
                //  буфер не пуст,тогда это готовый элемент 
                if (!buffer.empty()) {
                    elements.push_back(buffer); //  элемент в вектор
                }
                buffer.clear(); // очищаем 
            }
            // если символ не запятая, добавляем его в буфер
            else {
                buffer += c;
            }
        }
        // просто добавляем символ в буфер в других случаях
        else {
            buffer += c;
        }
    }
    return elements;
}
// функция для объединения двух множеств
string unionSets(vector<string>& set1, vector<string>& set2) {
    unordered_set<string> unionSet; // хранит уникальные элементы

    for (const auto& element : set1) {
        if (!element.empty()) {       //если элемент не пустой то мы его добавляем во множетсво 1
            unionSet.insert(element);
        }
    }
    for (const auto& element : set2) {   //если элмент не пустой то де самое для мнржества 2
        if (!element.empty()) {
            unionSet.insert(element);
        }
    }

    string result = "{";               //форммирование стрки результата
    bool isFirstElement = true;   //начинаем с первого жлемента и скобки
    for (const auto& element : unionSet) {
        if (!isFirstElement) {
            result += ",";       //если элемент не первый, разделяем его запятой с другими
        }
        result += element;
        isFirstElement = false;
    }
    result += "}";   //закрываем
    return result;
}

// функция для чтения множеств из файла
vector<string> readSets(const string& path) {
    ifstream f(path); //отркываем файл по указаннному пути path
    if (!f.is_open()) {   //отркылся ли файл
        cout << "Error while opening file!" << endl;
        return {};
    }

    vector<string> sets; //хранение строк, которые будут извлечены из файла
    string buff; //строка для построчного чтения из файла
    while (getline(f, buff)) {
        size_t found = buff.find('=');  //ищем = и извлекаем все, что после него
        if (found != string::npos) {
            string dataAfterEqualSign = buff.substr(found + 1);
            if (!checkBrackets(dataAfterEqualSign)) {   //баланс скобок и сообщение если несбалансированы
                cout << "Error: unbalanced brackets in the set: " << dataAfterEqualSign << endl;
                continue;   //переход к след строке
            }
            sets.push_back(dataAfterEqualSign);     //если баланс ок, добавляем в вектор sets
        }
    }
    f.close();
    return sets;
}

// функция для создания и открытия файла
void createFile(string& path) {    //принимает ссылку на строку path чтобы изменить ее значение внутри функции
    cout << "Enter the name of the file (e.g., input.txt): ";
    cin >> path;

    ifstream checkFile(path);
    if (checkFile.good()) {    //проверка на существование файла
        cout << "File " << path << " already created." << endl;
        checkFile.close();
        return;
    }
    checkFile.close();

    ofstream f(path);
    if (!f.is_open()) {
        cout << "Error while creating file!" << endl;
        return;
    }
    cout << "File " << path << " successfully created and opened." << endl;
    f.close();
}

// функция для ввода множеств
void inputSets(const string& path) {
    int numSets;
    cout << "Enter the number of sets: ";
    cin >> numSets;
    if (numSets <= 0) {  //проверка на положительное число
        cout << "The number of sets must be greater than 0!" << endl;
        return;
    }

    ofstream f(path, ios::app);  //открытие файла в режиме добавления
    if (!f.is_open()) {
        cout << "Error while opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < numSets; i++) {  //цикл по количеству множеств
        int numElements;
        cout << "Enter the number of items in the set " << i + 1 << ": ";
        cin >> numElements;
        if (numElements <= 0) {  //положительное число
            cout << "The number of items must be greater than 0!" << endl;
            continue;
        }

        string setStr = "{";
        cout << "Enter the elements of the set " << i + 1 << " (separated by commas, use {} for sets and <> for tuples): ";
        cin.ignore();//очистка буфера ввода 

        string inputLine;
        getline(cin, inputLine); //считываем строку

        string buffer; //текущий жлемент
        bool inTuple = false; //внутри кортежа
        bool inSet = false; //внутри множества
        int elementsCount = 0; //счетчик элементов

        for (size_t j = 0; j < inputLine.length(); j++) { //посимвольная обработка строки
            char c = inputLine[j];

            if (c == '<') {  // начало кортежа
                inTuple = true;
                buffer += c;
            }
            else if (c == '>') {  //конец кортежа
                inTuple = false;
                buffer += c;
            }
            else if (c == '{') {  //начало множетсва
                inSet = true;
                buffer += c;
            }
            else if (c == '}') {  //конец множества
                inSet = false;
                buffer += c;
            }
            else if (c == ',' && !inTuple && !inSet) {  //разделяет элементы, удаляет пробелы справа и слева
                buffer.erase(0, buffer.find_first_not_of(" \t"));
                buffer.erase(buffer.find_last_not_of(" \t") + 1);
                if (!buffer.empty()) {  //если буфер не пустой
                    setStr += buffer;  //добавляем элемент в множество
                    elementsCount++;
                    if (elementsCount < numElements) setStr += ",";
                }
                buffer.clear();
            }
            else {
                buffer += c;
            }
        }

        if (!buffer.empty()) {  //если элемент последний
            buffer.erase(0, buffer.find_first_not_of(" \t"));
            buffer.erase(buffer.find_last_not_of(" \t") + 1);
            if (!buffer.empty()) {
                setStr += buffer;
                elementsCount++;
            }
        }

        setStr += "}";

        if (elementsCount != numElements) { //проверка числа элементов
            cout << "Error: the number of entered elements (" << elementsCount << ") does not match the specified number (" << numElements << ")!" << endl;
            continue;
        }

        if (!checkBrackets(setStr)) { //баланс скобок
            cout << "Error: unbalanced brackets in the set: " << setStr << endl;
            continue;
        }

        f << "set" << (i + 1) << "=" << setStr << endl;  //заносим в файл
        cout << "Set " << setStr << " successfully added." << endl;
    }
    f.close();
}

// функция для объединения всех множеств
void unionAllSets(const string& path) {   // читаем множества из файла в вектор строк
    vector<string> sets = readSets(path);
    if (sets.size() < 2) {   // достаточно ли множеств для объединения
        cout << "Not enough sets for union (need at least 2)." << endl;
        return;
    }

    vector<vector<string>> subsetsList; //хранение разобранных подмножеств
    for (const auto& set : sets) { //разбираем мнржества и добавляем в список
        subsetsList.push_back(parseSet(set));
    }

    string result = unionSets(subsetsList[0], subsetsList[1]); //первые два множества
    for (size_t i = 2; i < subsetsList.size(); i++) {  //со всеми остальными
        auto help_union = parseSet(result);
        result = unionSets(help_union, subsetsList[i]);
    }

    cout << "Union result: " << result << endl; //вывод в консоль

    // результат в файл
    ofstream f(path, ios::app);  //открываем файл для записи в режиме добавления
    if (!f.is_open()) {
        cout << "Error while opening file for writing union result!" << endl;
        return;
    }
    f << "union_result=" << result << endl;
    f.close();
    cout << "Union result has been written to the file: " << path << endl;
}