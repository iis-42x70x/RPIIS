# Лабораторная работа 1. Структуры данных
## Цель работы
- Исследовать свойства структур данных.
- Разработать библиотеку алгоритмов обработки структур данных.
## Задачи
- Разработать библиотеку для работы со структурой данных двунаправленный список на языке программирования C#.
- Разработать тестовую программу, которая демонстрирует работоспособность реализованной библиотеки работы со структурой данных.
- Методы, достпуные в реализованной библиотеке: вставка элемента в список, удаление элемента из списка, сортировка списка, поиск элемента в списке, объединение и пересечение двух списков.
## Список используемых понятий
Двусвязный (двунаправленный) список — это разновидность связного списка, при которой переход по элементам возможен в обоих направлениях (как вперед, так и назад), в отличие от односвязного (однонаправленного) списка.
Вот термины, необходnuимые для понимания концепции двусвязных (двунаправленных) списков:

- Ссылка. В каждой ссылке связного списка могут храниться данные, называемые элементом.
- Следующая ссылка. В каждой ссылке связного списка содержится ссылка на следующую ссылку (Next).
- Предыдущая ссылка. В каждой ссылке связного списка содержится ссылка на предыдущую ссылку (Prev).
- Связный список содержит ссылку (связку) на первую ссылку (First) и на последнюю ссылку (Last).

