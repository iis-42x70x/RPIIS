# <p align="center">Лабораторная работа №1</p>
Вариант 27. Однонаправленный список. Вставка элемента в список. Удаление
элемента из списка. Сортировка списка. Поиск элемента в списке.Пересечение и Обьединение списков
## <p align="center">Цели лабораторной работы:</p>
1. Разработать библиотеку для работы с однонаправленным списком на выбранном императивном языке программирования (например, C++, Java, Python).
2. Создать тестовую программу для демонстрации функциональности разработанной библиотеки.
3. Разработать систему тестов для проверки работоспособности и корректности библиотеки, учитывая требования полноты, адекватности и непротиворечивости.
4. Составить отчет по выполнению лабораторной работы.
## <p align="center">Задачи лабораторной работы:</p>
1. Изучить спецификацию задачи по работе с однонаправленным списком.
2. Выбрать язык программирования для реализации библиотеки (например, C++, Java, Python) в соответствии с индивидуальным заданием.
3. Разработать и реализовать библиотеку для работы с односвязным списком, включая операции описанные в индивидуальном задании.
4. Написать тестовую программу, которая демонстрирует работоспособность библиотеки.
5. Разработать систему тестов, включающую тест-кейсы для проверки различных аспектов работы библиотеки, включая корректность, производительность и обработку ошибок.
6. Провести тестирование разработанной библиотеки, убедившись в ее правильной работе на различных входных данных.
7. Составить подробный отчет, включая описание решения задачи, архитектуры библиотеки, результаты тестирования и выводы.
## <p align="center">Список используемых понятий:</p>
1. `Библиотека программного обеспечения (Библиотека кода):` в программировании библиотека представляет собой совокупность программного кода, предназначенного для решения определенных задач. Этот код может содержать функции, классы, процедуры или другие компоненты, которые разработчики могут повторно использовать в своих программных проектах. Библиотеки упрощают разработку, так как они предоставляют готовые решения для типовых задач.
2. `Библиотека gtest/gtest.h:` библиотека для модульного тестирования на языке С++.
3. `Однонаправленный список:` базовая структура данных, представляющая собой соединённые узлы с однотипными данными. Каждый узел состоит из элемента и ссылки на следующий элемент.
## <p align="center">Описание функций:</p>
1. ### <p align="center">Функция Push_back(Добавление элемента в конец списка):</p>
~~~c++
void List::push_b(int _value)
    {
        Node *temp=new Node(_value);
        if(is_empty())
        {
            first=temp;
            last=temp;
            return;
        }
      last->next=temp;
      last=temp;
      size++;
    }
~~~
2. ### <p align="center">Функция Remove(Удаление элемента из списка),Remove_first(Удаление первого элемента из списка),Remove_last(Удаление последнего элемента из списка):</p>
~~~c++
void List::Remove_first()
    {
        if(is_empty())
        {
            return;
        }
        Node* p = first->next;
        delete first;
        first=p;
        size--;
    }

    void List::Remove_last()
    {
        if(is_empty()) return;
        if (first == last)
        {
            Remove_first();
            return ;
        }
        Node* p = first;
        while (p->next != last)
        {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
        size--;
    }
void List::Remove(int _val) {
        if (is_empty()) return;
        if (first->value == _val) {
            Remove_first();
            return;
        }
        else if (last->value == _val) {
                Remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->value != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            return;
        }
        slow->next = fast->next;
        delete fast;
        size--;
    }
~~~
3. ### <p align="center">Функция Sort(Cортировка списка(пузырьком)):</p>
~~~c++
void List::Sort()
    {
        Node* temp = first;
        while (temp != nullptr)
        {
            Node* current = first;
            while (current->next != nullptr)
            {
                if (current->value >= current->next->value) 
                {
                   swap(current->value, current->next->value);
                }
                current = current->next;
            }
            temp = temp->next;
        }
    }
~~~
4. ### <p align="center">Функция find(Нахождение элемента в списке(Вовзаращает истину,если элемент найден и ложь,если нет)):</p>
~~~c++
bool List::find(int _value)
    {
        Node* temp = first;
        while (temp != nullptr && temp->value != _value)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
~~~
5. ### <p align="center">Функция Union_list(Обьединение двух списков):</p>
~~~c++
List List::union_list(Node *current2)
    {
        List a1;
        List b1;
        List result;

        Node *current1=this->first;//Копируем элементы 1-ого списка
        while(current1!=nullptr)
        {
            a1.push_b(current1->value);
            current1=current1->next;
        }
        while(current2!=nullptr)
        {
            b1.push_b(current2->value);
            current2=current2->next;
        }
        Node *current3=a1.first;
        while(current3!=nullptr)
        {
            Node *current4=b1.first;
            while(current4!=nullptr)
            {
                if(current3->value == current4->value)
                {
                    result.push_b(current3->value);
                    a1.Remove(current3->value);
                    b1.Remove(current4->value);
                    current3=a1.first;
                    break;
                }
                current4=current4->next;    
            }
            if(current3!=nullptr)
            current3=current3->next;    
        }
        for(Node *current5=a1.first;current5!=nullptr;current5=current5->next)
        {
            result.push_b(current5->value);
        }
        for(Node *current6=b1.first;current6!=nullptr;current6=current6->next)
        {
            result.push_b(current6->value);
        }
        result.Sort();  
        return result;
    }
~~~
6. ### <p align="center">Функция Intersection_list(Пересечение двух списков):</p>
~~~c++
List List::intersection_list(Node *current2)
    {
        List a1;
        List b1;
        List result;

        Node *current1=this->first;//Копируем элементы 1-ого списка
        while(current1!=nullptr)
        {
            a1.push_b(current1->value);
            current1=current1->next;
        }
        while(current2!=nullptr)
        {
            b1.push_b(current2->value);
            current2=current2->next;
        }
        Node *current3=a1.first;
        while(current3!=nullptr)
        {
            Node *current4=b1.first;
            while(current4!=nullptr)
            {
                if(current3->value == current4->value)
                {
                    result.push_b(current3->value);
                    a1.Remove(current3->value);
                    b1.Remove(current4->value);
                    current3=a1.first;
                    break;
                }
                current4=current4->next;    
            }
            if(current3!=nullptr)
            current3=current3->next;    
        }     
        result.Sort();
        return result; 
    }
~~~
## <p align="center">Результаты Тестов:</p>
![Снимок экрана от 2025-03-19 19-10-35](https://github.com/user-attachments/assets/e0d0e19d-9160-45fe-ab7a-98c318efff13)
![Снимок экрана от 2025-03-19 19-10-57](https://github.com/user-attachments/assets/103f2f96-b23b-4c7a-a00a-c5ab0ce6cb7a)
## <p align="center">Вывод</p>
В ходе выполнения работы познакомился созданием библиотек в С++, познакомился с концепцией реализация в .срр файлах, декларация $-$ в .hpp,познакомился с Google C++ Testing Framework,реализоавал библиотеку для работы c однонаправленным списком,а также создал систему тестов,которая проверяет корректность созданной библиотеки.
## <p align="center">Используемые источники и материалы:</p>
- https://stackoverflow.com/questions/1208028/significance-of-a-inl-file-in-c (.inl)
- https://www.cyberforum.ru/cpp-beginners/thread2600085.html (про .h и .cpp)
- https://www.youtube.com/watch?v=SajrPhE6FoQ (реализация однонаправленного списка от SimpleCode)
- https://habr.com/ru/articles/667880/ (googletest)
- http://google.github.io/googletest/ (googletest)
- https://chat.deepseek.com (помощь в освоении материала)

