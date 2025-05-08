# Лабораторная работа №2

## Задача:
$\textcolor{#4b0082}{\textit{Вариант 12}}$ Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (с учётом кратных вхождений элементов).
## Цель:
* Исследовать свойства структур данных и разработать библиотеку алгоритмов обработки структур данных (для нахождения симм разности мультимножеств, считанных из файла).
* Разработать Гугл Тесты, которые проверяют успешное выполнение всех функций

## Список ключевых понятий:
* $\textcolor{#4b0082}{\textbf{Множество}}$ — простейшая информационная конструкция и математическая структура,
позволяющая рассматривать какие-то объекты как целое, связывая их.
* $\textcolor{#4b0082}{\textbf{Мультимножество (множество с учётом кратных вхождений элементов}}$ модификация понятия множества, допускающая включение одного и того же элемента в совокупность по нескольку раз. Число элементов в мультимножестве, с учётом повторяющихся элементов, называется его размером или мощностью.различаются не более, чем на единицу.
* $\textcolor{#4b0082}{\textbf{Симметрической разностью}}$ неориентированных множеств ***A*** и ***B*** *с учётом кратных
вхождений* элементов будем называть неориентированное множество S тогда и только тогда,
когда для любого x истинно ***S|x| = max{A|x|-B|x|, B|x|-A|x|}***.

![png-transparent-symmetric-difference-number-set-complement-rożnica-zbiorow-circle-purple-angle-text](https://github.com/iis-32170x/RPIIS/assets/145003765/dc7ad5f2-f5ed-4c44-89a2-8f2200f2b8f4)

## Алгоритмы операций над мультимножествами

### Считывание мультимножеств из файла

* Если файл указан некорректно или  его не существует, вылетает сообщение "Ошибка открытия файла!" и выполнение программы завершается (связано с функцией запуска программы ниже)).
*  Иначе посимвольно считываем файл, записывая в MultiSet[0] первое мультимножество, в MultiSet[1] второе..
   * в зависимости от того, какой символ считался (цифра, фигурная скобка, запятая, пробел, переменная...), он записывается в соответствующее поле мультимножества (элемент, кратность или просто счетчик скобок, который помогает определить начало и конец другого мультимножества или подмножество внутри него)

``` c++
void GetSets(Set MultiSet[], string path) {
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла!");
    }

    int curr_brackets_count = 0;

    char ch;
    int m = -1;
    MultiSet[0].set_count = m + 1;
    int elem_in_set = 0;
    while (file.get(ch)) {
        if (ch == '{') {
            if (curr_brackets_count > 0) {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
                curr_brackets_count++;
            }
            else {
                m++;
                MultiSet[0].set_count = m + 1;
                elem_in_set = 0;
                curr_brackets_count++;
            }
        }
        else if (ch == ',') {
            if (curr_brackets_count == 1) {
                elem_in_set++;
            }
            else {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
            }
        }
        else if (isdigit(ch)) {
            if (curr_brackets_count == 1) {
                if (MultiSet[m].Elem[elem_in_set].multiplicity == 1 && !MultiSet[m].Elem[elem_in_set].IsAlone) {
                    MultiSet[m].Elem[elem_in_set].multiplicity = (ch - '0');
                    MultiSet[m].Elem[elem_in_set].IsAlone = true;
                }
                else {
                    MultiSet[m].Elem[elem_in_set].multiplicity = MultiSet[m].Elem[elem_in_set].multiplicity * 10 + (ch - '0');
                }
            }
            else {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
            }
        }
        else if (ch == '}') {
            if (curr_brackets_count > 1) {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
                curr_brackets_count--;
            }
            else {
                MultiSet[m].elem_count = elem_in_set + 1;
                curr_brackets_count--;
            }
        }
        else if (ch == ' ' || ch == '\n') {}
        else {
            MultiSet[m].Elem[elem_in_set].element.push_back(ch);
            MultiSet[m].Elem[elem_in_set].code_num += ch;
        }
    }
    MultiSet[0].brackets_count = curr_brackets_count;
    file.close();
}
```

###  Вывод мультимножеств из файла в консоль

* Выводим поэлементно каждое мультмножество (кратность эл. и сам элемент), разделяя  их запятой. 

``` c++
void SeeSets(Set MultiSet[]) {
    for (int i = 0; i < MultiSet[0].set_count; i++) {
        cout << "МНОЖЕСТВО № " << i + 1 << ": \n\n\t{ ";
        for (int j = 0; j < MultiSet[i].elem_count; j++) {
            if (MultiSet[i].Elem[j].multiplicity == 1) {
                if (j != MultiSet[i].elem_count - 1) {
                    cout << MultiSet[i].Elem[j].element << ", ";
                }
                else cout << MultiSet[i].Elem[j].element;
            }
            else {
                if (j != MultiSet[i].elem_count - 1) {
                    cout << MultiSet[i].Elem[j].multiplicity << MultiSet[i].Elem[j].element << ", ";
                }
                else cout << MultiSet[i].Elem[j].multiplicity << MultiSet[i].Elem[j].element;
            }
        }
        cout << "} \n\n\n";
    }
}
```

### Приведение считанных мультимножеств к стандартному типу

* Приводим все муьтимножества типа {а,в,а,с,с,а,а,с} к стандартному виду {4а,в,3с}
  * Проходим по всем элементам мультимножестваю
  * Если найдены одинаковые элементы, суммируем их кратность и записываем в один элемент. Уменьшаем количество элементов в мультимножестве
  * Иначе скипаем его, оставляя в изначальном виде

``` c++
void OneType(Set MultiSet[]) {
    for (int i = 0; i <= MultiSet[0].set_count; i++) {
        for (int j = 0; j < MultiSet[i].elem_count; j++) {
            for (int k = j + 1; k < MultiSet[i].elem_count; k++) {
                if (((MultiSet[i].Elem[j].element == MultiSet[i].Elem[k].element) && ((MultiSet[i].Elem[j].multiplicity != MultiSet[i].Elem[k].multiplicity) || (MultiSet[i].Elem[j].multiplicity == 1 && MultiSet[i].Elem[k].multiplicity == 1)) || (MultiSet[i].Elem[j].code_num == MultiSet[i].Elem[k].code_num))) {
                    MultiSet[i].Elem[j].multiplicity = MultiSet[i].Elem[j].multiplicity + MultiSet[i].Elem[k].multiplicity;
                    for (int t = k; t < MultiSet[i].elem_count; t++) {
                        MultiSet[i].Elem[t] = MultiSet[i].Elem[t + 1];
                    }
                    MultiSet[i].elem_count--;
                    k--;
                }

            }
        }
    }
}
```

### Симметрическая разность

* Сравниваем элементы 1 множеств асо вторым
   * Если найдены одинаковые эелементы, высчитываем разность их кратностей
       * Кратность =0 --- Эл уничтожаются (не записываем в результат симм разности, просто скипаем)
       * Кратность > 0 --- записываем элемент в рез-т с новой кратностью, равной разности А_В мн
       * Кратность < 0 --- домножаем кратность на (-1) и записываем элемент в рез-т с новой кратностью, равной разности А_В мн
   * Если одинаковые элементы не найдены, то записываем эл из 1 мн в разности А_В мн
 * Сравниваем элементы 2 множества с 1
   * Если найдены одинаковые, то скипаем, тк мы уже записали их в разность А_В мн
   * Иначе записываем элемент 2 мн в разность В_А
 * Объединяем разности А_В и В_А и записываем в результат АВ
   

``` c++
void SymmDiff(Set MultiSet[]) {
    Set A = MultiSet[0];
    if (MultiSet[0].brackets_count == 0) {
        int n = 1;
        while (n < MultiSet[0].set_count) {
            Set A_B, B_A, AB;
            int a_b = 0, b_a = 0, ab = 0;

            for (int i = 0; i < A.elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < MultiSet[n].elem_count; j++) {
                    if ((A.Elem[i].element == MultiSet[n].Elem[j].element) || ((A.Elem[i].code_num == MultiSet[n].Elem[j].code_num))) {
                        int mcy;
                        mcy = A.Elem[i].multiplicity - MultiSet[n].Elem[j].multiplicity;
                        if (mcy == 0) {}
                        else if (mcy > 0) {
                            A_B.Elem[a_b] = A.Elem[i];
                            A_B.Elem[a_b].multiplicity = mcy;
                            a_b++;
                            A_B.elem_count++;
                        }
                        else {
                            mcy *= -1;
                            A_B.Elem[a_b] = A.Elem[i];
                            A_B.Elem[a_b].multiplicity = mcy;
                            a_b++;
                            A_B.elem_count++;

                        }
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    A_B.Elem[a_b] = A.Elem[i];
                    a_b++;
                    A_B.elem_count++;
                }

            }

            for (int i = 0; i < MultiSet[n].elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < A.elem_count; j++) {
                    if ((A.Elem[j].element == MultiSet[n].Elem[i].element) || (A.Elem[j].code_num == MultiSet[n].Elem[i].code_num)) {
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    B_A.Elem[b_a] = MultiSet[n].Elem[i];
                    b_a++;
                    B_A.elem_count++;
                }
            }
            for (int i = 0; i < B_A.elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < AB.elem_count; j++) {
                    if (B_A.Elem[i].element == AB.Elem[j].element) {
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    AB.Elem[ab] = B_A.Elem[i];
                    ab++;
                    AB.elem_count++;
                }
            }

            for (int i = 0; i < A_B.elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < AB.elem_count; j++) {
                    if (A_B.Elem[i].element == AB.Elem[j].element) {
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    AB.Elem[ab] = A_B.Elem[i];
                    ab++;
                    AB.elem_count++;
                }
            }

            AB.elem_count--;
            A = AB;
            n++;
        }

        cout << "\nРЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ СИММЕТРИЧЕСКОЙ РАЗНОСТИ:\n\n\t{ ";
        for (int j = 0; j < A.elem_count; j++) {
            if (A.Elem[j].multiplicity == 1) {
                if (j != A.elem_count - 1) {
                    cout << A.Elem[j].element << ", ";
                }
                else cout << A.Elem[j].element;
            }
            else {
                if (j != A.elem_count - 1) {
                    cout << A.Elem[j].multiplicity << A.Elem[j].element << ", ";
                }
                else cout << A.Elem[j].multiplicity << A.Elem[j].element;
            }
        }
        cout << "}\n";
        MultiSet[0] = A;
    }
    else cout << "Некорректный ввод!\n";
}
``` 
### Запуск выполнения всех функций, который отлавливаем исключение

Функция Do_Symm_Diff пытается выполнить функцию GetSets, которая выбратывает ошибку если файл введен некорректно. Если с файлом есть проблема, то Do_Symm_Diff ловит исключение и выкидывает ошибку в консоль, останавливая выполнение всей программы. Иначе запускает выполнение остальных функций.

``` c++
void Do_Symm_Diff(Set MultiSet[], string path) {
    try {
        GetSets(MultiSet, path);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return;
    }

    OneType(MultiSet);
    SeeSets(MultiSet);
    SymmDiff(MultiSet);
}
```
## Примеры выполнения программы
* Файл введен корректно
  
![Снимок экрана 2024-03-29 110624](https://github.com/iis-32170x/RPIIS/assets/145003765/3aa6db5f-2675-4209-a363-b3e383980f23)

![Снимок экрана 2024-03-29 110531](https://github.com/iis-32170x/RPIIS/assets/145003765/2d5e5fa1-6b9b-40d6-afae-8cc5bc86d880)

* Файл введен некорректно

![Снимок экрана 2024-03-29 110735](https://github.com/iis-32170x/RPIIS/assets/145003765/cfdcb917-db82-47ca-b557-345d86be1dcc)
  


## Результат выполнения GTest

![Снимок экрана 2024-03-28 231759](https://github.com/iis-32170x/RPIIS/assets/145003765/192545ae-8f9e-4bef-bb22-fed1d8e57845)

##  Список использованных источников 

* [Мультимножества](https://ru.wikipedia.org/wiki/%D0%9C%D1%83%D0%BB%D1%8C%D1%82%D0%B8%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%BE)
* Л. А. Гладков, В. В. Курейчик, В. М. Курейчик   "Дискретная математика"
* [Обработка исключений](https://learn.microsoft.com/ru-ru/cpp/cpp/errors-and-exception-handling-modern-cpp?view=msvc-170)
* [Считывание из файла](https://purecodecpp.com/archives/2751)