![Пример списка](https://miro.medium.com/v2/resize:fit:1100/format:webp/0*qIPvFnSs3903p0E_.jpg)

- **Источники**:  
Статья с [medium.com](https://medium.com/nuances-of-programming/%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B-%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85-%D0%B8-%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B-%D0%B4%D0%B2%D1%83%D1%81%D0%B2%D1%8F%D0%B7%D0%BD%D1%8B%D0%B9-%D0%B4%D0%B2%D1%83%D0%BD%D0%B0%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%BD%D1%8B%D0%B9-%D1%81%D0%BF%D0%B8%D1%81%D0%BE%D0%BA-8d2bcb42da49).


### Алгоритмы

### Реализуем тип данных списка
public class DoublyNode<T> — узел двусвязного списка с обобщённым типом T.

T Data — данные, хранящиеся в узле.

DoublyNode<T> Previous — ссылка на предыдущий узел.

DoublyNode<T> Next — ссылка на следующий узел.

Конструкторы:

DoublyNode(T data) — создаёт узел с данными.

DoublyNode() — пустой конструктор.
```c#
namespace Lib
{
    public class DoublyNode<T>
    {
        public T Data { get; set; }
        public DoublyNode<T> Previous { get; set; } // хранит ссылку
        public DoublyNode<T> Next { get; set; }
        public DoublyNode(T data)
        {
            this.Data = data;
        }

        public DoublyNode()
        {

        }
    }

}
```

**Основные функции:**
- *add*- добавление элемента
- *AddFirst* - добавление элемента в начлао списка
- *print* - вывод двухсвязного списка
- *RemoveElement* - удаление элемента
- *Count* - отображение количества элементов в списке
- *IsPUSTO* - возращает булевое значение в зависимости есть или нет элементов в списке
- *Clear* - удаляет список
- *search* - выполняет поиск в списке по значению 
- *SortMintoMax* - сортирует список 
- *mergeList* -  "сливает" два списка в один
- *FindIntersection* - находит пересечение элементов


### Функция add:

```c#
public void Add(T data)
        {
            DoublyNode<T> node = new DoublyNode<T>(data);
            if (head == null)
                head = node;
            else
            {
                tail.Next = node;
                node.Previous = tail;
            }
            tail = node;
            count++;
        }

```

### Функция AddFirst 
Создаётся новый узел node с переданными данными.

Если список пуст (head == null), то новый узел становится и головой, и хвостом.

Иначе:

у прежнего хвоста (tail) устанавливается Next = node,

у нового узла — Previous = tail.

Ссылка tail обновляется на node.

Счётчик count увеличивается на 1.
```c#
 public void AddFirst(T data)
        {
            DoublyNode<T> node = new DoublyNode<T>(data);
            DoublyNode<T> temp = head;
            node.Next = temp;
            head = node;
            if (count == 0)
                tail = head;
            else
                temp.Previous = node;
            count++;
        }
```

### Функция print
Начинает с головы списка (head).

Пока узел не null, выводит его данные (Data) через пробел.

Переходит к следующему узлу (print = print.Next).

В конце — перенос строки.
```c#
 public void print()
        {
            DoublyNode<T> print = head;
            while (print != null)
            {
                Console.Write(" " + print.Data);
                print = print.Next;
            }
            Console.WriteLine();
        }
```

### Функция RemoveElement
Ищет узел с нужными данными (data).

Если находит:

Обновляет ссылки соседних узлов, чтобы "вырезать" текущий.

Если это был хвост — обновляет tail.

Если это была голова — обновляет head.

Уменьшает счётчик count.

Возвращает true.

Если не находит — возвращает false.
```c#
 public bool RemoveElement(T data)
        {
            DoublyNode<T> current = head;
            while (current != null) // проходим по всему списку
            {
                if (current.Data.Equals(data)) // сравниваем 
                {
                    break;
                }
                current = current.Next;
            }
            if (current != null) // будет выполняться только если нашли элемент
            {                    // если элемент не найден то элемент равна НУЛ
                if (current.Next != null)
                {
                    current.Next.Previous = current.Previous;
                }
                else
                {
                    tail = current.Previous;
                }
                if (current.Previous != null)
                {
                    current.Previous.Next = current.Next;
                }
                else
                {
                    head = current.Next;
                }
                count--;
                return true;
            }
            return false;
        }
```
### Функция Count
Только для чтения (get).

Возвращает текущее количество элементов в списке (count).
```c#
  public int Count { get { return count; } }
```
### Функция IsPUSTO
Только для чтения (get).

Возвращает true, если список пуст (count == 0), иначе — false.
```c#
 public bool IsPUSTO { get { return count == 0; } }
```
### Функция Clear
Полностью очищает список:

обнуляет ссылки на head и tail,

сбрасывает счётчик count в 0.
```c#
public void Clear()
        {
            head = null;
            tail = null;
            count = 0;
        }
```
### Функция search
Проходит по списку от головы.

Если находит узел с нужными данными — возвращает true.

Если не находит — возвращает false.
```c#
public bool search(T data)
        {
            DoublyNode<T> current = head;
            while (current != null)
            {
                if (current.Data.Equals(data))
                    return true;
                current = current.Next;
            }
            return false;
        }
```
### Функция SortMintoMax
Сортирует список по возрастанию (сортировка пузырьком).

Пока есть перестановки (swapped == true):

Проходит по списку.

Если текущий элемент больше следующего — меняет их местами.

Работает для обобщённого типа T с поддержкой сравнения (Comparer<T>)
```c#
 public void SortMintoMax()
        {
            if (head == null || head.Next == null)
            {
                return;
            }

            bool swapped;
            do
            {
                swapped = false;
                DoublyNode<T> current = head;

                while (current.Next != null)
                {
                    if (Comparer<T>.Default.Compare(current.Data, current.Next.Data) > 0)
                    {
                        T temp = current.Data;
                        current.Data = current.Next.Data;
                        current.Next.Data = temp;
                        swapped = true;
                    }
                    current = current.Next;
                }
            } while (swapped);
        }
```
### Функция mergeList
Объединяет два списка: добавляет list2 в конец list1.

Если оба пусты — ничего не делает.

Если list1 пуст — копирует в него list2.

Если list2 пуст — ничего не делает.

Иначе соединяет хвост list1 с головой list2, обновляет tail и count.

Обнуляет list2 (он становится пустым).
```c#
 public void mergeList(MyList<T> list1, MyList<T> list2) // сливание списков
        {
            if (list1.IsPUSTO && list2.IsPUSTO)
            {
                return;
            }
            if (list1.IsPUSTO)
            {
                list1.head = list2.head;
                list1.tail = list2.tail;
                list1.count = list2.count;
                return;
            }
            if (list2.IsPUSTO)
            {
                return;
            }

            list1.tail.Next = list2.head;
            list2.head.Previous = list1.tail;
            list1.tail = list2.tail;
            list1.count += list2.count;

            list2.head = null;
            list2.tail = null;
            list2.count = 0;
        }
```
### Функция FindIntersection
Ищет пересечение двух списков.

Проходит по каждому элементу list1 и ищет его в list2.

Если находит совпадение, добавляет его в новый список intersection.

Возвращает новый список, содержащий элементы, которые есть в обоих списках.
```c#
 public MyList<T> FindIntersection(MyList<T> list1, MyList<T> list2) // пересечение
        {
            MyList<T> intersection = new MyList<T>();
            DoublyNode<T> current1 = list1.head;

            while (current1 != null)
            {
                DoublyNode<T> current2 = list2.head;
                while (current2 != null)
                {
                    if (current1.Data.Equals(current2.Data))
                    {
                        intersection.Add(current1.Data);
                        break;
                    }
                    current2 = current2.Next;
                }
                current1 = current1.Next;
            }

            return intersection;

        }
```
 Алгоритмы [metanit](https://metanit.com/sharp/algoritm/2.2.php).
## Пример работы
Реализуем библиотеку в программе:
```c#
using System;
using Lib;

namespace ProjectWithLib
{
    class Program
    {
        static void Main()
        {
            Random random = new Random();
            MyList<int> list1 = new MyList<int>();
            MyList<int> list2 = new MyList<int>();


            int size1 = random.Next(5, 20);
            int size2 = random.Next(5, 20);
            for (int i = 0; i < size1; i++)
            {
                list1.Add(random.Next(1, 20));
            }
            for (int i = 0; i < size2; i++)
            {
                list2.Add(random.Next(1, 20));
            }

            Console.WriteLine($"Initial List 1 (Size: {size1}):");
            list1.print();
            Console.WriteLine($"Initial List 2 (Size: {size2}):");
            list2.print();

            while (true)
            {
                Console.WriteLine("Select an action:");
                Console.WriteLine("1 - Add element");
                Console.WriteLine("2 - Add first element");
                Console.WriteLine("3 - Search element");
                Console.WriteLine("4 - Remove element");
                Console.WriteLine("5 - Sort");
                Console.WriteLine("6 - Find intersection");
                Console.WriteLine("7 - Merge");
                Console.WriteLine("8 - View");
                Console.WriteLine("9 - Exit");

                int choice = Convert.ToInt32(Console.ReadLine());

                if (choice >= 1 && choice <= 5)
                {
                    Console.WriteLine("Select the list (1 or 2): ");
                    int listChoice = Convert.ToInt32(Console.ReadLine());
                    MyList<int> selectedList;

                    if (listChoice == 2)
                        selectedList = list2;

                    else
                        selectedList = list1;


                    switch (choice)
                    {
                        case 1:
                            Console.Write("Enter number to add: ");
                            int addNum = Convert.ToInt32(Console.ReadLine());
                            selectedList.Add(addNum);
                            Console.Write("Updated List: ");
                            selectedList.print();
                            break;




                        case 2:
                            Console.Write("Enter number to add first: ");
                            int addFirstNum = Convert.ToInt32(Console.ReadLine());
                            selectedList.AddFirst(addFirstNum);
                            Console.Write("Updated List: ");
                            selectedList.print();
                            break;

                        case 3:
                            Console.Write("Enter number to search: ");
                            int searchNum = Convert.ToInt32(Console.ReadLine());
                            if (selectedList.search(searchNum))
                                Console.WriteLine("Number found!");
                            else
                                Console.WriteLine("Number not found.");
                            break;

                        case 4:
                            Console.Write("Enter number to remove: ");
                            int removeNum = Convert.ToInt32(Console.ReadLine());
                            if (selectedList.RemoveElement(removeNum))
                                Console.WriteLine("Number removed successfully.");
                            else
                                Console.WriteLine("Number not found in the list.");
                            break;

                        case 5:
                            Console.Write("Sorting list...");
                            selectedList.SortMintoMax();
                            selectedList.print();
                            break;
                    }
                }
                else
                {
                    switch (choice)
                    {

                        case 6:
                            MyList<int> intersection = list1.FindIntersection(list1, list2);
                            Console.WriteLine("Intersection of List 1 and List 2:");
                            intersection.print();
                            break;

                        case 7:
                            list1.mergeList(list1, list2);
                            Console.WriteLine("Merged List:");
                            list1.print();
                            break;

                        case 8:
                            list1.print();
                            list2.print();
                            break;

                        case 9:
                            Console.WriteLine("Exiting...");
                            return;

                        default:
                            Console.WriteLine("Invalid choice. Please try again.");
                            break;
                    }
                }
            }
        }
    }
}
```
При запуске у нас рандомный(от 5 до 20) размер списка и рандомные(от 1 до 20) элементы списка:
![image](https://github.com/user-attachments/assets/bf669121-9286-4f10-a9c5-44b7de67787d)

Это реализуется в этой части кода:
```c#
  Random random = new Random();
            MyList<int> list1 = new MyList<int>();
            MyList<int> list2 = new MyList<int>();


            int size1 = random.Next(5, 20);
            int size2 = random.Next(5, 20);
            for (int i = 0; i < size1; i++)
            {
                list1.Add(random.Next(1, 20));
            }
            for (int i = 0; i < size2; i++)
            {
                list2.Add(random.Next(1, 20));
            }

            Console.WriteLine($"Initial List 1 (Size: {size1}):");
            list1.print();
            Console.WriteLine($"Initial List 2 (Size: {size2}):");
            list2.print();
```

Далее получаем список операций, которые можем выполнить со списком(ами):
![image](https://github.com/user-attachments/assets/9a0bb801-bd6f-4d6a-a967-91a71774f6f0)

Ну и можем проверить корректность выполнения методов из библиотеки:

# Добавим элемент 667 во второй список:
![image](https://github.com/user-attachments/assets/b81f1a8c-4c19-4373-8bc1-3d18a1d1c778)
# Добавим элемент в начало 1-го списка:
![image](https://github.com/user-attachments/assets/127f9113-34f7-4339-b492-3753c9c81923)
# Так можем найти элемент:
![image](https://github.com/user-attachments/assets/e348b4e9-5745-4f3e-beaa-ea701054d10e)
# Удалили 667:
![image](https://github.com/user-attachments/assets/6dc6b8a4-b19b-4a8b-ae56-7fdeb0a862d0)
# 667 отсутствует (мы его удалили):
![image](https://github.com/user-attachments/assets/b8d2cfdc-335a-4803-89f7-f548f9415907)
# Отсортировали первый список: 
![image](https://github.com/user-attachments/assets/2d552e24-802c-49d3-a73a-12c3624793a3)
# Вот пересечение списков:
![image](https://github.com/user-attachments/assets/5abc70dd-b612-41e1-a398-336a454cb3fa)
# Объединение двух списков (список 1 становится объединением двух списков, второй список становится пустым):
![image](https://github.com/user-attachments/assets/6bbd2c3b-2374-4fc1-bde7-d5d2c8bd0254)
# Ну и последний вариант выбора(не считая завершения), просмотр:
![image](https://github.com/user-attachments/assets/77827d90-e6b6-4f22-9e76-239ce925d2fc)
Как можем заметить, второй список перестал существовать, а первый список увеличился(это из-за операции объежинения)


## Вывод
В ходе выполнения данной лабораторной работы я:
- Изучил принцип работы двунаправленного списка.
- Приобрёл навыки разработки библиотек в C#.
- Разработал библиотеку алгоритмов обработки структуры данных двунаправленного списка.
